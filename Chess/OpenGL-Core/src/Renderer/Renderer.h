#pragma once

struct Quad;
struct TransformComponent;
struct SpriteSheetComponent;

class VertexArray;
class IndexBuffer;
class VertexArray;
class VertexBuffer;
class VertexBufferLayout;
class IndexBuffer;
class Shader;
class Entity;

struct RenderData
{
	VertexArray VertexArray;
	VertexBuffer VetexBuffer;
	VertexBufferLayout Layout;
	IndexBuffer IndexBuffer;

	Shader TextureShader;
	Shader ColorShader;

	RenderData();
};

class Renderer
{
public:
	Renderer() = default;
	Renderer(const Renderer&) = delete;

public:
	static void Init(const glm::vec2& viewport);
	static void ShutDown();

	static void DrawQuad(const glm::mat4& transform, const Texture* texture);
	static void DrawQuad(const glm::mat4& transform, const Colors::RGBA& color);
	static void DrawQuad(const glm::vec3& position,const glm::vec3& scale, const Colors::RGBA& color);

	static void ResetStats();
	static int GetDrawCalls();

	static void UpdateViewport(int width, int height);
	static const glm::vec2& GetViewport();
	static const glm::mat4& GetProjectionView();

private:
	static Renderer* Get();

	static void Draw(const VertexArray& vb, const IndexBuffer& ib);
	void CalculateProjectionViewMatrix();

private:
	int m_DrawCalls;
	glm::vec2 m_Viewport;
	glm::mat4 m_ProjectionView;
	RenderData m_RenderData;
};






