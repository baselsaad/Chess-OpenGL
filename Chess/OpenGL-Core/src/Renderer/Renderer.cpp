#include "pch.h"
#include "Utilities\Debug.h"
#include "Defaults.h"

void Renderer::Draw(const VertexArray& vb, const IndexBuffer& ib)
{
	vb.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}