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
	virtual ~OpenGLWindow();

public:
	void Clear();
	void Swap();

	void SetVsync(bool enable);

	inline  GLFWwindow* GetWindowHandle() { return m_WindowHandle; }
	inline const GLFWwindow* GetWindowHandle() const { return m_WindowHandle; }

	inline void SetWindowWidth(int width) {m_Width = width;}
	inline void SetWindowHeight(int height) {m_Height = height;}

	inline int GetWindowWidth() const { return m_Width; }
	inline int GetWindowHeight() const { return m_Height; }

	operator GLFWwindow*() const { return m_WindowHandle; }

private:
	GLFWwindow* m_WindowHandle;
	int m_Width, m_Height;
};

