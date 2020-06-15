#include "pch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace SK_Game_Engine
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
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
				return std::make_shared<OpenGLTexture>(path);
			}
			default:
			{
				SKGE_CORE_ASSERT(false, "Unknown Renderer API.");
				return nullptr;
			}
		}
	}
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
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
			return std::make_shared<OpenGLTexture>(width, height);
		}
		default:
		{
			SKGE_CORE_ASSERT(false, "Unknown Renderer API.");
			return nullptr;
		}
		}
	}
}