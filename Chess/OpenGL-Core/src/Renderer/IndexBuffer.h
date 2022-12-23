#pragma once

class IndexBuffer
{
public:
	IndexBuffer() = default;
	IndexBuffer(const uint32_t* data, uint32_t count);
	~IndexBuffer();

public:

	void Bind() const;
	void UnBind() const;

	inline uint32_t GetCount() const { return m_Count; };

private:
	uint32_t m_RendererID;
	uint32_t m_Count;
};

