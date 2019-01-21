#include "ShaderLoader.h"



ShaderLoader::ShaderLoader()
{
}


ShaderLoader::~ShaderLoader()
{
}

VkShaderModule ShaderLoader::LoadShaderModule(VkDevice device, const std::string& filename)
{
	auto shaderCode = readFile(filename);

	VkShaderModule shaderModule = createShaderModule(device,shaderCode);
	return shaderModule;
}

void ShaderLoader::Destroy(VkDevice device, VkShaderModule shaderModule)
{
	vkDestroyShaderModule(device, shaderModule, nullptr);
}

VkShaderModule ShaderLoader::createShaderModule(VkDevice device, const std::vector<char>& code)
{
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	VkShaderModule shaderModule;
	if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module!");
	}

	return shaderModule;
}

