#pragma once
#include "SK-Game-Engine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace SK_Game_Engine
{
	class SKGE_API OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}
