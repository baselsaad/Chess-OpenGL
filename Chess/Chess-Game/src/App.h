#pragma once

class OpenGLWindow;
class Event;
enum class EventType;
class GLFWWindow;

class Application
{
	using EventFuncType = std::function<void(Event&)>;

public:
	Application();
	~Application();

public:
	void Run();
	void InitEventSystem();

	void OnClose(Event& event);
	void OnResizeWindow(Event& event);

	void OnMousePressed(Event& event);
	void OnMouseReleased(Event& event);
	void OnMouseMove(Event& event);

	template<typename T>
	void BindActionEvent(EventType inputEvent, T* obj, void(T::* ptrFunc)(Event&));

	void OnEvent(Event& event);

private:
	std::shared_ptr<OpenGLWindow> m_Window;
	EventFuncType m_EventCallback;

	std::unordered_map<EventType, EventFuncType> m_BindFunctions;
};

extern bool s_Running;