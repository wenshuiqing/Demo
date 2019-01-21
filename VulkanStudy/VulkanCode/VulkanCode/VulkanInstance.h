#pragma once
#include "HeaderFile.h"

#ifdef NDEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = true;
#endif


class VulkanInstance
{
private:
	static VulkanInstance* instanceWrap;

public:
	VkInstance instance;

	const std::vector<const char*> validationLayers = {
	"VK_LAYER_LUNARG_standard_validation"
	};


private:
	VulkanInstance();
	VulkanInstance(const VulkanInstance&)=delete;
	VulkanInstance& operator=(const VulkanInstance&) = delete;
	virtual ~VulkanInstance();



public:
	static VulkanInstance* GetInstance();
	void Init();


	void Destory();


private:
	bool checkValidationLayersSupport();
	std::vector<const char*> getRequiredExtensions();
};

