#pragma once
#include "SK-Game-Engine/Core.h"

namespace SK_Game_Engine
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class SKGE_API Renderer
	{
	public:
		inline static RendererAPI GetRendererAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}
