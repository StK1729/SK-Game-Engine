#pragma once
#include "Core.h"

namespace SK_Game_Engine
{
	class SKGE_API Input 
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<double, double> GetMouseCursorPos() { return s_Instance->GetMouseCursorPosImpl(); }
		inline static double GetMousePosX() { return s_Instance->GetMousePosXImpl(); }
		inline static double GetMousePosY() { return s_Instance->GetMousePosYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<double, double> GetMouseCursorPosImpl() = 0;
		virtual double GetMousePosXImpl() = 0;
		virtual double GetMousePosYImpl() = 0;
		static std::unique_ptr<Input> s_Instance;
	};
}
