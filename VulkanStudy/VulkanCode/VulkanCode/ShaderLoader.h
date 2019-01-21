#pragma once
#include "HeaderFile.h"
#include "Loader.h"
class ShaderLoader
{
public:
	ShaderLoader();
	virtual ~ShaderLoader();

	VkShaderModule LoadShaderModule(VkDevice device, const std::string& filename);

	void Destroy(VkDevice device,VkShaderModule shaderModule);

private:
	VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);


};

