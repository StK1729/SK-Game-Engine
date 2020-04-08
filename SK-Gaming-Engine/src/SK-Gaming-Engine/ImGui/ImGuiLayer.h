#pragma once
#include "SK-Gaming-Engine/Layer.h"
#include <imgui.h>
#include "Platform/OpenGL/ImGuiRenderer.h"

namespace SK_Gaming_Engine
{
	class SKGE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate();
		void OnEvent(Event& event);
		void OnAttach();
		void OnDetach();

	private:
		float m_Time = 0.0f;
	};
}