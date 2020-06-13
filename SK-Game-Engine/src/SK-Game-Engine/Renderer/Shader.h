#pragma once
#include <string>
#include "SK-Game-Engine/Core/Core.h"
#include <glm/glm.hpp>

namespace SK_Game_Engine {
	class SKGE_API Shader {
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) = 0;
		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void UploadUniformInt(const std::string& name, int value) = 0;
		virtual void UploadUniformFloat(const std::string& name, float value) = 0;
		virtual void UploadUniformFloat2(const std::string& name, const glm::vec2& vector) = 0;
		virtual void UploadUniformFloat3(const std::string& name, const glm::vec3& vector) = 0;
		virtual void UploadUniformFloat4(const std::string& name, const glm::vec4& vector) = 0;
		virtual const std::string& GetName() const = 0;
		virtual void SetName(const std::string& name) = 0;

		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Shader::Create(const std::string& name, const std::string& filepath);
	protected:
		std::string m_Name;
	};

	class SKGE_API ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);
		Ref<Shader> Get(const std::string& name);
		inline bool Exists(const std::string& name) { return m_Shaders.find(name) != m_Shaders.end(); }
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};

}
