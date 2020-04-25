#include "pch.h"
#include "Shader.h"
#include "SK-Game-Engine/Renderer/RendererAPI.h"
#include "SK-Game-Engine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace SK_Game_Engine 
{
	Shader* Shader::Create(const std::string vertexSrc, const std::string fragmentSrc)
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
				return new OpenGLShader( vertexSrc, fragmentSrc);
			}
			default:
			{
				SKGE_CORE_ASSERT(false, "Unknown Renderer API.");
				return nullptr;
			}
		}
	}
}