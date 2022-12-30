#include "pch.h"
#include "Renderer.h"

Renderer Renderer::s_Instance;

Renderer& Renderer::Get()
{
	ASSERT(s_Instance.m_IsInitialized, "Renderer should be Initialized first!!");
	return s_Instance;
}

void Renderer::Init()
{
	GLenum state = glewInit();
	ASSERT(state == GLEW_OK, "glewInit should be called after a valid OpenGL rendering context has been created!!");

	glDebugMessageCallback(OpenGLMessageCallback, nullptr);

	// Texturing
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	s_Instance.m_DrawCalls = 0;
	s_Instance.m_IsInitialized = true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib)
{
	ib.Bind();
	va.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	s_Instance.m_DrawCalls++;
}