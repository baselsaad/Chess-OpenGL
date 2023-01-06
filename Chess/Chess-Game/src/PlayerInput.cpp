#include "pch.h"
#include "OpenGL-Core.h"
#include "PlayerInput.h"

void PlayerInput::OnEvent(Event& e)
{
	auto finder = m_BoundFunctions.find(e.GetEventType());
	if (finder != m_BoundFunctions.end())
	{
		auto& func = finder->second;
		func(e);
	}
}

