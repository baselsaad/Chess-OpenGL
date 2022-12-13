#pragma once
#include "Renderer/Debug.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Defaults
{
	static const int PositionsSize = 4 * 4;
	static const int IndicesSize = 6;

	//positions with texture coord 2 | 2
	// Each "Line" for X , Y 
	static constexpr float positions[PositionsSize] =
	{
		 -50.0f, -50.0f , 0.0f, 0.0f,		// 0 bottom_left 
		  50.0f, -50.0f , 1.0f, 0.0f,		// 1 bottom_right
		  50.0f,  50.0f , 1.0f, 1.0f,		// 2 top_right
		 -50.0f,  50.0f , 0.0f, 1.0f		// 3 top_left
	};

	static constexpr uint32_t indices[IndicesSize] =
	{
		0, 1, 2,
		2, 3, 0
	};

	/**************************************************
	 *				3 * * * * * * * * * * * 2
	 *				*					*   *
	 *				* 			   *		*
	 *				*  		  *				*
	 * 				*  	  *					*
	 * 				*  *					*
	 * 				0 * * * * * * * * * * * 1
	 **************************************************/

}

GLFWwindow* CreateOpenGLContext()
{
	/* Initialize the library */
	CHECK(glfwInit(), "GLFW is not initialized!");

	//should be called for glDebugMessageCallback
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(960, 540, "OpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		__debugbreak();
		return nullptr;
	}

	glfwMakeContextCurrent(window);// Make the window's context current 
	glfwSwapInterval(true); // vsync
	GLenum state = glewInit();//glewInit should be called after a valid OpenGL rendering context has been created

	// Set Callback error message
	glDebugMessageCallback(OpenGLMessageCallback, nullptr);

	// GPU driver and OpenGL Information
	std::cout << "OpenGL Info:" << std::endl;
	std::cout << "  Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "  Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "  Version: " << glGetString(GL_VERSION) << std::endl;
	return window;
}
