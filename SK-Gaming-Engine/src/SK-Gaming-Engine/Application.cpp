#include "Application.h"
#include "Log.h";
#include <iostream>
#include "Events/Event.h"
#include "Events/ApplicationEvents.h"

namespace SK_Gaming_Engine {

	Application::Application() 
	{

	}

	Application::~Application()
	{

	}
	void Application::Run() 
	{
		WindowResizeEvent e(1200,720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			SKGE_CORE_TRACE(e);
		}
		if (!e.IsInCategory(EventCategoryInput))
		{
			SKGE_CORE_TRACE(e);
		}
		std::cin.get();
	}
}