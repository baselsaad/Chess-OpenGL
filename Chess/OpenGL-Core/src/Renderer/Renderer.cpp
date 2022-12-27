#include "pch.h"
#include "Renderer.h"

Renderer Renderer::s_Instance;
int Renderer::s_DrawCalls = 0;

Renderer& Renderer::Get()
{
	return s_Instance;
}

void Renderer::Init()
{
	ASSERT(glewInit() == GLEW_OK, "glewInit should be called after a valid OpenGL rendering context has been created!!"); 

	glDebugMessageCallback(OpenGLMessageCallback, nullptr);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	s_Instance.s_DrawCalls = 0;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib)
{
	ib.Bind();
	va.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	s_Instance.s_DrawCalls++;
}