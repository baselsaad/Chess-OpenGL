#pragma once
#include <iostream>

class VertexBuffer
{
public:
	VertexBuffer(const void* data, uint32_t size);
	~VertexBuffer();

public:
	void Bind() const;
	void UnBind() const;

private:
	uint32_t m_RendererID;
};

