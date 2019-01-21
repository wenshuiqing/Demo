#include "VulkanGraphicsManager.h"
#include "VulkanWindow.h"
#include "VulkanInstance.h"
#include "VulkanDebugUtilsMessenger.h"
#include "VulkanDevice.h"
#include "VulkanSwapChainKHR.h"



VulkanGraphicsManager::VulkanGraphicsManager()
{
	graphicsPipelineWrap = new VulkanGraphicsPipeline();
}


VulkanGraphicsManager::~VulkanGraphicsManager()
{
	Destroy();
}

void VulkanGraphicsManager::Init()
{
	VulkanInstance::GetInstance()->Init();
	VulkanDebugUtilsMessenger::GetInstance()->Init();
	VulkanDevice::GetInstance()->Init();
	VulkanSwapChainKHR::GetInstance()->Init();

	graphicsPipelineWrap->Init();

	VulkanSwapChainKHR::GetInstance()->createFramebuffers(graphicsPipelineWrap);

	QueueFamilyIndices queueFamilyIndices = VulkanDevice::GetInstance()->FindQueueFamilies();
	commandPoolWrap = new VulkanCommandPool(queueFamilyIndices.graphicsFamily.value());
	commandPoolWrap->createCommandBuffers();
	commandPoolWrap->recordCommand(graphicsPipelineWrap);

	createSyncObjects();
}

void VulkanGraphicsManager::DrawFrame()
{
	vkWaitForFences(VulkanDevice::GetInstance()->device, 1, &inFlightFences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());

	uint32_t imageIndex;
	VkResult result = vkAcquireNextImageKHR(VulkanDevice::GetInstance()->device, VulkanSwapChainKHR::GetInstance()->swapChain, std::numeric_limits<uint64_t>::max(), imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

	if (result == VK_ERROR_OUT_OF_DATE_KHR) {
		recreateSwapChain();
		return;
	}
	else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
		throw std::runtime_error("failed to acquire swap chain image!");
	}

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;

	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &(commandPoolWrap->commandBuffers[imageIndex]);

	VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(VulkanDevice::GetInstance()->device, 1, &inFlightFences[currentFrame]);
	//fence用于在命令缓冲区完成执行时进行通知，我们可以用来通知一帧完成了
	if (vkQueueSubmit(VulkanDevice::GetInstance()->graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { VulkanSwapChainKHR::GetInstance()->swapChain };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;

	presentInfo.pImageIndices = &imageIndex;

	result = vkQueuePresentKHR(VulkanDevice::GetInstance()->presentQueue, &presentInfo);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR ||VulkanWindow::GetInstance()-> framebufferResized) {
		VulkanWindow::GetInstance()->framebufferResized = false;
		recreateSwapChain();
	}
	else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swap chain image!");
	}

	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}



void VulkanGraphicsManager::Destroy()
{
	cleanupSwapChain();

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		vkDestroySemaphore(VulkanDevice::GetInstance()->device, renderFinishedSemaphores[i], nullptr);
		vkDestroySemaphore(VulkanDevice::GetInstance()->device, imageAvailableSemaphores[i], nullptr);
		vkDestroyFence(VulkanDevice::GetInstance()->device, inFlightFences[i], nullptr);
	}

	commandPoolWrap->Destroy();

	VulkanDevice::GetInstance()->Destroy();
	VulkanDebugUtilsMessenger::GetInstance()->Destroy();
	VulkanInstance::GetInstance()->Destory();

}



void VulkanGraphicsManager::createSyncObjects()
{
	imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo = {};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		if (vkCreateSemaphore(VulkanDevice::GetInstance()->device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
			vkCreateSemaphore(VulkanDevice::GetInstance()->device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
			vkCreateFence(VulkanDevice::GetInstance()->device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to create synchronization objects for a frame!");
		}
	}
}

void VulkanGraphicsManager::recreateSwapChain()
{
	int width = 0, height = 0;
	while (width == 0 || height == 0) {
		glfwGetFramebufferSize(VulkanWindow::GetInstance()->window, &width, &height);
		glfwWaitEvents();
	}

	vkDeviceWaitIdle(VulkanDevice::GetInstance()->device);

	cleanupSwapChain();

	VulkanSwapChainKHR::GetInstance()->Init();

	graphicsPipelineWrap->Init();
	VulkanSwapChainKHR::GetInstance()->createFramebuffers(graphicsPipelineWrap);
	commandPoolWrap->createCommandBuffers();
}

void VulkanGraphicsManager::cleanupSwapChain()
{

	VulkanSwapChainKHR::GetInstance()->destroyFramebuffers();

	commandPoolWrap->freeCommandBuffers();

	graphicsPipelineWrap->Destroy();

	VulkanSwapChainKHR::GetInstance()->Destroy();
}

