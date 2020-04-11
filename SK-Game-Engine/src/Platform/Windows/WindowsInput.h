#pragma once
#include "SK-Game-Engine/Input.h"

namespace SK_Game_Engine
{
	
	class SKGE_API WindowsInput : public Input
	{
	protected:
		bool IsKeyPressedImpl(int keycode) override;
		bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<double, double> GetMouseCursorPosImpl() override;
		double GetMousePosXImpl() override;
		double GetMousePosYImpl() override;
	};
}
