#pragma once
#include "SK-Game-Engine/Core.h"
#include "SK-Game-Engine/Renderer/RendererAPI.h"

namespace SK_Game_Engine
{
	class SKGE_API OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Clear() override;
		void SetClearColor(const glm::vec4& color) override;
		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}