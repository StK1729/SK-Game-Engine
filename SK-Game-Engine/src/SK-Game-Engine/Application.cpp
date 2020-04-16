#include "pch.h"
#include "Application.h"
#include "Log.h"
#include <glad/glad.h>
#include "Input.h"
namespace SK_Game_Engine {

#define BIND_EVENT_FN(x) std::bind(&x , this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	GLenum ShaderDataTypeToOpenGLType(const ShaderDataType& element)
	{
		switch (element) {
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				return GL_FLOAT;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			{
				return GL_INT;
			}
			case ShaderDataType::Mat3:
			{
				return GL_FLOAT_MAT3;
			}
			case ShaderDataType::Mat4:
			{
				return GL_FLOAT_MAT4;
			}
			case ShaderDataType::Bool:
			{
				return GL_BOOL;
			}
		}

		SKGE_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	Application::Application()
	{
		SKGE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
		std::string vertexSrc = R"(
		#version 450 core
		layout(location = 0) in vec3 v_Position;
		layout(location = 1) in vec4 v_Color;
		out vec3 o_Position;
		out vec4 o_Color;
		void main()
		{
			o_Position = v_Position;
			o_Color = v_Color;
			gl_Position = vec4(v_Position, 1.0);
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
		m_Shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
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
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Shader->Bind();
			m_SquareVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
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