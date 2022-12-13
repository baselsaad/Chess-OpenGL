#pragma once
#include <iostream>

class VertexBuffer;
class VertexBufferLayout;

class VertexArray
{

public:
	VertexArray();
	~VertexArray();

public:
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;

private:
	uint32_t m_RendererID;
};

