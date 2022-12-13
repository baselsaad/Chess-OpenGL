#include "pch.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"



Renderer::Renderer(GLFWwindow* window)
	: m_WindowHandle(window)
{
}

void Renderer::Draw(const VertexArray& vb, const IndexBuffer& ib) const
{
	// because we generate and bind the buffer outside the loop, OpenGL knows which buffer should be drawn
	vb.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::OnUpdate(const VertexArray& vb, const IndexBuffer& ib, Shader& shader)
{
	// 4:3 Aspect ratio
	// 2.0 * 2 = 4
	// 1.5 * 2 = 3
	const char* projUniform = "u_MVP";
	const glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	const glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	// Draw Quads
	{
		for (int i = 0; i < m_Quads.size(); i++)
		{
			shader.Bind();
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Quads[i].Transform);
			glm::mat4 mvp = proj * view * model;
			shader.SetUniformMat4f(projUniform, mvp);

			if (m_Quads[i].BindTexture())
			{
				shader.SetUniform1i("u_Texture", 0);
			}

			Draw(vb, ib);

			std::string labelName = "Sprite-" + std::to_string(i + 1);
		}
	}

}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Swap() const
{
	/* Swap front and back buffers */
	glfwSwapBuffers(m_WindowHandle);

	/* Poll for and process events */
	glfwPollEvents();
}

void Renderer::AddNewQuad(Texture* texture)
{
	m_Quads.emplace_back(DEFAULT_TRANSFORM, texture);
}
