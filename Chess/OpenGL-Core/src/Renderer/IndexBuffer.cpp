#include "pch.h"
#include "OpenGL-Core.h"
#include "Utilities\Debug.h"

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
	: m_Count(count)
{
	ASSERT(sizeof(uint32_t) == sizeof(GLuint), "");

	// Index-Buffer
	const int buffersCount = 1;
	glGenBuffers(buffersCount, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	const int buffersCount = 1;
	glDeleteBuffers(buffersCount, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::UnBind() const
{
	// 0 to unbind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
