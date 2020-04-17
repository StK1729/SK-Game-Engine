#include "pch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace SK_Game_Engine
{
	VertexArray* VertexArray::Create()
	{
		RendererAPI::API rendererApi = Renderer::GetRendererAPI();
		switch (rendererApi) {
			case RendererAPI::API::None:
			{
				SKGE_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
			{
				return new OpenGLVertexArray();
			}
			default:
			{
				SKGE_CORE_ASSERT(false, "Unknown Renderer API.");
				return nullptr;
			}
		}
	}
}
