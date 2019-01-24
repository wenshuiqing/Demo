#include "VulkanLayerAndExtension.h"

VulkanLayerAndExtension* VulkanLayerAndExtension::instance = 0;

VulkanLayerAndExtension::VulkanLayerAndExtension()
{
}


VulkanLayerAndExtension::~VulkanLayerAndExtension()
{
}


VulkanLayerAndExtension* VulkanLayerAndExtension::GetInstance()
{
	if (instance = nullptr)
		instance = new VulkanLayerAndExtension();
	return instance;
}

bool VulkanLayerAndExtension::CheckExtensionSupport(std::vector<const char*> extensionNames, VkPhysicalDevice gpu)
{
	uint32_t extensionCount;
	std::vector<VkExtensionProperties> availableExtensions;
	if (gpu != nullptr) {
		vkEnumerateDeviceExtensionProperties(gpu, nullptr, &extensionCount, nullptr);
		availableExtensions.resize(extensionCount);
		vkEnumerateDeviceExtensionProperties(gpu, nullptr, &extensionCount, availableExtensions.data());
	}
	else
	{
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		availableExtensions.resize(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtensions.data());
	}
	std::set<std::string> requiredExtensions(extensionNames.begin(), extensionNames.end());

	for (const auto& extension : availableExtensions)
	{
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}

bool VulkanLayerAndExtension::CheckLayersSupport(std::vector<const char*> LayerNames)
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> avalidationLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, avalidationLayers.data());

	std::set<std::string> requiredLayers(LayerNames.begin(), LayerNames.end());

	for (const auto& layer : avalidationLayers)
	{
		requiredLayers.erase(layer.layerName);
	}

	return requiredLayers.empty();
}
