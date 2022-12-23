#include "pch.h"
#include "Utilities\Debug.h"
#include "Defaults.h"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib)
{
	ib.Bind();
	va.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}





