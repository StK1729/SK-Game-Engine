#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvents.h"

namespace SK_Gaming_Engine {

	SKGE_API class Application {
	public:
		SKGE_API Application();
		SKGE_API virtual ~Application();
		SKGE_API void Run();
		void OnEvent(Event& e);
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication();
}