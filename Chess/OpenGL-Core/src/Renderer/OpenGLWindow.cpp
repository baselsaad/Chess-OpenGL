#include "pch.h"
#include "Utilities\Debug.h"


OpenGLWindow::OpenGLWindow(const WindowData& data)
	: m_Width(data.Width)
	, m_Height(data.Height)
	, m_AspectRatio(data.Width / data.Height)
{
	/* Initialize the library */
	ASSERT(glfwInit(), "GLFW is not initialized!");

	//should be called for glDebugMessageCallback
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	m_WindowHandle = glfwCreateWindow(data.Width, data.Height, data.Title.c_str(), NULL, NULL);
	ASSERT(m_WindowHandle, "Window is null!");

	glfwMakeContextCurrent(m_WindowHandle);// Make the window's context current 
	SetVsync(true);
	GLenum state = glewInit();//glewInit should be called after a valid OpenGL rendering context has been created

	// Set Callback error message
	//glDebugMessageCallback(OpenGLMessageCallback, nullptr); //shows unnecessarily messages
	glfwSetErrorCallback(GLFWErrorCallback);

	// GPU driver and OpenGL Information
	Debug::Info("OpenGL Info:");
	Debug::Info("  Vendor: {0}", glGetString(GL_VENDOR));
	Debug::Info("  GPU: {0}", glGetString(GL_RENDERER));
	Debug::Info("  OpenGL-Version: {0}", glGetString(GL_VERSION));
}

OpenGLWindow::~OpenGLWindow()
{
	glfwDestroyWindow(m_WindowHandle);
	glfwTerminate();
}

void OpenGLWindow::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLWindow::Swap()
{
	/* Swap front and back buffers */
	glfwSwapBuffers(m_WindowHandle);
}

void OpenGLWindow::PollEvents()
{
	/* Poll for and process events */
	glfwPollEvents();
}

void OpenGLWindow::SetVsync(bool enable)
{
	glfwSwapInterval(enable);
}