#include "pch.h"
#include "VertexBuffer.h"

#include "Renderer.h"


VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
	// Vertex-Buffer
	const int buffersCount = 1;
	glGenBuffers(buffersCount, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	const int buffersCount = 1;
	glDeleteBuffers(buffersCount, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::UnBind() const
{
	// 0 to unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
