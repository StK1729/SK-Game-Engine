#pragma once
#include <string>
#include "SK-Game-Engine/Core.h"
#include <glm/glm.hpp>

namespace SK_Game_Engine {
	class SKGE_API Shader {
	public:
		Shader(const std::string vertexSrc, const std::string frahmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererId;
	};

}
