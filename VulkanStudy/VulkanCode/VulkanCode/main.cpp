
#include <iostream>

#include "VulkanWindow.h"


int main() {


	try
	{
		VulkanWindow::GetInstance()->Init();


		VulkanWindow::GetInstance()->Update();


		VulkanWindow::GetInstance()->Destroy();
		//app.run();
		
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;

		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}