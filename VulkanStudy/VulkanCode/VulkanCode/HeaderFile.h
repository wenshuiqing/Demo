#pragma once
#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>
#include <cstring>
#include <map>
#include <optional>
#include <set>
#include<algorithm>
#include <fstream>


#ifdef NDEBUG
const bool enableValidationLayers = true;
#else
const bool enableValidationLayers = true;
#endif

const  std::vector<const char*> requestLayers = {
	"VK_LAYER_LUNARG_standard_validation"
};
const std::vector<const char*> requestDeviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
const std::vector<const char*> requestInstanceExtensions = {};