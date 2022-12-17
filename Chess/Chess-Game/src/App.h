#pragma once

class OpenGLWindow;
class GLFWWindow;
class PlayerInput;

enum class EventType;
class Event;

class Application
{
public:

	using EventFuncType = std::function<void(Event&)>;
	Application();
	~Application();

public:
	void Run();
	void SetupEventCallback();

	void OnClose(Event& event);
	void OnResizeWindow(Event& event);

	void OnEvent(Event& event);

private:
	std::shared_ptr<OpenGLWindow> m_Window;
	std::shared_ptr<PlayerInput> m_PlayerInput;

	EventFuncType m_EventCallback;

	float m_LastFrameTime = 0.0f;
};

extern bool s_Running;
