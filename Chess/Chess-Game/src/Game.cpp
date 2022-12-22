#include "pch.h"
#include "Game.h"

#include "Renderer\Defaults.h"
#include "Utilities\Log.h"
#include "Utilities\Debug.h"
#include "Utilities\Colors.h"
#include "Event.h"
#include "PlayerInput.h"

Game::Game(int height, int width)
	: m_VertexBuffer(Defaults::Positions, Defaults::PositionsSize)
	, m_IndexBuffer(Defaults::Indices, Defaults::IndicesCount)
	, m_Shader("res/shaders/Color.shader")
	, m_VertexArray(VertexArray())
	, m_WindowHeight(height)
	, m_WindowWidth(width)
{
	constexpr int totalPieces = 32;
	m_EntityPool.resize(totalPieces);
}

Game::Game()
	: Game(960, 540)
{
}

void Game::SetupPlayerInput(PlayerInput* input)
{
	ASSERT(input, "input can not be null!!");

	input->BindActionEvent(EventType::MouseButtonPressed, this, &Game::OnMousePressed);
	input->BindActionEvent(EventType::MouseButtonReleased, this, &Game::OnMouseReleased);
	input->BindActionEvent(EventType::MouseMove, this, &Game::OnMouseMove);
}

static Quad RedQuad(TransformComponent({ 400.0f, 50.0f, 0.0f }), Colors::Red);
static Quad WhiteQuad(TransformComponent({ 0.0f,0.0f,0.0f }), Colors::White);

void Game::OnStart()
{
	Debug::Info("OnStart");

	m_Layout.Push<float>(2);
	m_Layout.Push<float>(2);
	m_VertexArray.AddBuffer(m_VertexBuffer, m_Layout);

	RedQuad.Transform.Scale.x = 3.0f;
	RedQuad.Transform.Scale.y = 2.0f;

	m_Renderer.AddNewQuad(&WhiteQuad);
	m_Renderer.AddNewQuad(&RedQuad);
}

static Quad* s_SelectedQuad = nullptr;
static float s_PressedX = 0.0f;
static float s_PressedY = 0.0f;

void Game::OnUpdate(float deltaTime)
{
}

void Game::OnRender()
{
	m_Renderer.OnUpdate(m_VertexArray, m_VertexBuffer, m_IndexBuffer, m_Shader);
}

void Game::OnDestroy()
{
	Debug::Log("OnDestroy");
}

void Game::OnMousePressed(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseButtonPressed, "Wrong Event Type!!");

	MouseButtonPressedEvent* pressedButton = static_cast<MouseButtonPressedEvent*>(&event);
	//Debug::Log("MouseButton Pressed on X:{0}, Y:{1}", pressedButton->GetXPosition(), m_WindowHeight - pressedButton->GetYPosition());

	s_PressedX = pressedButton->GetXPosition();
	s_PressedY = m_WindowHeight - pressedButton->GetYPosition();

	if (RedQuad.IsInQuad(pressedButton->GetXPosition(), m_WindowHeight - pressedButton->GetYPosition()))
	{
		s_SelectedQuad = &RedQuad;
	}
	else if (WhiteQuad.IsInQuad(pressedButton->GetXPosition(), m_WindowHeight - pressedButton->GetYPosition()))
	{
		s_SelectedQuad = &WhiteQuad;
	}
	else
	{
		s_SelectedQuad = nullptr;
	}
}

void Game::OnMouseReleased(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseButtonReleased, "Wrong Event Type!!");
	MouseButtonReleasedEvent* releasedButton = static_cast<MouseButtonReleasedEvent*>(&event);
	//Debug::Log("MouseButton Released on X:{0}, Y:{1}", releasedButton->GetXPosition(), releasedButton->GetYPosition());

	s_SelectedQuad = nullptr;
	s_PressedX = 0.0f;
	s_PressedY = 0.0f;
}

void Game::OnMouseMove(Event& event)
{
	if (s_SelectedQuad == nullptr)
		return;

	ASSERT(event.GetEventType() == EventType::MouseMove, "Wrong Event Type!!");
	MouseMoveEvent* e = static_cast<MouseMoveEvent*>(&event);

	double xOffset = (e->GetXPos() - s_PressedX);
	double yOffset = ((m_WindowHeight - e->GetYPos()) - s_PressedY);

	s_SelectedQuad->Transform.Translation.x += (float)xOffset;
	s_SelectedQuad->Transform.Translation.y += (float)yOffset;

	s_PressedX = e->GetXPos();
	s_PressedY = m_WindowHeight - e->GetYPos();
}

void Game::UpdateWindowResolution(int height, int width)
{
	m_WindowHeight = height;
	m_WindowWidth = width;
}
