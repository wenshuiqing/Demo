#include "VulkanWindow.h"
#include "VulkanDevice.h"

VulkanWindow * VulkanWindow::instance = 0;
VulkanWindow::VulkanWindow()
{
	
}


VulkanWindow::~VulkanWindow()
{
}

VulkanWindow* VulkanWindow::GetInstance()
{
	if (instance == nullptr)
		instance = new VulkanWindow();
	return instance;
}

void VulkanWindow::Init()
{
	initWindow();
	manager.Init();
}

void VulkanWindow::Update()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		manager.DrawFrame();
	}
	vkDeviceWaitIdle(VulkanDevice::GetInstance()->device);
}

void VulkanWindow::Destroy()
{
	manager.Destroy();
	glfwDestroyWindow(window);
	glfwTerminate();
}

void VulkanWindow::initWindow()
{
	if (window != nullptr)return;
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

