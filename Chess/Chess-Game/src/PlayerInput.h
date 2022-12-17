#pragma once
#include "Event.h"

using EventFuncType = std::function<void(Event&)>;

class PlayerInput
{
public:
	PlayerInput() = default;
	~PlayerInput() = default;

public:
	void OnEvent(Event& e);
	void BindActionEvent(EventType inputEvent, EventFuncType&& func); 

private:
	std::unordered_map<EventType, EventFuncType> m_BindFunctions;
};