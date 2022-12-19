#pragma once

class OpenGLWindow;
class GLFWWindow;
class PlayerInput;

enum class EventType;
class Event;
class Game;

class Application
{
public:

	using EventFuncType = std::function<void(Event&)>;
	Application();
	~Application();

public:
	void OnStart();
	void Run();
	void SetupEventCallback();
	void OnDestroy();

	void OnClose(Event& event);
	void OnResizeWindow(Event& event);

private:
	std::unique_ptr<OpenGLWindow> m_Window;
	std::unique_ptr<PlayerInput> m_PlayerInput;
	Game* m_GameLayer;

	EventFuncType m_EventCallback;

	float m_LastFrameTime = 0.0f;
};

extern bool s_Running;
