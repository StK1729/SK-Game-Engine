#pragma once
#include "SK-Game-Engine/Core.h"
#include "RendererAPI.h"
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"
#include <glm/glm.hpp>

namespace SK_Game_Engine
{

	class SKGE_API Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetRendererAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static std::unique_ptr<SceneData> s_SceneData;
	};
}
