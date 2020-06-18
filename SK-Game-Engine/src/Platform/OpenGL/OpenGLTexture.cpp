#include "pch.h"
#include "OpenGLTexture.h"
#include "glad/glad.h"
#include "stb_image.h"

namespace SK_Game_Engine
{
	OpenGLTexture::OpenGLTexture(const std::string& path) 
		: m_Path {path}
	{
		SKGE_PROFILING_FUNCTION();

		int width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data;
		{
			SKGE_PROFILING_SCOPE("OpenGLTexture::OpenGLTexture(const std::string & path) stbi_load");
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		}
		SKGE_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;
		switch (channels){
			case 3: {
				m_InternalFormat = GL_RGB8;
				m_DataFormat = GL_RGB;
				break;
			}
			case 4: {
				m_InternalFormat = GL_RGBA8;
				m_DataFormat = GL_RGBA;
				break;
			}
		}
		SKGE_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		glTextureStorage2D(m_RendererId, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height)
		: m_Width {width}
		, m_Height {height}
	{
		SKGE_PROFILING_FUNCTION();

		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
		
		SKGE_CORE_ASSERT(m_InternalFormat & m_DataFormat, "Format not supported!");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		glTextureStorage2D(m_RendererId, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		SKGE_PROFILING_FUNCTION();

		glDeleteTextures(1, &m_RendererId);
	}

	void OpenGLTexture::SetData(void* data, uint32_t size)
	{
		SKGE_PROFILING_FUNCTION();

		uint32_t bpc = m_DataFormat == GL_RGBA ? 4 : 3;
		SKGE_CORE_ASSERT(size == bpc * m_Width * m_Height, "Invalid size!");
		glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture::Bind(uint32_t slot) const
	{
		SKGE_PROFILING_FUNCTION();

		glBindTextureUnit(0, m_RendererId);
	}
}