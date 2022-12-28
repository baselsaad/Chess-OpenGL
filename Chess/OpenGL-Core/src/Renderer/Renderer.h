#pragma once
class VertexArray;
class IndexBuffer;
class Shader;
struct Quad;

class Renderer
{
public:
	Renderer() = default;
	Renderer(const Renderer&) = delete;

public:
	static Renderer& Get();
	static void Init();

	void Draw(const VertexArray& vb, const IndexBuffer& ib);
	void ResetStats() { s_Instance.m_DrawCalls = 0; }
	size_t GetDrawCalls() { return s_Instance.m_DrawCalls; }
private:
	static Renderer s_Instance;

	int m_DrawCalls;
	bool m_IsInitialized;
};






