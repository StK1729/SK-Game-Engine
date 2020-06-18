#include "pch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace SK_Game_Engine
{
	static GLenum ShaderDataTypeToOpenGLType(const ShaderDataType& element)
	{
		switch (element) {
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			{
				return GL_FLOAT;
			}
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			{
				return GL_INT;
			}
			case ShaderDataType::Mat3:
			{
				return GL_FLOAT_MAT3;
			}
			case ShaderDataType::Mat4:
			{
				return GL_FLOAT_MAT4;
			}
			case ShaderDataType::Bool:
			{
				return GL_BOOL;
			}
		}

		SKGE_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		SKGE_PROFILING_FUNCTION();

		glCreateVertexArrays(1, &m_RendererId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		SKGE_PROFILING_FUNCTION();

		glDeleteVertexArrays(1, &m_RendererId);
	}

	void OpenGLVertexArray::Bind()
	{
		SKGE_PROFILING_FUNCTION();

		glBindVertexArray(m_RendererId);
	}
	void OpenGLVertexArray::Unbind()
	{
		SKGE_PROFILING_FUNCTION();

		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		SKGE_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");
		glBindVertexArray(m_RendererId);
		vertexBuffer->Bind();
		uint32_t index = 0;
		#pragma warning( push )
		#pragma warning(disable:4312)
		const BufferLayout& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.Count, ShaderDataTypeToOpenGLType(element.Type), element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), reinterpret_cast<const void*>(element.Offset));
			++index;
		}
		#pragma warning( pop )
		m_VertexBuffers.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererId);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}
}
