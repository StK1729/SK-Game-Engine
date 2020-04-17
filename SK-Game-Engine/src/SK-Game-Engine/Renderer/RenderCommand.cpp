#include "pch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace SK_Game_Engine
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
