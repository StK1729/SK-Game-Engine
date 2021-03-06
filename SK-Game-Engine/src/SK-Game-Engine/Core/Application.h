#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "SK-Game-Engine/Events/ApplicationEvents.h"
#include "SK-Game-Engine/ImGui/ImGuiLayer.h"
#include "SK-Game-Engine/Core/TimeStep.h"


namespace SK_Game_Engine {

	class SKGE_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		static Application* s_Instance;
		Ref<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running;
		LayerStack m_LayerStack;
		float m_LastFrameTime;
		bool m_Minimized;
	};

	Application* CreateApplication();
}