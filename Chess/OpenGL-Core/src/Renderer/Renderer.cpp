#include "pch.h"
#include "OpenGL-Core.h"

#include "Defaults.h"

// Manage life time
static Renderer* s_Instance = nullptr;

RenderData::RenderData()
	: VetexBuffer(Defaults::Positions, Defaults::PositionsSize)
	, IndexBuffer(Defaults::Indices, Defaults::IndicesCount)
	, TextureShader("res/shaders/Texture.shader")
	, ColorShader("res/shaders/Color.shader")
{
	Layout.Push<float>(2);
	Layout.Push<float>(2);
	VertexArray.AddBuffer(VetexBuffer, Layout);
}

Renderer* Renderer::Get()
{
	ASSERT(s_Instance != nullptr, "Renderer should be Initialized first!!");
	return s_Instance;
}

void Renderer::Init(const glm::vec2& viewport)
{
	ASSERT(s_Instance == nullptr, "Renderer should only be initialized once!!");
	GLenum state = glewInit();
	ASSERT(state == GLEW_OK, "glewInit should be called after a valid OpenGL rendering context has been created!!");

#if DEBUG
	glDebugMessageCallback(OpenGLMessageCallback, nullptr);
#endif

	// Texturing
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	s_Instance = new Renderer();
	s_Instance->m_DrawCalls = 0;
	s_Instance->m_Viewport = viewport;
	s_Instance->CalculateProjectionViewMatrix();
}

void Renderer::ShutDown()
{
	delete s_Instance;
}

void Renderer::DrawQuad(const glm::mat4& transform, const Texture* texture)
{
	glm::mat4 mvp = Renderer::Get()->m_ProjectionView * transform;

	Renderer::Get()->m_RenderData.TextureShader.Bind();
	texture->Bind(0);

	Renderer::Get()->m_RenderData.TextureShader.SetUniformMat4f("u_MVP", mvp);
	Renderer::Get()->m_RenderData.TextureShader.SetUniform1i("u_Texture", 0);

	Draw(Renderer::Get()->m_RenderData.VertexArray, Renderer::Get()->m_RenderData.IndexBuffer);
}

void Renderer::DrawQuad(const glm::mat4& transform, const Colors::RGBA& color)
{
	glm::mat4 mvp = Renderer::Get()->m_ProjectionView * transform;

	Renderer::Get()->m_RenderData.ColorShader.Bind();
	Renderer::Get()->m_RenderData.ColorShader.SetUniformMat4f("u_MVP", mvp);
	Renderer::Get()->m_RenderData.ColorShader.SetUniform4f("u_Color", color);

	Draw(Renderer::Get()->m_RenderData.VertexArray, Renderer::Get()->m_RenderData.IndexBuffer);
}

void Renderer::DrawQuad(const glm::vec3& position, const glm::vec3& scale, const Texture* texture)
{
	glm::mat4 transform =
		glm::translate(glm::mat4(1.0f), position)
		* glm::mat4(1.0f)
		* glm::scale(glm::mat4(1.0f), scale);

	DrawQuad(transform, texture);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib)
{
	ib.Bind();
	va.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	Renderer::Get()->m_DrawCalls++;
}

int Renderer::GetDrawCalls()
{
	return Renderer::Get()->m_DrawCalls;
}

void Renderer::ResetStats()
{
	Renderer::Get()->m_DrawCalls = 0;
}

void Renderer::CalculateProjectionViewMatrix()
{
	const glm::mat4 proj = glm::ortho(0.0f, m_Viewport.x, 0.0f, m_Viewport.y, -1.0f, 1.0f);
	m_ProjectionView = proj * glm::mat4(1.0f); // proj * view (Camera Pos(1.0f,1.0f))
}

void Renderer::UpdateViewport(int width, int height)
{
	glViewport(0, 0, width, height);

	Renderer::Get()->m_Viewport.x = width;
	Renderer::Get()->m_Viewport.y = height;
	Renderer::Get()->CalculateProjectionViewMatrix();
}

const glm::vec2& Renderer::GetViewport()
{
	return Renderer::Get()->m_Viewport;
}

const glm::mat4& Renderer::GetProjectionView()
{
	return Renderer::Get()->m_ProjectionView;
}