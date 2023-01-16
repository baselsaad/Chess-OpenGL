#pragma once
#include <vector>
#include "Utilities/Debug.h"

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
    VertexBufferLayout();

    template<typename T>
    void Push(uint32_t count);

    const std::vector<VertexBufferElement>& GetElements() const;
    uint32_t GetStride() const;

private:
    std::vector<VertexBufferElement> m_Elements;
    uint32_t m_Stride;
};

