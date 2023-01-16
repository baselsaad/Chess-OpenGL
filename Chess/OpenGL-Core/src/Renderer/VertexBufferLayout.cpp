#include "pch.h"
#include "OpenGL-Core.h"

VertexBufferLayout::VertexBufferLayout()
	: m_Stride(0)
{
}

const std::vector<VertexBufferElement>& VertexBufferLayout::GetElements() const
{
	return m_Elements;
}

uint32_t VertexBufferLayout::GetStride() const
{
	return m_Stride;
}

template <typename T>
void VertexBufferLayout::Push(uint32_t count)
{
	static_assert(sizeof(T) > 0, "Type is not Supported!!");
}

template<>
void VertexBufferLayout::Push<uint32_t>(uint32_t count)
{
	m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
	m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}

template<>
void VertexBufferLayout::Push<float>(uint32_t count)
{
	m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });
	m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}

template<>
void VertexBufferLayout::Push<uint8_t>(uint32_t count)
{
	m_Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });
	m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}