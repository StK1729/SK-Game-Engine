#pragma once
#include "SK-Gaming-Engine/Input.h"

namespace SK_Gaming_Engine
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
