#pragma once

#include "Core.h"
#include "Window.h"

namespace SK_Gaming_Engine {

	SKGE_API class Application {
	public:
		SKGE_API Application();
		SKGE_API virtual ~Application();
		SKGE_API void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication();
}