#pragma once

#include "HeaderFile.h"
class VulkanCommandPool
{
public:
	uint32_t familyIndex;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;

public:
	VulkanCommandPool(uint32_t index);
	~VulkanCommandPool();


	void Destroy();




	void createCommandBuffers();


	void recordCommand(class VulkanGraphicsPipeline*);

	void freeCommandBuffers();
private:
	void createCommandPool(uint32_t index);

};

