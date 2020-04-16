#pragma once
#include "SK-Game-Engine/Core.h"
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
		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() override { return  m_VertexBuffers; };
		inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() override { return m_IndexBuffer; };
	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		uint32_t m_RendererId;
	};
}