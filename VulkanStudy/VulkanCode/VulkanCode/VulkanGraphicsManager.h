#pragma once
#include "HeaderFile.h"

class VulkanGraphicsPipeline;
class VulkanCommandPool;
class VulkanGraphicsManager
{
public:

	VulkanGraphicsPipeline* graphicsPipelineWrap;
	VulkanCommandPool* commandPoolWrap;


public:
	const int MAX_FRAMES_IN_FLIGHT = 2;

private:
	


	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	size_t currentFrame = 0;


public:
	VulkanGraphicsManager();
	virtual ~VulkanGraphicsManager();

	void Init();

	void DrawFrame();

	void Destroy();

private:
	void createSyncObjects();

	void recreateSwapChain();

	void cleanupSwapChain();
};

