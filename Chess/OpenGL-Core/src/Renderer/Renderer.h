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
	inline size_t GetDrawCalls() const { return s_DrawCalls; }

private:
	static int s_DrawCalls;
};






