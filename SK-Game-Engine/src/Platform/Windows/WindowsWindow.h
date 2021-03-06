#pragma once

#include "SK-Game-Engine/Core/Window.h"
#include "SK-Game-Engine/Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace SK_Game_Engine {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		inline void* GetNativeWindow() const override { return m_Window; }

		// Window attributes 
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;
		struct WindowData
		{
			std::string Title = "";
			unsigned int Width = 0, Height = 0;
			bool VSync = false;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}

