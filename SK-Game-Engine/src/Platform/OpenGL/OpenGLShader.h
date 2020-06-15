#pragma once
#include "SK-Game-Engine/Renderer/Shader.h"
#include <unordered_map>
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace SK_Game_Engine
{
	class OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& filepath);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		void SetMat3(const std::string& name, const glm::mat3& matrix) override;
		void SetMat4(const std::string& name, const glm::mat4& matrix) override;
		void SetInt(const std::string& name, int value) override;
		void SetFloat(const std::string& name, float value) override;
		void SetFloat2(const std::string& name, const glm::vec2& vector) override;
		void SetFloat3(const std::string& name, const glm::vec3& vector) override;
		void SetFloat4(const std::string& name, const glm::vec4& vector) override;
		inline const std::string& GetName() const override { return m_Name; };
		inline void SetName(const std::string& name) override { m_Name = name; };
	private:
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		uint32_t m_RendererId;
	};
}
