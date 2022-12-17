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

	template<typename T>
	inline void BindActionEvent(EventType inputEvent, T* obj, void (T::* func)(Event&))
	{
		m_BindFunctions[inputEvent] = [obj, func](Event& e) { (obj->*func)(e); };
	}

private:
	std::unordered_map<EventType, EventFuncType> m_BindFunctions;
};