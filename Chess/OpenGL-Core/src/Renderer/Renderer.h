#pragma once
class VertexArray;
class IndexBuffer;
class Shader;
struct Quad;

class Renderer
{
public:
	Renderer() = default;
	~Renderer() = default;

public:
	void Draw(const VertexArray& vb, const IndexBuffer& ib);
	void OnUpdate(const VertexArray& va, const VertexBuffer& vb, const IndexBuffer& ib, Shader& shader);

	void AddNewQuad(Quad* quad);

	inline size_t GetDrawCalls() const { return m_Quads.size(); }
private:
	std::vector<Quad*> m_Quads;
};






