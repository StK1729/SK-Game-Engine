#include "pch.h"
#include "Application.h"
#include "Log.h"
#include <glad/glad.h>

namespace SK_Gaming_Engine {

#define BIND_EVENT_FN(x) std::bind(&x , this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	Application::Application() 
	{
		SKGE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
		SKGE_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled()) {
				break;
			}
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	
	void Application::Run() 
	{
		while (m_Running)
		{
			glClear(GL_COLOR_BUFFER_BIT);
			glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
			m_Window->OnUpdate();
		}
	}
}