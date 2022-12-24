#pragma once
class VertexArray;
class IndexBuffer;
class Shader;
struct Quad;

class Renderer
{
public:
	Renderer() = delete;
	Renderer(const Renderer&) = delete;
	~Renderer() = delete;

public:
	static void Draw(const VertexArray& vb, const IndexBuffer& ib);
	static void ResetStats() { s_DrawCalls = 0; }
	static size_t GetDrawCalls() { return s_DrawCalls; }
private:
	static int s_DrawCalls;
};






