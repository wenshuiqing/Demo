#pragma once
#include "HeaderFile.h"


class VulkanInstance
{
private:
	static VulkanInstance* instanceWrap;

public:
	VkInstance instance;



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
	std::vector<const char*> getRequiredExtensions();
};

