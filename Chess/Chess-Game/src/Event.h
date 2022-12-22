#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define BIND_FUN(obj, fun)											\
[&] (auto&&... args)												\
{																	\
	obj->fun(std::forward<decltype(args)>(args)...);				\
}

enum class MouseButtonType
{
	Left = GLFW_MOUSE_BUTTON_LEFT, Right = GLFW_MOUSE_BUTTON_RIGHT, UnSupported
};

enum class EventType
{
	CloseWindow = 0,
	ResizeWindow,
	MouseButtonEvent,
	MouseButtonPressed,
	MouseButtonReleased,
	MouseMove
};

class Event
{
public:
	virtual EventType GetEventType() = 0;
};

class CloseWindowEvent : public Event
{
	virtual EventType GetEventType() override
	{
		return EventType::CloseWindow;
	}
};

class ResizeWindowEvent : public Event
{

public:
	ResizeWindowEvent(int width, int height)
		: m_Width(width), m_Height(height)
	{
	}

	virtual EventType GetEventType() override
	{
		return EventType::ResizeWindow;
	}

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	int m_Width, m_Height;

};

class MouseButtonEvent : public Event
{
public:
	using Super = MouseButtonEvent;

	MouseButtonEvent(int button, double x, double y)
		: m_XPosition(x)
		, m_YPosition(y)
	{
		switch (button)
		{
			case GLFW_MOUSE_BUTTON_LEFT:	m_ButtonType = MouseButtonType::Left;			break;
			case GLFW_MOUSE_BUTTON_RIGHT:	m_ButtonType = MouseButtonType::Right;			break;
			default:						m_ButtonType = MouseButtonType::UnSupported;	break;
		}
	}

	virtual EventType GetEventType() override
	{
		return EventType::MouseButtonEvent;
	}

	inline MouseButtonType GetButtonType() { return m_ButtonType; }

	inline double GetXPosition() { return m_XPosition; }
	inline double GetYPosition() { return m_YPosition; }

private:
	MouseButtonType m_ButtonType;
	double m_XPosition;
	double m_YPosition;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(int btn, double x, double y)
		: Super(btn, x, y)
	{
	}

	virtual EventType GetEventType() override
	{
		return EventType::MouseButtonPressed;
	}
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{

public:
	MouseButtonReleasedEvent(int btn, double x, double y)
		: Super(btn, x, y)
	{
	}

	virtual EventType GetEventType() override
	{
		return EventType::MouseButtonReleased;
	}
};


class MouseMoveEvent : public Event
{

public:
	MouseMoveEvent(double xPos, double yPos)
		: m_XPosition(xPos)
		, m_YPosition(yPos)
	{
	}

	inline double GetXPos() const { return m_XPosition; }
	inline double GetYPos() const { return m_YPosition; }

	virtual EventType GetEventType() override
	{
		return EventType::MouseMove;
	}

private:
	double m_XPosition;
	double m_YPosition;
};

