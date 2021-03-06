#pragma once
#include "SK-Game-Engine/Renderer/Texture.h"

namespace SK_Game_Engine
{
	class OpenGLTexture : public Texture2D
	{
	public:
		OpenGLTexture(const std::string& path);
		OpenGLTexture(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture();
		void SetData(void* data, uint32_t size) override;
		inline uint32_t GetWidth() const override { return m_Width; };
		uint32_t GetHeight() const override { return m_Height; }
		void Bind(uint32_t slot = 0) const override;

	private:
		std::string m_Path;
		uint32_t m_Width;
		uint32_t m_Height;
		uint32_t m_RendererId;
		uint32_t m_DataFormat;
		uint32_t m_InternalFormat;
	};
}
