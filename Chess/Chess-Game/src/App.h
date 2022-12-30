#pragma once
#include "Utilities\DeltaTime.h"
#include "Container.h"

class OpenGLWindow;
class GLFWWindow;
class PlayerInput;
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

	using EventFuncType = std::function<void(Event&)>;
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
	PlayerInput* m_PlayerInput;
	Game* m_GameLayer;

	EventFuncType m_EventCallback;
	DeltaTime m_DeltaTime;
	EntityContainer m_EntityContainer;
};

extern bool s_Running;
