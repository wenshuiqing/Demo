#include "VulkanInstance.h"


VulkanInstance * VulkanInstance::instanceWrap = 0;
VulkanInstance::VulkanInstance()
{

}


VulkanInstance::~VulkanInstance()
{
}


VulkanInstance* VulkanInstance::GetInstance()
{
	if (instanceWrap == nullptr)
		instanceWrap = new VulkanInstance();

	return instanceWrap;
}

void VulkanInstance::Init()
{
	if (enableValidationLayers && !checkValidationLayersSupport()) {
		throw std::runtime_error("validation layers request,but not avaliable!");
	}


	VkApplicationInfo appInfoe = {};
	appInfoe.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfoe.pApplicationName = "Hello Triangle";
	appInfoe.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfoe.pEngineName = "No Engine";
	appInfoe.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfoe.apiVersion = VK_API_VERSION_1_0;
	//appInfoe.pNext = nullptr;

	//instance 的创建信息
	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfoe;


	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
	std::cout << "avaliable extensions : " << std::endl;
	for (const auto& extension : extensions)
	{
		std::cout << "\t" << extension.extensionName << std::endl;
	}

	auto glfwExtensions = getRequiredExtensions();

	createInfo.enabledExtensionCount = static_cast<uint32_t>(glfwExtensions.size());
	createInfo.ppEnabledExtensionNames = glfwExtensions.data();

	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}


	//创建实例
	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
		throw std::runtime_error("fail to create instance");
	}
}


void VulkanInstance::Destory()
{
	vkDestroyInstance(instance, nullptr);
}



bool VulkanInstance::checkValidationLayersSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> avalidationLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, avalidationLayers.data());


	for (const char* layerName : validationLayers) {
		bool layerFound = false;

		for (const auto& layerProperties : avalidationLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}
		if (!layerFound) {
			return false;
		}
	}

	return true;
}

std::vector<const char*> VulkanInstance::getRequiredExtensions()
{
	//获取扩展
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	}

	return extensions;
}
