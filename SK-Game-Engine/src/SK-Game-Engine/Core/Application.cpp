#include "pch.h"
#include "Application.h"
#include "Log.h"
#include "Input.h"
#include "SK-Game-Engine/Renderer/Renderer.h"
#include <GLFW/glfw3.h> // temporary until platform is configured.

namespace SK_Game_Engine {

#define BIND_EVENT_FN(x) std::bind(&x , this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
		: m_Window{ Ref<Window>(Window::Create()) }
		, m_LastFrameTime{ 0.0f }
		, m_Running{ true }
		, m_Minimized{ false }
	{
		SKGE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new SK_Game_Engine::ImGuiLayer();
		PushLayer(m_ImGuiLayer);
	}

	Application::~Application()
	{
		std::cout << "Deleting Application!!!" << std::endl;
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
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
		// SKGE_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled()) {
				break;
			}
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}


	void Application::Run()
	{
		auto [x, y] = Input::GetMouseCursorPos();
		while (m_Running)
		{
			float time = (float)glfwGetTime();
			Timestep timestep{ time - m_LastFrameTime };
			m_LastFrameTime = time;

			if (!m_Minimized) {
				for (Layer* layer : m_LayerStack) {
					layer->OnUpdate(timestep);
				}

				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack) {
					layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}
}