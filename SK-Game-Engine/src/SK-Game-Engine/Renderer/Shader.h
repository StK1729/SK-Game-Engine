#pragma once
#include <string>
#include "SK-Game-Engine/Core.h"

namespace SK_Game_Engine {
	class SKGE_API Shader {
	public:
		virtual ~Shader() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string vertexSrc, const std::string fragmentSrc);
	};

}
