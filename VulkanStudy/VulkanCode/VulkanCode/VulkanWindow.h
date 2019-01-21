#pragma once

#include "HeaderFile.h"
#include "VulkanGraphicsManager.h"




class VulkanWindow
{
public:
	const int WIDTH = 800;
	const int HEIGHT = 600;


	GLFWwindow* window;
	bool framebufferResized = false;
	VulkanGraphicsManager manager;


private:
	static VulkanWindow* instance;
	VulkanWindow();
	VulkanWindow(const VulkanWindow&)=delete;
	VulkanWindow& operator=(VulkanWindow&) = delete;
	~VulkanWindow();



public:
	static VulkanWindow* GetInstance();


	void Init();

	void Update();

	void Destroy();

private:
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
		auto app = reinterpret_cast<VulkanWindow*>(glfwGetWindowUserPointer(window));
		app->framebufferResized = true;
	}

	void initWindow();
};

