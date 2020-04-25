#pragma once
#include "SK-Game-Engine/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace SK_Game_Engine
{
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string vertexSrc, const std::string fragmentSrc);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& vector);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& vector);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& vector);
	private:
		uint32_t m_RendererId;
	};
}
