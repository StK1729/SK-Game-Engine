#include "pch.h"
#include "Application.h"
#include "Log.h"
#include "Input.h"

namespace SK_Game_Engine {

#define BIND_EVENT_FN(x) std::bind(&x , this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
		: m_Camera {-1.6f, 1.6f, -0.9f, 0.9f}
	{
		SKGE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		std::string vertexSrc = R"(
		#version 450 core
		layout(location = 0) in vec3 v_Position;
		layout(location = 1) in vec4 v_Color;

		uniform mat4 u_ViewProjectionMatrix;

		out vec3 o_Position;
		out vec4 o_Color;
		void main()
		{
			o_Position = v_Position;
			o_Color = v_Color;
			gl_Position = u_ViewProjectionMatrix * vec4(v_Position, 1.0);
		})";
		std::string fragmentSrc = R"(
		#version 450 core
		layout(location = 0) out vec4 v_Color;
		in vec3 o_Position;
		in vec4 o_Color;
		void main()
		{
			v_Color = o_Color;
		})";
		m_Shader = std::make_shared<Shader>(vertexSrc, fragmentSrc);
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		m_VertexArray = std::shared_ptr<VertexArray>(VertexArray::Create());
		m_SquareVertexArray = std::shared_ptr<VertexArray>(VertexArray::Create());
		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		float squareVertices[] =
		{
			0.3f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			1.0f, 0.3f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			0.3f, 1.0f, 0.0f, 0.1f, 1.0f, 1.0f, 1.0f
		};
		std::shared_ptr<VertexBuffer> vertexBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));
		std::shared_ptr<VertexBuffer> squareVertexBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		vertexBuffer->SetLayout( BufferLayout
			{
				{ ShaderDataType::Float3, "v_Position"},
				{ ShaderDataType::Float4, "v_Color"}
			});

		squareVertexBuffer->SetLayout(BufferLayout
			{
				{ ShaderDataType::Float3, "v_Position"},
				{ ShaderDataType::Float4, "v_Color"}
			});

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
		uint32_t indices[] = { 0,1,2 };
		std::shared_ptr<IndexBuffer> indexBuffer = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
		m_VertexArray->AddIndexBuffer(indexBuffer);
		uint32_t squareIndices[] = { 0,1,2, 2,3,0 };
		std::shared_ptr<IndexBuffer> squareIndexBuffer = std::shared_ptr<IndexBuffer>(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->AddIndexBuffer(squareIndexBuffer);
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
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		SKGE_CORE_TRACE("{0}", e);

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


	void Application::Run()
	{
		auto [x, y] = Input::GetMouseCursorPos();
		while (m_Running)
		{
			// glClearColor(0.2f, 0.3f, 0.8f, 1.0f); make it black instead
			RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
			RenderCommand::Clear();
			//m_Camera.SetPosition({ 0.5f, 0.5f, 0.0f });
			m_Camera.SetRotation(45.0f);
			Renderer::BeginScene(m_Camera);
			Renderer::Submit(m_Shader, m_SquareVertexArray);
			Renderer::Submit(m_Shader, m_VertexArray);
			Renderer::EndScene();

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			m_Window->OnUpdate();
		}
	}
}