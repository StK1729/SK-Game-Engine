#include "pch.h"
#include "SK-Game-Engine/Renderer/Buffer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"

namespace SK_Game_Engine
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
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
				return std::make_shared<OpenGLVertexBuffer>(vertices, size);
			}
			default:
			{
				SKGE_CORE_ASSERT(false, "Unknown Renderer API.");
				return nullptr;
			}
		}
	}
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
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
			return std::make_shared<OpenGLIndexBuffer>(indices, size);
		}
		default:
		{
			SKGE_CORE_ASSERT(false, "Unknown Renderer API.");
			return nullptr;
		}
		}
	}
}