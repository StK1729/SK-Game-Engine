#pragma once
#include "SKGE.h"

class Sandbox2D : public SK_Game_Engine::Layer
{
public:
	Sandbox2D();
	~Sandbox2D() = default;
	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(const SK_Game_Engine::Timestep& ts) override;
	void OnImGuiRender() override;
	void OnEvent(SK_Game_Engine::Event& event) override;
private:
	SK_Game_Engine::OrthographicCameraController m_CameraController;
	// Temporary. It will be abstracted in 2D Renderer
	SK_Game_Engine::Ref<SK_Game_Engine::VertexArray> m_VertexArray;
	SK_Game_Engine::Ref<SK_Game_Engine::Texture2D> m_Texture;
	SK_Game_Engine::Scope<SK_Game_Engine::ShaderLibrary> m_ShaderLibrary;
	glm::vec4 m_Color;
};