#include "pch.h"
#include "OpenGL-Core.h"
#include "Utilities\Debug.h"


VertexBuffer::VertexBuffer(const void* data, uint32_t size)
{
	ASSERT(sizeof(uint32_t) == sizeof(GLuint), "OpenGL GLuint != uint32_t");

	// Vertex-Buffer
	constexpr int buffersCount = 1;

	glGenBuffers(buffersCount, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(uint32_t size)
{
	ASSERT(sizeof(uint32_t) == sizeof(GLuint), "OpenGL GLuint != uint32_t");

	constexpr int buffersCount = 1;

	glCreateBuffers(buffersCount, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
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

void VertexBuffer::SetData(const void* data, uint32_t size) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}
