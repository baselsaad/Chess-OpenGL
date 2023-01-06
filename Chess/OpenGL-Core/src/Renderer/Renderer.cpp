#include "pch.h"
#include "OpenGL-Core.h"

#include "Defaults.h"

static int s_DrawCalls = 0;
static struct RenderData* s_Data = nullptr;

struct RenderData
{
	VertexArray VertexArray;
	VertexBuffer VetexBuffer;
	VertexBufferLayout Layout;
	IndexBuffer IndexBuffer;

	Shader TextureShader;
	Shader ColorShader;

	glm::vec2 Viewport;
	glm::mat4 ProjectionView;

	RenderData(int width, int height)
		: VetexBuffer(Defaults::Positions, Defaults::PositionsSize)
		, IndexBuffer(Defaults::Indices, Defaults::IndicesCount)
		, TextureShader("res/shaders/Texture.shader")
		, ColorShader("res/shaders/Color.shader")
		, Viewport(width, height)
	{
		Layout.Push<float>(2);
		Layout.Push<float>(2);
		VertexArray.AddBuffer(VetexBuffer, Layout);

		CalculateProjectionViewMatrix();
	}

	void CalculateProjectionViewMatrix()
	{
		const glm::mat4 proj = glm::ortho(0.0f, Viewport.x, 0.0f, Viewport.y, -1.0f, 1.0f);
		ProjectionView = proj * glm::mat4(1.0f); // proj * view (Camera Pos(1.0f,1.0f))
	}
};

void Renderer::Init(const glm::vec2& viewport)
{
	ASSERT(s_Data == nullptr, "Renderer should only be initialized once!!");
	GLenum state = glewInit();
	ASSERT(state == GLEW_OK, "glewInit should be called after a valid OpenGL rendering context has been created!!");

#if DEBUG
	glDebugMessageCallback(OpenGLMessageCallback, nullptr);
#endif

	// Texturing
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	s_Data = new RenderData(viewport.x, viewport.y);
	s_DrawCalls = 0;
}

void Renderer::ShutDown()
{
	delete s_Data;
}

void Renderer::DrawQuad(const glm::mat4& transform, const Texture* texture)
{
	ASSERT(s_Data , "Renderer should only be initialized !!");

	glm::mat4 mvp = s_Data->ProjectionView * transform;

	s_Data->TextureShader.Bind();
	texture->Bind(0);

	s_Data->TextureShader.SetUniformMat4f("u_MVP", mvp);
	s_Data->TextureShader.SetUniform1i("u_Texture", 0);

	Draw(s_Data->VertexArray, s_Data->IndexBuffer);
}

void Renderer::DrawQuad(const glm::mat4& transform, const Colors::RGBA& color)
{
	ASSERT(s_Data , "Renderer should only be initialized !!");
	glm::mat4 mvp = s_Data->ProjectionView * transform;

	s_Data->ColorShader.Bind();
	s_Data->ColorShader.SetUniformMat4f("u_MVP", mvp);
	s_Data->ColorShader.SetUniform4f("u_Color", color);

	Draw(s_Data->VertexArray, s_Data->IndexBuffer);
}

void Renderer::DrawQuad(const glm::vec3& position, const glm::vec3& scale, const Texture* texture)
{
	glm::mat4 transform =
		glm::translate(glm::mat4(1.0f), position)
		* glm::mat4(1.0f)
		* glm::scale(glm::mat4(1.0f), scale);

	DrawQuad(transform, texture);
}

void Renderer::DrawQuad(const glm::vec3& position, const glm::vec3& scale, const Colors::RGBA& color)
{
	glm::mat4 transform =
		glm::translate(glm::mat4(1.0f), position)
		* glm::mat4(1.0f)
		* glm::scale(glm::mat4(1.0f), scale);

	DrawQuad(transform, color);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib)
{
	ib.Bind();
	va.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	s_DrawCalls++;
}

int Renderer::GetDrawCalls()
{
	return s_DrawCalls;
}

void Renderer::ResetStats()
{
	s_DrawCalls = 0;
}

void Renderer::UpdateViewport(int width, int height)
{
	ASSERT(s_Data , "Renderer should only be initialized !!");

	glViewport(0, 0, width, height);

	s_Data->Viewport.x = width;
	s_Data->Viewport.y = height;
	s_Data->CalculateProjectionViewMatrix();
}

const glm::vec2& Renderer::GetViewport()
{
	ASSERT(s_Data , "Renderer should only be initialized !!");

	return s_Data->Viewport;
}

const glm::mat4& Renderer::GetProjectionView()
{
	ASSERT(s_Data , "Renderer should only be initialized !!");

	return s_Data->ProjectionView;
}