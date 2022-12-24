#include "pch.h"

int Renderer::s_DrawCalls = 0;

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib)
{
	ib.Bind();
	va.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	s_DrawCalls++;
}