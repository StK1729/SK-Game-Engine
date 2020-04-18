#include "pch.h"
#include "WindowsInput.h"
#include <GLFW/glfw3.h>
#include "SK-Game-Engine/Application.h"

namespace SK_Game_Engine {

	std::unique_ptr<Input> Input::s_Instance = std::make_unique<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<double, double> WindowsInput::GetMouseCursorPosImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { xpos, ypos };
	}

	double WindowsInput::GetMousePosXImpl()
	{
		auto[xpos, ypos] = GetMouseCursorPosImpl();
		return xpos;
	}

	double WindowsInput::GetMousePosYImpl()
	{
		auto [xpos, ypos] = GetMouseCursorPosImpl();
		return ypos;
	}

}
