#pragma once
#include "HeaderFile.h"


class VulkanSwapChainKHR
{
private:
	static VulkanSwapChainKHR* instance;

public:

	VkSwapchainKHR swapChain;

	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;

private:
	VulkanSwapChainKHR();
	VulkanSwapChainKHR(const VulkanSwapChainKHR&)=delete;
	VulkanSwapChainKHR& operator=(VulkanSwapChainKHR&) = delete;
	virtual ~VulkanSwapChainKHR();

public:
	static VulkanSwapChainKHR* GetInstance();

	void Init();

	void Destroy();

	void createFramebuffers(class VulkanGraphicsPipeline* );

	void destroyFramebuffers();

private:
	void createSwapChain();

	void createImageViews();


	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& avaliableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> avaliablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
};

