#pragma once

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(const void* data, uint32_t size);
	VertexBuffer(uint32_t size);
	~VertexBuffer();

public:
	void Bind() const;
	void UnBind() const;
	void SetData(const void* data, uint32_t size) const;

private:
	uint32_t m_RendererID;
};

