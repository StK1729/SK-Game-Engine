#pragma once
#include "OrthographicCamera.h"
#include <SK-Game-Engine/Core/TimeStep.h>
#include "SK-Game-Engine/Events/ApplicationEvents.h"
#include "SK-Game-Engine/Events/MouseEvents.h"

namespace SK_Game_Engine
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = true);
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);
		inline OrthographicCamera& GetCamera() { return m_Camera; };
		inline const OrthographicCamera& GetCamera() const { return m_Camera; };

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		float m_AspectRatio;
		float m_ZoomLevel;
		glm::vec3 m_CameraPosition;
		float m_CameraRotation;
		float m_CameraTranslationSpeed;
		float m_CameraRotationSpeed;
		bool m_Rotation;
		OrthographicCamera m_Camera;
	};
}
