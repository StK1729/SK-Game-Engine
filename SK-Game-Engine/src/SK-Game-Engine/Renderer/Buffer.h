#pragma once
#include "SK-Game-Engine/Core/Core.h"

namespace SK_Game_Engine
{

	enum class ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	struct BufferElement
	{
	public:
		BufferElement()
			: Name{ "" }, Type{ ShaderDataType::Float }, Size{ 0 }, Count{ 0 }, Offset{ 0 }, Normalized{ false }
		{}
		BufferElement(ShaderDataType type, const std::string name, bool  normalized = false)
			: Name{ name }, Type{ type }, Size{ 0 }, Count{ 0 }, Offset{ 0 }, Normalized{ normalized }
		{
			switch (type) {
				case ShaderDataType::Float:
				case ShaderDataType::Int:
				{
					Size = 4;
					Count = 1;
					break;
				}
				case ShaderDataType::Float2:
				case ShaderDataType::Int2:
				{
					Size = 8;
					Count = 2;
					break;
				}
				case ShaderDataType::Float3:
				case ShaderDataType::Int3:
				{
					Size = 12;
					Count = 3;
					break;
				}
				case ShaderDataType::Float4:
				case ShaderDataType::Int4:
				{
					Size = 16;
					Count = 4;
					break;
				}
				case ShaderDataType::Mat3:
				{
					Size = 4 * 3 * 3;
					Size = 3 * 3;
					break;
				}
				case ShaderDataType::Mat4:
				{
					Size = 4 * 4 * 4;
					Size = 4 * 4;
					break;
				}
				case ShaderDataType::Bool:
				{
					Size = 1;
					Count = 1;
					break;
				}
			}
		}
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		uint32_t Count;
		bool Normalized;
	};

	class SKGE_API BufferLayout
	{
	public:
		BufferLayout()
			: m_Elements{ std::vector<BufferElement>() }, m_Stride{ 0 }
		{}
		BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements{ elements }
		{
			CalculateOffsetAndStride();
		}

		BufferLayout(std::vector<BufferElement>& elements) : m_Elements{ elements }
		{
			CalculateOffsetAndStride();
		}

		BufferLayout(std::vector<BufferElement>&& elements) : m_Elements{ std::move(elements) }
		{
			CalculateOffsetAndStride();
		}

		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		inline uint32_t GetStride() const { return m_Stride; }
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.cbegin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.cend(); }
	private:
		inline void CalculateOffsetAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (BufferElement& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type) {
			case ShaderDataType::Float:
			case ShaderDataType::Int:
			{
				return 4;
			}
			case ShaderDataType::Float2:
			case ShaderDataType::Int2:
			{
				return 8;
			}
			case ShaderDataType::Float3:
			case ShaderDataType::Int3:
			{
				return 12;
			}
			case ShaderDataType::Float4:
			case ShaderDataType::Int4:
			{
				return 16;
			}
			case ShaderDataType::Mat3:
			{
				return 4 * 3 * 3;
			}
			case ShaderDataType::Mat4:
			{
				return 4 * 4 * 4;
			}
			case ShaderDataType::Bool:
			{
				return 1;
			}
		}

		SKGE_CORE_ASSERT(false, "Unknown ShaderDataType");
		return 0;
	}

	class SKGE_API VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;
		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class SKGE_API IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32_t GetCount() const = 0;
		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};

}
