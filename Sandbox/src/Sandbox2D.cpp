#include "Sandbox2D.h"
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D")
	, m_CameraController{ 1280.0f / 720.0f }
	, m_Color{ 0.2f, 0.3f, 0.8f, 1.0f }
	, m_ShaderLibrary{ std::make_unique<SK_Game_Engine::ShaderLibrary>() }
{
}

void Sandbox2D::OnAttach()
{

	m_ShaderLibrary->Add(SK_Game_Engine::Shader::Create("SquareVertexShader", "assets/shaders/SquareShaders.glsl"));
	m_VertexArray = SK_Game_Engine::Ref<SK_Game_Engine::VertexArray>(SK_Game_Engine::VertexArray::Create());

	float squareVertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f, 
		0.5f, 0.5f, 0.0f, 
		-0.5f, 0.5f, 0.0f
	};

	SK_Game_Engine::Ref<SK_Game_Engine::VertexBuffer> squareVertexBuffer = SK_Game_Engine::Ref<SK_Game_Engine::VertexBuffer>(SK_Game_Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));


	squareVertexBuffer->SetLayout(SK_Game_Engine::BufferLayout
		{
			{ SK_Game_Engine::ShaderDataType::Float3, "v_Position"},
		});
	m_VertexArray->AddVertexBuffer(squareVertexBuffer);
	uint32_t squareIndices[] = { 0,1,2, 2,3,0 };
	SK_Game_Engine::Ref<SK_Game_Engine::IndexBuffer> squareIndexBuffer = SK_Game_Engine::Ref<SK_Game_Engine::IndexBuffer>(SK_Game_Engine::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_VertexArray->AddIndexBuffer(squareIndexBuffer);


}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(const SK_Game_Engine::Timestep& ts)
{
	m_CameraController.OnUpdate(ts);
	SK_Game_Engine::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	SK_Game_Engine::RenderCommand::Clear();
	SK_Game_Engine::Renderer::BeginScene(m_CameraController.GetCamera());
	static glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(0.1f));
	SK_Game_Engine::Ref<SK_Game_Engine::Shader> shader = m_ShaderLibrary->Get("SquareVertexShader");
	shader->Bind();
	shader->UploadUniformFloat4("u_Color", m_Color);
	for (int j = 0; j < 20; ++j) {
		for (int i = 0; i < 20; ++i) {
			glm::vec3 position{ -1.65f + i * 0.11f, 0.8f - j * 0.11f, 0.0f };
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
			SK_Game_Engine::Renderer::Submit(shader, m_VertexArray, transform);
		}
	}
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
	ImGui::End();
}

void Sandbox2D::OnEvent(SK_Game_Engine::Event& event)
{
	m_CameraController.OnEvent(event);
}
