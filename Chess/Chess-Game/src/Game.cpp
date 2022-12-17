#include "pch.h"
#include "Game.h"

#include "Utilities\Log.h"
#include "Utilities\Debug.h"

Game::Game()
{
	m_EntityPool.resize(500);
}

void Game::SetupPlayerInput(PlayerInput* input)
{
	ASSERT(input, "input can not be null!!");

	input->BindActionEvent(EventType::MouseButtonPressed, BIND_FUN(this, Game::OnMousePressed));
	input->BindActionEvent(EventType::MouseButtonReleased, BIND_FUN(this, Game::OnMouseReleased));
}

void Game::OnUpdate(float deltaTime)
{
	Debug::Info("DeltaTime: {0}", deltaTime);
}

void Game::OnMousePressed(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseButtonPressed, "Wrong Event Type!!");

	MouseButtonPressedEvent* pressedButton = static_cast<MouseButtonPressedEvent*>(&event);

	Debug::Warn("MouseButton Pressed on X:{0}, Y:{1}", pressedButton->GetXPosition(), pressedButton->GetYPosition());
}

void Game::OnMouseReleased(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseButtonReleased, "Wrong Event Type!!");

	MouseButtonReleasedEvent* releasedButton = static_cast<MouseButtonReleasedEvent*>(&event);
	Debug::Error("MouseButton Released on X:{0}, Y:{1}", releasedButton->GetXPosition(), releasedButton->GetYPosition());
}

void Game::OnMouseMove(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseMove, "Wrong Event Type!!");

	MouseMoveEvent* e = static_cast<MouseMoveEvent*>(&event);
	//Debug::Warn("X: {0}, Y : {1}", e->GetXPos(), e->GetYPos());
}
