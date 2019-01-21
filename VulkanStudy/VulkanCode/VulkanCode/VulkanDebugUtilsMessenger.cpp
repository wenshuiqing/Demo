#include "VulkanDebugUtilsMessenger.h"
#include "VulkanInstance.h"


VulkanDebugUtilsMessenger * VulkanDebugUtilsMessenger::instance = 0;
VulkanDebugUtilsMessenger::VulkanDebugUtilsMessenger()
{
	
}

VulkanDebugUtilsMessenger::~VulkanDebugUtilsMessenger()
{

}

VulkanDebugUtilsMessenger* VulkanDebugUtilsMessenger::GetInstance()
{
	if (instance == nullptr)
		instance = new VulkanDebugUtilsMessenger();

	return instance;
}

void VulkanDebugUtilsMessenger::Init()
{
	if (!enableValidationLayers)return;

	VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
		| VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
		| VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

	createInfo.pfnUserCallback = debugCallback;
	createInfo.pUserData = nullptr;


	if (CreateDebugUtilsMessengerEXT (&createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
		throw std::runtime_error("failed to set up debug messenger");
	}
}

void VulkanDebugUtilsMessenger::Destroy()
{
	if (enableValidationLayers) {
		DestroyDebugUtilsMessengerEXT(debugMessenger, nullptr);
	}
}



VkResult VulkanDebugUtilsMessenger::CreateDebugUtilsMessengerEXT( const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
{
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(VulkanInstance::GetInstance()-> instance, "vkCreateDebugUtilsMessengerEXT");
	if (func != nullptr) {
		return func(VulkanInstance::GetInstance()->instance, pCreateInfo, pAllocator, pDebugMessenger);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void VulkanDebugUtilsMessenger::DestroyDebugUtilsMessengerEXT( VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(VulkanInstance::GetInstance()->instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) {
		func(VulkanInstance::GetInstance()->instance, debugMessenger, pAllocator);
	}
}
