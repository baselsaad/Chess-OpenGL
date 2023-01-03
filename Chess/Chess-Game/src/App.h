#pragma once
#include "Utilities\DeltaTime.h"
#include "PlayerInput.h"

class OpenGLWindow;
class GLFWWindow;
class DeltaTime;
class EntityContainer;

enum class EventType;
class Event;
class ResizeWindowEvent;
class CloseWindowEvent;
class Game;

class Application
{
public:
	Application();
	~Application();

public:
	void OnStart();
	void Run();
	void SetupEventCallback();
	void OnDestroy();

	void OnClose(CloseWindowEvent& event);
	void OnResizeWindow(ResizeWindowEvent& event);

private:
	OpenGLWindow* m_Window;
	Game* m_Game;

	PlayerInput m_PlayerInput;

	std::function<void(Event&)> m_EventCallback;
	DeltaTime m_DeltaTime;
};

extern bool s_Running;
