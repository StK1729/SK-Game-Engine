#include "pch.h"
#include "OpenGLShader.h"
#include "SK-Game-Engine/Core/Core.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>

namespace SK_Game_Engine
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") {
			return GL_VERTEX_SHADER;
		}
		if (type == "fragment") {
			return GL_FRAGMENT_SHADER;
		}
		SKGE_CORE_ASSERT(false, "Invalid shader type");
		return 0;
	}

	// This is just temporary until the proper file system is built. This clearly violates Separation of Concerns.
	static std::string ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in) {
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else {
			SKGE_CORE_ASSERT("Could not open filepath '{0}'", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			SKGE_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			SKGE_CORE_ASSERT(ShaderTypeFromString(type), "Invalid type specified");
			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}
		return shaderSources;
	}


	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
		: m_RendererId{ 0 }
	{
		m_Name = name;
		std::unordered_map<GLenum, std::string> shaderSources{ {GL_VERTEX_SHADER, vertexSource}, {GL_FRAGMENT_SHADER, fragmentSource } };
		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
		: m_RendererId{ 0 }
	{
		std::string shaderSource = ReadFile(filepath);
		std::unordered_map<GLenum, std::string> shaderSources = PreProcess(shaderSource);
		Compile(shaderSources);
		auto lastSlash = filepath.find_last_of('/');
		lastSlash = lastSlash == std::string::npos ? 0 : ++lastSlash;
		auto lastDot = filepath.rfind('.');
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& filepath)
		: m_RendererId{ 0 }
	{
		std::string shaderSource = ReadFile(filepath);
		std::unordered_map<GLenum, std::string> shaderSources = PreProcess(shaderSource);
		Compile(shaderSources);
		m_Name = name;
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererId);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererId);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		int location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		int location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		int location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		int location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& vector)
	{
		int location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform2f(location, vector.x, vector.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& vector)
	{
		int location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& vector)
	{
		int location = glGetUniformLocation(m_RendererId, name.c_str());
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		std::vector<GLuint> shaderIds;
		shaderIds.reserve(shaderSources.size());
		uint32_t program = glCreateProgram();
		for (const std::pair<GLenum, std::string>& keyValuePair : shaderSources) {
			GLenum type = keyValuePair.first;
			const std::string& shaderSource = keyValuePair.second;
			// Read our shader into the appropriate buffers

			// Create an empty shader handle
			GLuint shader = glCreateShader(type);

			// Send the shader's source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* source = (const GLchar*)shaderSource.c_str();
			glShaderSource(shader, 1, &source, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				SKGE_CORE_ERROR("{0}", infoLog.data());
				SKGE_CORE_ASSERT(false, "Shader compilation failure!");
				return;
			}
			// Attach our shader to our program
			glAttachShader(program, shader);
			shaderIds.push_back(shader);
		}

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto shaderId : shaderIds) {
				glDeleteShader(shaderId);
			}

			SKGE_CORE_ERROR("{0}", infoLog.data());
			SKGE_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		for (auto shaderId : shaderIds) {
			glDetachShader(m_RendererId, shaderId);
		}

		m_RendererId = program;
	}

}