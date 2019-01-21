#pragma once

#include "HeaderFile.h"
#include <optional>
#include "VulkanInstance.h"

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentFamily;

	bool isComplete() {
		return graphicsFamily.has_value() && presentFamily.has_value();
	}
};
struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};


const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

class VulkanDevice
{
private:
	static VulkanDevice* instance;
	VulkanDevice();
	VulkanDevice(const VulkanDevice&)=delete;
	VulkanDevice& operator=(const VulkanDevice&)=delete;
	virtual ~VulkanDevice();


public:
	VkSurfaceKHR surface;
	VkDevice device;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkQueue graphicsQueue;
	VkQueue presentQueue;

public:
	static VulkanDevice* GetInstance();

	void Init();


	void Destroy();


	QueueFamilyIndices FindQueueFamilies();

	SwapChainSupportDetails QuerySwapChainSupport();

private:

	void createSurface();
	void PickPhysicalDevice();

	void createLogicDevice();
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	
	bool isDeviceSuitable(VkPhysicalDevice device);

	bool checkDeviceExtensionSupport(VkPhysicalDevice device);


};

