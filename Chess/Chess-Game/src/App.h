#pragma once
#include "Utilities\DeltaTime.h"

class OpenGLWindow;
class GLFWWindow;
class PlayerInput;
class DeltaTime;

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
	OpenGLWindow* m_Window;
	PlayerInput* m_PlayerInput;
	Game* m_GameLayer;

	EventFuncType m_EventCallback;
	DeltaTime m_DeltaTime;
};

extern bool s_Running;
