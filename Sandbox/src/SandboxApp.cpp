#include <SKGE.h>
#include <SK-Game-Engine/Core/EntryPoint.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include "Sandbox2D.h"


class ExampleLayer : public SK_Game_Engine::Layer
{
public:
	ExampleLayer() : Layer("Example"),
		m_CameraController{ 1280.0f / 720.0f },
		m_Color{ 0.2f, 0.3f, 0.8f, 1.0f },
		m_ShaderLibrary{ std::make_unique<SK_Game_Engine::ShaderLibrary>() }
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

		uniform mat4 u_ViewProjectionMatrix;
		uniform mat4 u_TransformationMatrix;

		out vec3 o_Position;
		void main()
		{
			o_Position = v_Position;
			gl_Position = u_ViewProjectionMatrix * u_TransformationMatrix *vec4(v_Position, 1.0);
		})";

		std::string squareFragmentSrc = R"(
		#version 450 core
		layout(location = 0) out vec4 v_Color;
		in vec3 o_Position;
		uniform vec4 u_Color;
		void main()
		{
			v_Color = u_Color;
		})";

		// m_Shader = SK_Game_Engine::Ref<SK_Game_Engine::Shader>(SK_Game_Engine::Shader::Create(vertexSrc, fragmentSrc));
		m_ShaderLibrary->Load("assets/shaders/TextureShaders.glsl");
		m_SquareShader = SK_Game_Engine::Shader::Create("SquareVertexShader", squareVertexSrc, squareFragmentSrc);
		m_VertexArray = SK_Game_Engine::VertexArray::Create();
		m_SquareVertexArray = SK_Game_Engine::VertexArray::Create();
		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		float squareVertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
		};
		SK_Game_Engine::Ref<SK_Game_Engine::VertexBuffer> vertexBuffer = SK_Game_Engine::Ref<SK_Game_Engine::VertexBuffer>(SK_Game_Engine::VertexBuffer::Create(vertices, sizeof(vertices)));
		SK_Game_Engine::Ref<SK_Game_Engine::VertexBuffer> squareVertexBuffer = SK_Game_Engine::Ref<SK_Game_Engine::VertexBuffer>(SK_Game_Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		vertexBuffer->SetLayout(SK_Game_Engine::BufferLayout
			{
				{ SK_Game_Engine::ShaderDataType::Float3, "v_Position"},
				{ SK_Game_Engine::ShaderDataType::Float4, "v_Color"}
			});

		uint32_t indices[] = { 0,1,2 };
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		SK_Game_Engine::Ref<SK_Game_Engine::IndexBuffer> indexBuffer = SK_Game_Engine::Ref<SK_Game_Engine::IndexBuffer>(SK_Game_Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->AddIndexBuffer(indexBuffer);

		squareVertexBuffer->SetLayout(SK_Game_Engine::BufferLayout
			{
				{ SK_Game_Engine::ShaderDataType::Float3, "v_Position"},
				{ SK_Game_Engine::ShaderDataType::Float2, "v_TexCoord"}
			});

		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
		uint32_t squareIndices[] = { 0,1,2, 2,3,0 };
		SK_Game_Engine::Ref<SK_Game_Engine::IndexBuffer> squareIndexBuffer = SK_Game_Engine::Ref<SK_Game_Engine::IndexBuffer>(SK_Game_Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->AddIndexBuffer(squareIndexBuffer);



		m_Texture = SK_Game_Engine::Texture2D::Create("assets/textures/ChernoCheckerboard.png");
		m_LogoTexture = SK_Game_Engine::Texture2D::Create("assets/textures/ChernoLogo.png");

		auto textureShader = m_ShaderLibrary->Get("TextureShaders");
		textureShader->Bind();
		textureShader->SetInt("u_Texture", 0);
	}

	void OnUpdate(const SK_Game_Engine::Timestep& timestep) override
	{
		m_CameraController.OnUpdate(timestep);
		// glClearColor(0.2f, 0.3f, 0.8f, 1.0f); make it black instead
		SK_Game_Engine::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
		SK_Game_Engine::RenderCommand::Clear();
		SK_Game_Engine::Renderer::BeginScene(m_CameraController.GetCamera());
		static glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(0.1f));
		m_SquareShader->Bind();
		m_SquareShader->SetFloat4("u_Color", m_Color);
		for (int j = 0; j < 20; ++j) {
			for (int i = 0; i < 20; ++i) {
				glm::vec3 position{ -1.65f + i * 0.11f, 0.8f - j * 0.11f, 0.0f };
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
				SK_Game_Engine::Renderer::Submit(m_SquareShader, m_SquareVertexArray, transform);
			}
		}
		// Triangle
		//SK_Game_Engine::Renderer::Submit(m_Shader, m_VertexArray);
		m_Texture->Bind();
		SK_Game_Engine::Renderer::Submit(m_ShaderLibrary->Get("TextureShaders"), m_SquareVertexArray, glm::scale(glm::mat4(1), glm::vec3(1.5f)));
		m_LogoTexture->Bind();
		SK_Game_Engine::Renderer::Submit(m_ShaderLibrary->Get("TextureShaders"), m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		SK_Game_Engine::Renderer::EndScene();
	}

	void OnEvent(SK_Game_Engine::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
		ImGui::End();

	}

private:
	SK_Game_Engine::Ref<SK_Game_Engine::Shader> m_Shader;
	SK_Game_Engine::Ref<SK_Game_Engine::Shader> m_SquareShader;
	SK_Game_Engine::Ref<SK_Game_Engine::VertexArray> m_VertexArray;
	SK_Game_Engine::Ref<SK_Game_Engine::Texture2D> m_Texture, m_LogoTexture;
	SK_Game_Engine::Ref<SK_Game_Engine::VertexArray> m_SquareVertexArray;
	SK_Game_Engine::Scope<SK_Game_Engine::ShaderLibrary> m_ShaderLibrary;
	SK_Game_Engine::OrthographicCameraController m_CameraController;
	glm::vec4 m_Color;
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
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};

SK_Game_Engine::Application* SK_Game_Engine::CreateApplication()
{
	return new Sandbox();
}