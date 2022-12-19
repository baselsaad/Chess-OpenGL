#include "pch.h"
#include "Game.h"

#include "Utilities\Log.h"
#include "Utilities\Debug.h"

Game::Game()
{
	m_EntityPool.resize(24);
}

void Game::SetupPlayerInput(PlayerInput* input)
{
	ASSERT(input, "input can not be null!!");

	input->BindActionEvent(EventType::MouseButtonPressed, this, &Game::OnMousePressed);
	input->BindActionEvent(EventType::MouseButtonReleased, this, &Game::OnMouseReleased);
}

void Game::OnStart()
{
	Debug::Info("OnStart");
}

void Game::OnRender()
{
}

void Game::OnUpdate(float deltaTime)
{

}

void Game::OnDestroy()
{
	Debug::Log("OnDestroy");
}

void Game::OnMousePressed(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseButtonPressed, "Wrong Event Type!!");

	MouseButtonPressedEvent* pressedButton = static_cast<MouseButtonPressedEvent*>(&event);

	Debug::Log("MouseButton Pressed on X:{0}, Y:{1}", pressedButton->GetXPosition(), pressedButton->GetYPosition());
}

void Game::OnMouseReleased(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseButtonReleased, "Wrong Event Type!!");

	MouseButtonReleasedEvent* releasedButton = static_cast<MouseButtonReleasedEvent*>(&event);
	Debug::Log("MouseButton Released on X:{0}, Y:{1}", releasedButton->GetXPosition(), releasedButton->GetYPosition());
}

void Game::OnMouseMove(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseMove, "Wrong Event Type!!");

	MouseMoveEvent* e = static_cast<MouseMoveEvent*>(&event);
	//Debug::Warn("X: {0}, Y : {1}", e->GetXPos(), e->GetYPos());
}
