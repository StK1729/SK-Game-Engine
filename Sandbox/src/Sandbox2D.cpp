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
	SKGE_PROFILING_FUNCTION();

	m_Texture = SK_Game_Engine::Texture2D::Create("assets/textures/ChernoCheckerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(const SK_Game_Engine::Timestep& ts)
{
	SKGE_PROFILING_FUNCTION();

	m_CameraController.OnUpdate(ts);
	SK_Game_Engine::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	SK_Game_Engine::RenderCommand::Clear();
	SK_Game_Engine::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (int j = 0; j < 20; ++j) {
		for (int i = 0; i < 20; ++i) {
			glm::vec3 position{ -1.65f + i * 0.11f, 0.8f - j * 0.11f, 0.0f };
			SK_Game_Engine::Renderer2D::DrawQuad(position, {0.1f, 0.1f}, m_Color);
		}
	}

	SK_Game_Engine::Renderer2D::DrawRotatedQuad({ 0.5f, 0.5f }, { 5.0f, 5.0f }, glm::radians(45.0f), m_Texture, 10.0f);

	SK_Game_Engine::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	SKGE_PROFILING_FUNCTION();
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Color", glm::value_ptr(m_Color));
	ImGui::End();
}

void Sandbox2D::OnEvent(SK_Game_Engine::Event& event)
{
	m_CameraController.OnEvent(event);
}
