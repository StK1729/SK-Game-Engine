#include "pch.h"
#include "Application.h"
#include "Log.h"
#include <GLFW/glfw3.h>

namespace SK_Gaming_Engine {

#define BIND_EVENT_FN(x) std::bind(&x , this, std::placeholders::_1)

	Application::Application() 
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClosed));
		SKGE_CORE_TRACE("{0}", e);
	}

	Application::~Application()
	{

	}
	void Application::Run() 
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}