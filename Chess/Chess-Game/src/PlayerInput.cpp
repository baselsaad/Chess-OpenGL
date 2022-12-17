#include "pch.h"
#include "PlayerInput.h"

void PlayerInput::OnEvent(Event& e)
{
	auto finder = m_BindFunctions.find(e.GetEventType());
	if (finder != m_BindFunctions.end())
	{
		auto& func = finder->second;
		func(e);
	}
}

