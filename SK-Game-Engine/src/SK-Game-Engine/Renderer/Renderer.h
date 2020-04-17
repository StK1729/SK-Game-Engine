#pragma once
#include "SK-Game-Engine/Core.h"
#include "RendererAPI.h"
#include "RenderCommand.h"

namespace SK_Game_Engine
{

	class SKGE_API Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetRendererAPI() { return RendererAPI::GetAPI(); }
	};
}
