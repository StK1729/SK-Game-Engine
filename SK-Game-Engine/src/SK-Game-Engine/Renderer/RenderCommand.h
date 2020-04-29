#pragma once
#include "SK-Game-Engine/Core.h"
#include "RendererAPI.h"

namespace SK_Game_Engine
{
	class SKGE_API RenderCommand
	{
	public:
		inline static void RenderCommand::DrawIndexed(const Ref<VertexArray>& vertexArray)
		{ 
			s_RendererAPI->DrawIndexed(vertexArray); 
		}
		inline static void RenderCommand::SetClearColor(const glm::vec4& color) 
		{ 
			s_RendererAPI->SetClearColor(color); 
		}
		inline static void RenderCommand::Clear() 
		{ 
			s_RendererAPI->Clear(); 
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}
