#include "pch.h"
#include "Window.h"
#include "Utilities\Debug.h"


OpenGLWindow::OpenGLWindow(const WindowData& data)
	: m_Width(data.Width), m_Height(data.Height)
{
	m_WindowHandle = OpenGLContext::CreateOpenGLContext(data.Width, data.Height, data.Title);
}

OpenGLWindow::~OpenGLWindow()
{
	OpenGLContext::ShutDown();
}

void OpenGLWindow::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLWindow::Swap()
{
	/* Poll for and process events */
	glfwPollEvents();

	/* Swap front and back buffers */
	glfwSwapBuffers(m_WindowHandle);
}

void OpenGLWindow::SetVsync(bool enable)
{
	glfwSwapInterval(enable);
}

namespace OpenGLContext
{
	GLFWwindow* CreateOpenGLContext(int width, int height, const std::string& title)
	{
		/* Initialize the library */
		ASSERT(glfwInit(), "GLFW is not initialized!");

		//should be called for glDebugMessageCallback
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode window and its OpenGL context */
		GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		ASSERT(window, "Window is null!");

		glfwMakeContextCurrent(window);// Make the window's context current 
		glfwSwapInterval(true); // vsync
		GLenum state = glewInit();//glewInit should be called after a valid OpenGL rendering context has been created

		// Set Callback error message
		//glDebugMessageCallback(OpenGLMessageCallback, nullptr); shows unnecessarily messages
		glfwSetErrorCallback(GLFWErrorCallback);

		// GPU driver and OpenGL Information
		Debug::Info("OpenGL Info:");
		Debug::Info("  Vendor: {0}", glGetString(GL_VENDOR));
		Debug::Info("  GPU: {0}", glGetString(GL_RENDERER));
		Debug::Info("  OpenGL-Version: {0}", glGetString(GL_VERSION));

		return window;
	}


	void ShutDown()
	{
		glfwTerminate();
	}

}
