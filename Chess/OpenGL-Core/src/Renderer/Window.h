#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace OpenGLContext
{
	GLFWwindow* CreateOpenGLContext(int width, int height, const std::string& title);
	void ShutDown();
}

struct WindowData
{
	int Width;
	int Height;
	std::string Title;
};

class OpenGLWindow
{
public:
	OpenGLWindow() = default;
	OpenGLWindow(const WindowData& data);
	~OpenGLWindow();

public:
	void Clear();
	void Swap();

	void SetVsync(bool enable);

	inline const GLFWwindow* GetWindowHandle() { return m_WindowHandle; }
	inline const GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }

private:
	GLFWwindow* m_WindowHandle;
};

