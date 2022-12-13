// https://docs.gl/

#include "pch.h"
#include "OpenGL.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/VertexBufferLayout.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"

#include "Tools/Colors.h"
#include "Tools/Timer.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

static Timer::Lambda ChangeColor(Shader& shader, const char* colorUniform)
{
	int increamnt = 0;
	Colors::RGBA color = Colors::RGBA(Colors::ColorsArray.at(0));

	// colorUniform should be copied because its get out of scope 
	Timer::Lambda changeColor = [&color, &increamnt, &shader, colorUniform]()
	{
		increamnt++;
		if (increamnt >= Colors::ColorsArray.size())
		{
			increamnt = 0;
		}

		color = Colors::ColorsArray.at(increamnt);

		shader.Bind();
		shader.SetUniform4f(colorUniform, color.R, color.G, color.B, color.Alpha);
	};

	return changeColor;
}

int main()
{
	GLFWwindow* window = CreateOpenGLContext();

	{
		// VertexBuffer
		VertexBuffer vertexBuffer(Defaults::positions, Defaults::PositionsSize * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);

		// VertexArray
		VertexArray vertexArray;
		vertexArray.AddBuffer(vertexBuffer, layout);

		//IndexBuffer
		IndexBuffer indexBuffer(Defaults::indices, Defaults::IndicesSize);

		// Shaders
		Shader shader("res/shaders/Basic.shader");

		int textureNumber = 1;
		Texture testTexture("res/textures/test.png");

		Renderer renderer(window);

		// Timers 
		Timer timer;
		//timer.SetCallBackTimer(1.0f, ChangeColor(shader, colorUniform));

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();

			// Update TimersCallback
			{
				for (auto& tm : timer.CallbacksVec)
				{
					tm.Update();
				}
			}

			// Render
			{

				//renderer.AddNewQuad(&testTexture);
				
				//Basic Way to render multiaple objects (TODO: Batch rendering)
				renderer.OnUpdate(vertexArray, indexBuffer, shader);
			}

			renderer.Swap();
		}
	}

	// should be delete before glfwTerminate
	glfwTerminate();

	return 0;
}