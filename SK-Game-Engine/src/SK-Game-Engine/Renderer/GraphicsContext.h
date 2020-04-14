#pragma once

namespace SK_Game_Engine
{
	class SKGE_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
