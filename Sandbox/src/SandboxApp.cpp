#include <SKGE.h>
#include <memory>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"


class ExampleLayer : public SK_Game_Engine::Layer
{
public:
	ExampleLayer() : Layer("Example"),
		m_Camera{ -1.6f, 1.6f, -0.9f, 0.9f },
		m_CameraPosiition{ 0.0f },
		m_CameraMoveSpeed{ 5.0f },
		m_CameraRotation{ 0.0f },
		m_CameraRotationSpeed{ 180.0f }
	{
		std::string vertexSrc = R"(
		#version 450 core
		layout(location = 0) in vec3 v_Position;
		layout(location = 1) in vec4 v_Color;

		uniform mat4 u_ViewProjectionMatrix;
		uniform mat4 u_TransformationMatrix;

		out vec3 o_Position;
		out vec4 o_Color;
		void main()
		{
			o_Position = v_Position;
			o_Color = v_Color;
			gl_Position = u_ViewProjectionMatrix * u_TransformationMatrix *vec4(v_Position, 1.0);
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

		std::string squareVertexSrc = R"(
		#version 450 core
		layout(location = 0) in vec3 v_Position;
		layout(location = 1) in vec4 v_Color;

		uniform mat4 u_ViewProjectionMatrix;
		uniform mat4 u_TransformationMatrix;

		out vec3 o_Position;
		out vec4 o_Color;
		void main()
		{
			o_Position = v_Position;
			o_Color = v_Color;
			gl_Position = u_ViewProjectionMatrix * u_TransformationMatrix *vec4(v_Position, 1.0);
		})";

		std::string squareFragmentSrc = R"(
		#version 450 core
		layout(location = 0) out vec4 v_Color;
		in vec3 o_Position;
		in vec4 o_Color;
		void main()
		{
			v_Color = vec4(0.3, 0.2, 0.8, 1.0);
		})";

		m_Shader = std::make_shared<SK_Game_Engine::Shader>(vertexSrc, fragmentSrc);
		m_SquareShader = std::make_shared<SK_Game_Engine::Shader>( squareVertexSrc, squareFragmentSrc);
		m_VertexArray = std::shared_ptr<SK_Game_Engine::VertexArray>(SK_Game_Engine::VertexArray::Create());
		m_SquareVertexArray = std::shared_ptr<SK_Game_Engine::VertexArray>(SK_Game_Engine::VertexArray::Create());
		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		float squareVertices[] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.1f, 1.0f, 1.0f, 1.0f
		};
		std::shared_ptr<SK_Game_Engine::VertexBuffer> vertexBuffer = std::shared_ptr<SK_Game_Engine::VertexBuffer>(SK_Game_Engine::VertexBuffer::Create(vertices, sizeof(vertices)));
		std::shared_ptr<SK_Game_Engine::VertexBuffer> squareVertexBuffer = std::shared_ptr<SK_Game_Engine::VertexBuffer>(SK_Game_Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		vertexBuffer->SetLayout(SK_Game_Engine::BufferLayout
			{
				{ SK_Game_Engine::ShaderDataType::Float3, "v_Position"},
				{ SK_Game_Engine::ShaderDataType::Float4, "v_Color"}
			});

		squareVertexBuffer->SetLayout(SK_Game_Engine::BufferLayout
			{
				{ SK_Game_Engine::ShaderDataType::Float3, "v_Position"},
				{ SK_Game_Engine::ShaderDataType::Float4, "v_Color"}
			});

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
		uint32_t indices[] = { 0,1,2 };
		std::shared_ptr<SK_Game_Engine::IndexBuffer> indexBuffer = std::shared_ptr<SK_Game_Engine::IndexBuffer>(SK_Game_Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->AddIndexBuffer(indexBuffer);
		uint32_t squareIndices[] = { 0,1,2, 2,3,0 };
		std::shared_ptr<SK_Game_Engine::IndexBuffer> squareIndexBuffer = std::shared_ptr<SK_Game_Engine::IndexBuffer>(SK_Game_Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->AddIndexBuffer(squareIndexBuffer);
	}

	void OnUpdate(const SK_Game_Engine::Timestep& timestep) override
	{
		float timeInSeconds = timestep.GetSeconds();
		if (SK_Game_Engine::Input::IsKeyPressed(SKGE_KEY_LEFT)) {
			m_CameraPosiition.x -= m_CameraMoveSpeed * timeInSeconds;
		}
		else if (SK_Game_Engine::Input::IsKeyPressed(SKGE_KEY_RIGHT)) {
			m_CameraPosiition.x += m_CameraMoveSpeed * timeInSeconds;
		}

		if (SK_Game_Engine::Input::IsKeyPressed(SKGE_KEY_DOWN)) {
			m_CameraPosiition.y -= m_CameraMoveSpeed * timeInSeconds;
		}
		else if (SK_Game_Engine::Input::IsKeyPressed(SKGE_KEY_UP)) {
			m_CameraPosiition.y += m_CameraMoveSpeed * timeInSeconds;
		}

		if (SK_Game_Engine::Input::IsKeyPressed(SKGE_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed * timeInSeconds;
		}

		if (SK_Game_Engine::Input::IsKeyPressed(SKGE_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed * timeInSeconds;
		}

		// glClearColor(0.2f, 0.3f, 0.8f, 1.0f); make it black instead
		SK_Game_Engine::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		SK_Game_Engine::RenderCommand::Clear();
		m_Camera.SetPosition(m_CameraPosiition);
		m_Camera.SetRotation(m_CameraRotation);
		SK_Game_Engine::Renderer::BeginScene(m_Camera);
		static glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(0.1f));
		for (int j = 0; j < 20; ++j) {
			for (int i = 0; i < 20; ++i) {
				glm::vec3 position{ -1.65f + i * 0.11f, 0.8f - j * 0.11f, 0.0f };
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
				SK_Game_Engine::Renderer::Submit(m_SquareShader, m_SquareVertexArray, transform);
			}
		}
		//SK_Game_Engine::Renderer::Submit(m_Shader, m_VertexArray);
		SK_Game_Engine::Renderer::EndScene();
	}

	void OnEvent(SK_Game_Engine::Event& event) override
	{
	}



	void OnImGuiRender() override
	{
	}
private:
	std::shared_ptr<SK_Game_Engine::Shader> m_Shader;
	std::shared_ptr<SK_Game_Engine::Shader> m_SquareShader;
	std::shared_ptr<SK_Game_Engine::VertexArray> m_VertexArray;
	std::shared_ptr<SK_Game_Engine::VertexArray> m_SquareVertexArray;
	SK_Game_Engine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosiition;
	float m_CameraMoveSpeed;
	float m_CameraRotation;
	float m_CameraRotationSpeed;
};

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}

class Sandbox : public SK_Game_Engine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

SK_Game_Engine::Application* SK_Game_Engine::CreateApplication()
{
	return new Sandbox();
}