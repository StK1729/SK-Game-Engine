#include "pch.h"
#include "OpenGLContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace SK_Game_Engine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle{windowHandle}
	{
		SKGE_CORE_ASSERT(m_WindowHandle, "Window handle is NULL.")
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SKGE_CORE_ASSERT(status, "Failed to initialize glad.");

		SKGE_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		SKGE_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		SKGE_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}