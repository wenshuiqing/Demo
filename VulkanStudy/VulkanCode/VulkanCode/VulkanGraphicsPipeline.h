#pragma once

#include "ShaderLoader.h"
class VulkanGraphicsPipeline
{

public:
	ShaderLoader shaderLoader;

	std::vector<VkShaderModule> shaderModules;

	VkPipeline graphicsPipeline;
	VkPipelineLayout pipelineLayout;
	VkRenderPass renderPass;

	std::vector<VkPipelineShaderStageCreateInfo> shaderStages;

	VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
	VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
	VkViewport viewport = {};
	VkRect2D scissor = {};
	VkPipelineViewportStateCreateInfo viewportState = {};
	VkPipelineRasterizationStateCreateInfo rasterizer = {};
	VkPipelineMultisampleStateCreateInfo multisampling = {};

	VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
	VkPipelineColorBlendStateCreateInfo colorBlending = {};
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	VkPipelineDynamicStateCreateInfo dynamicState = {};



public:
	VulkanGraphicsPipeline();
	virtual ~VulkanGraphicsPipeline();


	void Init();

	void Destroy();
private:

	void createRenderPass();

	void SetupShaderStageCreateInfo();


	void SetupVertexInputStateCreateInfo();

	void SetupInputAssemblyStateCreateInfo();


	void SetupViewportStateCreateInfo();


	void SetupRasterizationStateCreateInfo();


	void SetupMultisampleStateCreateInfo();


	void SetupColorBlendStateCreateInfo();


	void createLayout();

	void createGraphicsPipeline();

private:
	VkShaderModule createShaderModule(const std::vector<char>& code);

};

