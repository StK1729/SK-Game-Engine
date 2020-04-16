#pragma once

#include "SK-Game-Engine/Renderer/Buffer.h"

namespace SK_Game_Engine
{
	class SKGE_API OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer();
		void Bind() const override;
		void Unbind() const override;
		inline void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
		inline const BufferLayout& GetLayout() const override { return m_Layout; };
	private:
		uint32_t m_RendererId;
		BufferLayout m_Layout;
	};

	class SKGE_API OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();
		void Bind() const override;
		void Unbind() const override;
		inline uint32_t GetCount() const override { return m_Count; };
	private:
		uint32_t m_RendererId;
		uint32_t m_Count;
	};
}
