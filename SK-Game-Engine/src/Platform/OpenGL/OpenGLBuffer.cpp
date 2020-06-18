#include "pch.h"
#include "OpenGLBuffer.h"
#include "glad/glad.h"

namespace SK_Game_Engine
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
		: m_RendererId {0}
	{
		SKGE_PROFILING_FUNCTION();

		glCreateBuffers(1, &m_RendererId);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		SKGE_PROFILING_FUNCTION();

		glDeleteBuffers(1, &m_RendererId);
	}
	void OpenGLVertexBuffer::Bind() const
	{
		SKGE_PROFILING_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	}
	void OpenGLVertexBuffer::Unbind() const
	{
		SKGE_PROFILING_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_RendererId{0}, m_Count {count}
	{
		SKGE_PROFILING_FUNCTION();

		glCreateBuffers(1, &m_RendererId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t)*count, indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		SKGE_PROFILING_FUNCTION();

		glDeleteBuffers(1, &m_RendererId);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		SKGE_PROFILING_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		SKGE_PROFILING_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}