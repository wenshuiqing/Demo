#include "VulkanCommandPool.h"
#include "VulkanDevice.h"
#include "VulkanSwapChainKHR.h"
#include "VulkanGraphicsPipeline.h"



VulkanCommandPool::VulkanCommandPool(uint32_t index) :familyIndex(index)
{
	createCommandPool(index);
}

VulkanCommandPool::~VulkanCommandPool()
{
	Destroy();
}


void VulkanCommandPool::Destroy()
{
	if (commandBuffers.size() > 0)
		freeCommandBuffers();
	vkDestroyCommandPool(VulkanDevice::GetInstance()->device, commandPool, nullptr);
}

void VulkanCommandPool::createCommandPool(uint32_t index)
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = index;

	if (vkCreateCommandPool(VulkanDevice::GetInstance()->device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create command pool!");
	}
}

void VulkanCommandPool::createCommandBuffers()
{
	commandBuffers.resize(VulkanSwapChainKHR::GetInstance()->swapChainFramebuffers.size());

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

	if (vkAllocateCommandBuffers(VulkanDevice::GetInstance()->device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate command buffers!");
	}

}


void VulkanCommandPool::recordCommand(VulkanGraphicsPipeline* graphicsPipelineWrap)
{
	for (size_t i = 0; i < commandBuffers.size(); i++) {
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

		if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = graphicsPipelineWrap->renderPass;
		renderPassInfo.framebuffer = VulkanSwapChainKHR::GetInstance()->swapChainFramebuffers[i];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = VulkanSwapChainKHR::GetInstance()->swapChainExtent;

		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipelineWrap-> graphicsPipeline);

		vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

		vkCmdEndRenderPass(commandBuffers[i]);

		if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
			throw std::runtime_error("failed to record command buffer!");
		}
	}
}

void VulkanCommandPool::freeCommandBuffers()
{
	if (commandBuffers.size() > 0)
		vkFreeCommandBuffers(VulkanDevice::GetInstance()->device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
}
