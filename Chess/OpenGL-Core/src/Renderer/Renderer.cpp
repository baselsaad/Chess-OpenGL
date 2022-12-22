#include "pch.h"
#include "Utilities\Debug.h"
#include "Defaults.h"


void Renderer::Draw(const VertexArray& vb, const IndexBuffer& ib)
{
	vb.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::OnUpdate(const VertexArray& va, const VertexBuffer& vb, const IndexBuffer& ib, Shader& shader)
{
	// 4:3 Aspect ratio
	// 2.0 * 2 = 4
	// 1.5 * 2 = 3
	const char* projUniform = "u_MVP";
	const glm::mat4 proj = glm::ortho(0.0f, (float)Defaults::WINDOW_WIDTH, 0.0f, (float)Defaults::WINDOW_HEIGHT, -1.0f, 1.0f);
	const glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	// Draw Quads
	{
		for (int i = 0; i < m_Quads.size(); i++)
		{
			shader.Bind();
			Quad* quad = m_Quads[i];
			glm::mat4 model = quad->Transform.GetTransform();
			glm::mat4 mvp = proj * view * model;
			shader.SetUniformMat4f(projUniform, mvp);

			if (quad->Sprite != nullptr)
			{
				quad->BindTexture();
				shader.SetUniform1i("u_Texture", 0);
			}
			else
			{
				shader.SetUniform4f("u_Color", quad->Color);
			}

			Draw(va, ib);
		}
	}

}

void Renderer::AddNewQuad(Quad* quad)
{
	m_Quads.emplace_back(quad);
}
