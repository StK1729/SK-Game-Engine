#pragma once
#include "SK-Game-Engine/Core/Core.h"
#include "SK-Game-Engine/Renderer/VertexArray.h"

namespace SK_Game_Engine
{
	class SKGE_API OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		void Bind() override;
		void Unbind() override;
		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		void AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
		inline const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() override { return  m_VertexBuffers; };
		inline const Ref<IndexBuffer>& GetIndexBuffer() override { return m_IndexBuffer; };
	private:
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererId;
	};
}