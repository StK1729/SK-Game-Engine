#include "Application.h"
#include <iostream>
namespace SK_Gaming_Engine {

	Application::Application() 
	{

	}

	Application::~Application()
	{

	}
	void Application::Run() 
	{
		std::cout << "This works" << std::endl;
		std::cin.get();
	}
}