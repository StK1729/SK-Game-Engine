#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Events/ApplicationEvents.h"


namespace SK_Gaming_Engine {

	SKGE_API class Application {
	public:
		SKGE_API Application();
		SKGE_API virtual ~Application();
		SKGE_API void Run();
		void OnEvent(Event& e);

		SKGE_API void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();
}