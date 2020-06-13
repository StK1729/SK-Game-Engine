#include "pch.h"
#include "OrthographicCameraController.h"
#include <SK-Game-Engine\KeyCodes.h>
#include <SK-Game-Engine\Input.h>

namespace SK_Game_Engine
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_AspectRatio{ aspectRatio }
		, m_ZoomLevel{ 1.0f }
		, m_CameraPosition{ 0.0f, 0.0f , 0.0f }
		, m_CameraRotation{ 0.0f }
		, m_CameraTranslationSpeed{ 10.0f }
		, m_CameraRotationSpeed{ 180.0f }
		, m_Camera{ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }
		, m_Rotation{ rotation }
	{

	}
	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		float timeInSeconds = ts.GetSeconds();
		if (Input::IsKeyPressed(SKGE_KEY_A) || Input::IsKeyPressed(SKGE_KEY_LEFT)) {
			m_CameraPosition.x -= m_CameraTranslationSpeed * timeInSeconds;
		} else if (Input::IsKeyPressed(SKGE_KEY_D) || Input::IsKeyPressed(SKGE_KEY_RIGHT)) {
			m_CameraPosition.x += m_CameraTranslationSpeed * timeInSeconds;
		}

		if (Input::IsKeyPressed(SKGE_KEY_S) || Input::IsKeyPressed(SKGE_KEY_DOWN)) {
			m_CameraPosition.y -= m_CameraTranslationSpeed * timeInSeconds;
		} else if (Input::IsKeyPressed(SKGE_KEY_W) || Input::IsKeyPressed(SKGE_KEY_UP)) {
			m_CameraPosition.y += m_CameraTranslationSpeed * timeInSeconds;
		}

		if (m_Rotation) {
			if (Input::IsKeyPressed(SKGE_KEY_Q)) {
				m_CameraRotation += m_CameraRotationSpeed * timeInSeconds;
			}

			if (Input::IsKeyPressed(SKGE_KEY_E)) {
				m_CameraRotation -= m_CameraRotationSpeed * timeInSeconds;
			}

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);
		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(SKGE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(SKGE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYOffset();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / e.GetHeight();
		return false;
	}
}