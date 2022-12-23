#include "pch.h"
#include "Game.h"

#include "Renderer\Defaults.h"
#include "Utilities\Log.h"
#include "Utilities\Debug.h"
#include "Utilities\Colors.h"
#include "Utilities\Timer.h"	
#include "Event.h"
#include "PlayerInput.h"

static Entity* s_SelectedEntity = nullptr;
static double s_PressedX = 0.0f;
static double s_PressedY = 0.0f;

Game::Game(int height, int width)
	: m_EntityVB(Defaults::Positions, Defaults::PositionsSize)
	, m_EntityIB(Defaults::Indices, Defaults::IndicesCount)
	, m_EntityShader("res/shaders/Texture.shader")
	, m_VertexArray(VertexArray())
	, m_WindowHeight(height)
	, m_WindowWidth(width)
	, m_TextureTest("res/textures/1024_13.png")
	, m_BackgroundTexture("res/textures/background.jpg")
	, m_BackgroundImage(TransformComponent({ 0.0f,0.0f,0.0f }), SpriteSheetComponent(&m_BackgroundTexture))
{
	constexpr int totalPieces = 32;
	m_EntityPool.reserve(totalPieces);

	const glm::mat4 proj = glm::ortho(0.0f, (float)m_WindowWidth, 0.0f, (float)m_WindowHeight, -1.0f, 1.0f);
	m_ProjectionView = proj * glm::mat4(1.0f);
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
	m_EntityLayout.Push<float>(2);
	m_EntityLayout.Push<float>(2);
	m_VertexArray.AddBuffer(m_EntityVB, m_EntityLayout);

	AdjustBackgroundImage();
	m_EntityPool.emplace_back(Entity(TransformComponent({ 0.0f,0.0f,0.0f }), SpriteSheetComponent(&m_TextureTest)));
}

void Game::OnUpdate(float deltaTime)
{
}

void Game::OnRender()
{
	DrawBackground();

	for (int i = 0; i < m_EntityPool.size(); i++)
	{
		m_EntityShader.Bind();
		Entity& entity = m_EntityPool[i];

		glm::mat4 model = entity.GetTransformComponent().GetTransformationMatrix();
		glm::mat4 mvp = m_ProjectionView * model;
		m_EntityShader.SetUniformMat4f("u_MVP", mvp);

		if (entity.GetSpriteSheetComponent().Sprite != nullptr)
		{
			entity.GetSpriteSheetComponent().BindTexture();
			m_EntityShader.SetUniform1i("u_Texture", 0);
		}
		else
		{
			m_EntityShader.SetUniform4f("u_Color", entity.GetSpriteSheetComponent().Color);
		}

		Renderer::Draw(m_VertexArray, m_EntityIB);
	}
}

void Game::OnDestroy()
{
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
		if (entity.IsInBound((int)s_PressedX, (int)s_PressedY))
			s_SelectedEntity = &entity;
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

	const glm::mat4 proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
	m_ProjectionView = proj * glm::mat4(1.0f);;

	AdjustBackgroundImage();
}

void Game::DrawBackground()
{
	glm::mat4 model = m_BackgroundImage.GetTransformComponent().GetTransformationMatrix();
	glm::mat4 mvp = m_ProjectionView * model;

	m_EntityShader.Bind();
	m_EntityShader.SetUniformMat4f("u_MVP", mvp);
	m_BackgroundImage.GetSpriteSheetComponent().BindTexture();
	m_EntityShader.SetUniform1i("u_Texture", 0);

	Renderer::Draw(m_VertexArray, m_EntityIB);
}

void Game::AdjustBackgroundImage()
{
	// Centering Calculation based on (0.0 , 0.0) position
	// so make sure every time we adjust the backgroundimage to set the x,y to 0
	m_BackgroundImage.GetTranslation().x = 0.0f;
	m_BackgroundImage.GetTranslation().y = 0.0f;

	// Calculate the Scale for the background entity to fit to the window
	float xNewScale = m_WindowWidth  / (Defaults::MAX_POSITION_OFFSET);
	float yNewScale = m_WindowHeight / (Defaults::MAX_POSITION_OFFSET);

	m_BackgroundImage.GetScale().x = xNewScale;
	m_BackgroundImage.GetScale().y = yNewScale;

	// center of the window
	float windowCenterX = (float)m_WindowWidth / 2;
	float windowCenterY = (float)m_WindowHeight / 2;

	// center of the quad
	float quadCenterX = (Defaults::MAX_POSITION_OFFSET / 2) * xNewScale;
	float quadCenterY = (Defaults::MAX_POSITION_OFFSET / 2) * yNewScale;

	float offsetX = windowCenterX - quadCenterX;
	float offsetY = windowCenterY - quadCenterY;

	m_BackgroundImage.GetTranslation().x += offsetX;
	m_BackgroundImage.GetTranslation().y += offsetY;
}
