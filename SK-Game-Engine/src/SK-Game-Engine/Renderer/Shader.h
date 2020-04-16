#pragma once
#include <string>
#include "SK-Game-Engine/Core.h"

namespace SK_Game_Engine {
	class SKGE_API Shader {
	public:
		Shader(const std::string vertexSrc, const std::string frahmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_RendererId;
	};

}
