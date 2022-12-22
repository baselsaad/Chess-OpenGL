#include "pch.h"
#include "Game.h"

#include "Renderer\Defaults.h"
#include "Utilities\Log.h"
#include "Utilities\Debug.h"
#include "Utilities\Colors.h"
#include "Event.h"
#include "PlayerInput.h"
#include "Entity.h"

static Entity* s_SelectedEntity = nullptr;
static float s_PressedX = 0.0f;
static float s_PressedY = 0.0f;

Game::Game(int height, int width)
	: m_VertexBuffer(Defaults::Positions, Defaults::PositionsSize)
	, m_IndexBuffer(Defaults::Indices, Defaults::IndicesCount)
	, m_Shader("res/shaders/Color.shader")
	, m_VertexArray(VertexArray())
	, m_WindowHeight(height)
	, m_WindowWidth(width)
{
	constexpr int totalPieces = 32;
	m_EntityPool.reserve(totalPieces);
}

Game::Game()
	: Game(Defaults::WINDOW_WIDTH, Defaults::WINDOW_HEIGHT)
{
}

void Game::SetupPlayerInput(PlayerInput* input)
{
	ASSERT(input, "input can not be null!!");

	input->BindActionEvent(EventType::MouseButtonPressed, this, &Game::OnMousePressed);
	input->BindActionEvent(EventType::MouseButtonReleased, this, &Game::OnMouseReleased);
	input->BindActionEvent(EventType::MouseMove, this, &Game::OnMouseMove);
}

void Game::OnStart()
{
	Debug::Info("OnStart");

	m_Layout.Push<float>(2);
	m_Layout.Push<float>(2);
	m_VertexArray.AddBuffer(m_VertexBuffer, m_Layout);

	m_EntityPool.emplace_back(new Entity(TransformComponent({ 100.0f, 100.0f, 0.0f }), Colors::Dark_Cyan));
	m_EntityPool.emplace_back(new Entity(TransformComponent({ 400.0f, 50.0f, 0.0f }), Colors::Red));
	m_EntityPool.emplace_back(new Entity(TransformComponent({ 200.0f, 50.0f, 0.0f }), Colors::Dark_Magenta));
	m_EntityPool.emplace_back(new Entity(TransformComponent({ 200.0f, 50.0f, 0.0f }), Colors::Orange));
	m_EntityPool.emplace_back(new Entity(TransformComponent({ 200.0f, 50.0f, 0.0f }), Colors::Pink));
	m_EntityPool.emplace_back(new Entity(TransformComponent({ 200.0f, 50.0f, 0.0f }), Colors::Tan));
}

void Game::OnUpdate(float deltaTime)
{
}

void Game::OnRender()
{
	const glm::mat4 proj = glm::ortho(0.0f, (float)m_WindowWidth, 0.0f, (float)m_WindowHeight, -1.0f, 1.0f);
	const glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	for (int i = 0; i < m_EntityPool.size(); i++)
	{
		m_Shader.Bind();
		Entity& entity = *m_EntityPool[i];

		glm::mat4 model = entity.GetTransformComponent().GetTransform();
		glm::mat4 mvp = proj * view * model;
		m_Shader.SetUniformMat4f("u_MVP", mvp);

		if (entity.GetSpriteSheetComponent().Sprite != nullptr)
		{
			entity.GetSpriteSheetComponent().BindTexture();
			m_Shader.SetUniform1i("u_Texture", 0);
		}
		else
		{
			m_Shader.SetUniform4f("u_Color", entity.GetSpriteSheetComponent().Color);
		}

		Renderer::Draw(m_VertexArray, m_IndexBuffer);
	}
}

void Game::OnDestroy()
{
	for (auto& entity : m_EntityPool)
		delete entity;
}

void Game::OnMousePressed(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseButtonPressed, "Wrong Event Type!!");
	MouseButtonPressedEvent* pressedButton = static_cast<MouseButtonPressedEvent*>(&event);

	s_PressedX = pressedButton->GetXPosition();
	s_PressedY = m_WindowHeight - pressedButton->GetYPosition();

	//TODO: grid system
	for (auto& entity : m_EntityPool)
	{
		if (entity->IsInBox(s_PressedX, s_PressedY))
			s_SelectedEntity = entity;
	}
}

void Game::OnMouseReleased(Event& event)
{
	ASSERT(event.GetEventType() == EventType::MouseButtonReleased, "Wrong Event Type!!");
	MouseButtonReleasedEvent* releasedButton = static_cast<MouseButtonReleasedEvent*>(&event);

	s_SelectedEntity = nullptr;
	s_PressedX = 0.0f;
	s_PressedY = 0.0f;
}

void Game::OnMouseMove(Event& event)
{
	if (s_SelectedEntity == nullptr)
		return;

	ASSERT(event.GetEventType() == EventType::MouseMove, "Wrong Event Type!!");
	MouseMoveEvent* e = static_cast<MouseMoveEvent*>(&event);

	double xOffset = (e->GetXPos() - s_PressedX);
	double yOffset = ((m_WindowHeight - e->GetYPos()) - s_PressedY);

	auto& location = s_SelectedEntity->GetTranslation();
	location.x += (float)xOffset;
	location.y += (float)yOffset;

	s_PressedX = e->GetXPos();
	s_PressedY = m_WindowHeight - e->GetYPos();
}

void Game::UpdateWindowResolution(int height, int width)
{
	m_WindowHeight = height;
	m_WindowWidth = width;
}
