#include "pch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace SK_Game_Engine
{
	VertexArray* VertexArray::Create()
	{
		RendererAPI rendererApi = Renderer::GetRendererAPI();
		switch (rendererApi) {
			case RendererAPI::None:
			{
				SKGE_CORE_ASSERT(false, "RendererAPI::None is currently not supported.");
				return nullptr;
			}
			case RendererAPI::OpenGL:
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
