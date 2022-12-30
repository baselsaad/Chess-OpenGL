#pragma once
struct GLFWwindow;

struct WindowData
{
	int Width;
	int Height;
	std::string Title;
};

class OpenGLWindow
{
public:
	OpenGLWindow(const WindowData& data);
	virtual ~OpenGLWindow();

public:
	void Clear();
	void Swap();
	void PollEvents();

	void SetVsync(bool enable);
	void UpdateViewport(int width, int height);

	inline GLFWwindow* GetWindowHandle() { return m_Window; }
	inline const GLFWwindow* GetWindowHandle() const { return m_Window; }

	inline int GetWindowWidth() const { return m_Width; }
	inline int GetWindowHeight() const { return m_Height; }
	inline float GetAspectRatio() const { return (float)m_Width / (float)m_Height; }

	operator GLFWwindow* () const { return m_Window; }

private:
	void HandleErrorMessages();
	void PrintGpuInformation();

private:
	GLFWwindow* m_Window;
	int m_Width, m_Height;
};

