#pragma once
#include <glm/glm.hpp>
namespace SK_Game_Engine
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		inline const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position);
		inline float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation);
		void SetProjection(float left, float right, float bottom, float top);
		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		glm::vec3 m_Position;
		float m_Rotation;
	};
}
