#pragma once
#include "SK-Game-Engine/Layer.h"
#include <imgui.h>
#include "Platform/OpenGL/ImGuiRenderer.h"
#include "SK-Game-Engine/Events/MouseEvents.h"
#include "SK-Game-Engine/Events/ApplicationEvents.h"
#include "SK-Game-Engine/Events/KeyEvents.h"

namespace SK_Game_Engine
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
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& е);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizedEvent(WindowResizeEvent& e);
		float m_Time = 0.0f;
	};
}