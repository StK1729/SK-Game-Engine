#pragma once
#include "SK-Game-Engine/Core/Layer.h"
#include "SK-Game-Engine/Events/MouseEvents.h"
#include "SK-Game-Engine/Events/KeyEvents.h"
#include "SK-Game-Engine/Core/KeyCodes.h"

namespace SK_Game_Engine
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}