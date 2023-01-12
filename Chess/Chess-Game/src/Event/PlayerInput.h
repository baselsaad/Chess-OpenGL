#pragma once
#include "Event.h"

using EventFunc = std::function<void(Event&)>;

class PlayerInput
{
public:
	PlayerInput() = default;
	~PlayerInput() = default;

public:
	void OnEvent(Event& e);

	template<typename T, typename MethodParameter>
	inline void BindAction(EventType inputEvent, T* obj, void (T::* func)(const MethodParameter&))
	{
		static_assert(std::is_base_of<Event, MethodParameter>::value, "Parameter Type of the Method must be derived from Event!!");

		m_BoundFunctions[inputEvent] = [obj, func](const Event& e) { (obj->*func)(static_cast<const MethodParameter&>(e)); };
	}

private:
	std::unordered_map<EventType, EventFunc> m_BoundFunctions;
};