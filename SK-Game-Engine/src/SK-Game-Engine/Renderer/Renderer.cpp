#include "pch.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Renderer2D.h"

namespace SK_Game_Engine
{

	Scope<Renderer::SceneData> Renderer::s_SceneData = std::make_unique<Renderer::SceneData>();

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjectionMatrix", s_SceneData->ViewProjectionMatrix);
		shader->SetMat4("u_TransformationMatrix", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}