#pragma once
#include <memory>
#include "SK-Game-Engine/Core.h"
#include "Buffer.h"

namespace SK_Game_Engine
{
	class SKGE_API VertexArray
	{
	public:
		virtual ~VertexArray() {};

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void AddIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() = 0;

		static VertexArray* Create();
	};
}