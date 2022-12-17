#pragma once
#include <vector>
#include "Utilities\Debug.h"

struct VertexBufferElement
{
	uint32_t Type;
	uint32_t Count;
	uint8_t normlized;

	static uint32_t GetSizeOfType(uint32_t type)
	{
		switch (type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}

		ASSERT(false, "");
		return 0;
	}

};

class VertexBufferLayout
{

public:
	VertexBufferLayout()
		: m_Stride(0)
	{
	}

public:
	template<typename Type>
	void Push(uint32_t count)
	{
		static_assert(sizeof(Type) > 0, "Type is not Supported!!");
	}

	template<>
	void Push<uint32_t>(uint32_t count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<float>(uint32_t count)
	{
		m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<uint8_t>(uint32_t count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });
		m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
	inline uint32_t GetStride() const { return m_Stride; }

private:
	std::vector<VertexBufferElement> m_Elements;
	uint32_t m_Stride;
};

