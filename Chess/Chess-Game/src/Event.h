#pragma once
#include <GLFW/glfw3.h>

enum class MouseButtonType
{
	Left = GLFW_MOUSE_BUTTON_LEFT, Right = GLFW_MOUSE_BUTTON_RIGHT, UnSupported
};

enum class EventType
{
	CloseWindow = 0,
	ResizeWindow,
	MouseButtonePressed,
	MouseButtoneReleased,
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

class MouseButtonPressedEvent : public Event
{

public:
	MouseButtonPressedEvent(int button)
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
		return EventType::MouseButtonePressed;
	}

	inline MouseButtonType GetButton() { return m_ButtonType; }


private:
	MouseButtonType m_ButtonType;
};

class MouseButtonReleasedEvent : public Event
{

public:
	MouseButtonReleasedEvent(int button)
	{

	}

	virtual EventType GetEventType() override
	{
		return EventType::MouseButtoneReleased;
	}

};

class MouseMoveEvent : public Event
{

public:
	MouseMoveEvent(float xPos, float yPos)
		: m_XPosition(xPos)
		, m_YPosition(yPos)
	{
	}

	inline float GetXPos() const { return m_XPosition; }
	inline float GetYPos() const { return m_YPosition; }

	virtual EventType GetEventType() override
	{
		return EventType::MouseMove;
	}


private:
	float m_XPosition, m_YPosition;
};
