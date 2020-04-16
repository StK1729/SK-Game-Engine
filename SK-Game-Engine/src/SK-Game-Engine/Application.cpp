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
		out vec3 o_Position;
		void main()
		{
			o_Position = v_Position;
			gl_Position = vec4(v_Position, 1.0);
		})";
		std::string fragmentSrc = R"(
		#version 450 core
		layout(location = 0) out vec4 v_Color;
		in vec3 o_Position;
		void main()
		{
			v_Color = vec4(o_Position + 0.5, 1.0);
		})";
		m_Shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		

		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		m_VertexBuffer = std::unique_ptr<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "v_Position"} 
		};

		uint32_t index = 0;
		#pragma warning( push )
		#pragma warning(disable:4312)
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.Count, ShaderDataTypeToOpenGLType(element.Type), element.Normalized ? GL_TRUE: GL_FALSE, layout.GetStride(), reinterpret_cast<const void*>(element.Offset));
			++index;
		}
		#pragma warning( pop )
		uint32_t indices[] = { 0,1,2 };
		m_IndexBuffer = std::unique_ptr<IndexBuffer>(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
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
			glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Shader->Bind();

			// glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
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