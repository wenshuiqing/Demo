#pragma once
#include "HeaderFile.h"

class VulkanDebugUtilsMessenger
{
private:
	static VulkanDebugUtilsMessenger* instance;
public:

	VkDebugUtilsMessengerEXT debugMessenger;

private:
	VulkanDebugUtilsMessenger();
	VulkanDebugUtilsMessenger(const VulkanDebugUtilsMessenger&)=delete;
	VulkanDebugUtilsMessenger& operator=(VulkanDebugUtilsMessenger&) = delete;
	virtual ~VulkanDebugUtilsMessenger();

public:
	static VulkanDebugUtilsMessenger* GetInstance();

	void Init();

	void Destroy();

private:
	VkResult CreateDebugUtilsMessengerEXT(
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, 
		const VkAllocationCallbacks* pAllocator, 
		VkDebugUtilsMessengerEXT* pDebugMessenger);

	void DestroyDebugUtilsMessengerEXT( VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
		std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

		return VK_FALSE;
	}
};

