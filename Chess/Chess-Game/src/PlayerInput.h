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

	template<typename T, typename MethodParameter>
	inline void BindActionEvent(EventType inputEvent, T* obj, void (T::* func)(MethodParameter&))
	{
		static_assert(std::is_base_of<Event, MethodParameter>::value, "Parameter Type of the Method must be derived from Event!!");

		m_BoundFunctions[inputEvent] = [obj, func](Event& e) { (obj->*func)(static_cast<MethodParameter&>(e)); };
	}

private:
	std::unordered_map<EventType, EventFuncType> m_BoundFunctions;
};