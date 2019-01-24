#pragma once
#include "HeaderFile.h"
class VulkanLayerAndExtension
{
private:


private:
	static VulkanLayerAndExtension* instance;
	VulkanLayerAndExtension();
	VulkanLayerAndExtension(const VulkanLayerAndExtension&) = delete;
	VulkanLayerAndExtension* operator=(VulkanLayerAndExtension&) = delete;
	~VulkanLayerAndExtension();




public:
	static VulkanLayerAndExtension* GetInstance();

	bool CheckExtensionSupport(std::vector<const char*> extensionNames, VkPhysicalDevice gpu);

	bool CheckLayersSupport(std::vector<const char*> LayerNames);


};

