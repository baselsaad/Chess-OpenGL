#include "pch.h"
#include "Game.h"

#include "Utilities\DeltaTime.h"
#include "Renderer\Defaults.h"
#include "Utilities\Log.h"
#include "Utilities\Debug.h"
#include "Utilities\Colors.h"
#include "Utilities\Timer.h"	
#include "Event.h"
#include "PlayerInput.h"
#include "Grid.h"

// Mouse Drag and Drop
static Entity* s_SelectedEntity = nullptr;
static double s_PressedX = 0.0f;
static double s_PressedY = 0.0f;

Game::Game(int height, int width)
	: m_EntityVB(Defaults::Positions, Defaults::PositionsSize)
	, m_EntityIB(Defaults::Indices, Defaults::IndicesCount)
	, m_EntityShader("res/shaders/Texture.shader")
	, m_Viewport(width, height)
	, m_TextureTest("res/textures/1024_13.png")
	, m_BackgroundTexture("res/textures/background.png")
	, m_BackgroundImage(TransformComponent({ 0.0f,0.0f,0.0f }), SpriteSheetComponent(&m_BackgroundTexture))
{
	constexpr int totalPieces = 32;
	m_EntityPool.reserve(totalPieces);

	CalculateProjectionViewMatrix();
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
	m_EntityPool.emplace_back(Entity(TransformComponent({ 0.0f,0.0f,0.0f }, { 0.75f,0.75f,1.0f }), SpriteSheetComponent(&m_TextureTest)));

	m_GridSystem.AddNewChessPiece(&m_EntityPool[0], 0);
}

void Game::OnUpdate(const DeltaTime& deltaTime)
{

}

void Game::OnRender()
{
	DrawBackground();
	DrawEntites();
}

void Game::OnDestroy()
{
}

void Game::DrawBackground()
{
	glm::mat4 model = m_BackgroundImage.GetTransformComponent().GetTransformationMatrix();
	glm::mat4 mvp = m_ProjectionView * model;

	m_EntityShader.Bind();
	m_EntityShader.SetUniformMat4f("u_MVP", mvp);
	m_BackgroundImage.GetSpriteSheetComponent().BindTexture();
	m_EntityShader.SetUniform1i("u_Texture", 0);

	Renderer::Get().Draw(m_VertexArray, m_EntityIB);
}

void Game::AdjustBackgroundImage()
{
	// Centering Calculation based on (0.0 , 0.0) position

	// Calculate the Scale for the background to fit to the window
	float xNewScale = m_Viewport.x / (Defaults::MAX_POSITION_OFFSET);
	float yNewScale = m_Viewport.y / (Defaults::MAX_POSITION_OFFSET);

	m_BackgroundImage.GetScale().x = xNewScale;
	m_BackgroundImage.GetScale().y = yNewScale;

	// center of the window
	float windowCenterX = (float)m_Viewport.x / 2.0f;
	float windowCenterY = (float)m_Viewport.y / 2.0f;

	// center of the quad
	float quadCenterX = (Defaults::MAX_POSITION_OFFSET * xNewScale) / 2.0f;
	float quadCenterY = (Defaults::MAX_POSITION_OFFSET * yNewScale) / 2.0f;

	m_BackgroundImage.GetTranslation().x = windowCenterX - quadCenterX;
	m_BackgroundImage.GetTranslation().y = windowCenterY - quadCenterY;
}

void Game::DrawBackgroundManually()
{
	std::vector<Entity> backgroundFields;
	backgroundFields.reserve(64);

	Shader backgroundShader("res/shaders/Color.shader");

	const float quadWidth = m_Viewport.x / 8;
	const float quadHeight = m_Viewport.y / 8;

	float xNewScale = quadWidth / (Defaults::MAX_POSITION_OFFSET);
	float yNewScale = quadHeight / (Defaults::MAX_POSITION_OFFSET);

	float xOffset = 0.0f;
	float yOffset = 0.0f;

	Colors::RGBA color = Colors::Black;

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			backgroundFields.emplace_back(Entity(TransformComponent({ xOffset,yOffset,0.0f }, { xNewScale,yNewScale,1.0f }), SpriteSheetComponent(color)));
			xOffset += quadWidth;
			if (x != 7)
				color = (color == Colors::Black) ? Colors::White : Colors::Black;
		}

		xOffset = 0.0f;
		yOffset += quadHeight;
	}

	backgroundShader.Bind();
	for (int i = 0; i < backgroundFields.size(); i++)
	{
		Entity& entity = backgroundFields[i];
		glm::mat4 model = entity.GetTransformComponent().GetTransformationMatrix();
		glm::mat4 mvp = m_ProjectionView * model;
		backgroundShader.SetUniformMat4f("u_MVP", mvp);

		entity.GetSpriteSheetComponent().BindTexture();
		backgroundShader.SetUniform4f("u_Color", entity.GetSpriteSheetComponent().Color);

		Renderer::Get().Draw(m_VertexArray, m_EntityIB);
	}
}

void Game::DrawEntites()
{
	m_EntityShader.Bind();

	for (int i = 0; i < m_EntityPool.size(); i++)
	{
		Entity& entity = m_EntityPool[i];
		glm::mat4 model = entity.GetTransformComponent().GetTransformationMatrix();
		glm::mat4 mvp = m_ProjectionView * model;
		m_EntityShader.SetUniformMat4f("u_MVP", mvp);

		entity.GetSpriteSheetComponent().BindTexture();
		m_EntityShader.SetUniform1i("u_Texture", 0);

		Renderer::Get().Draw(m_VertexArray, m_EntityIB);
	}
}

void Game::CalculateProjectionViewMatrix()
{
	const glm::mat4 proj = glm::ortho(0.0f, m_Viewport.x, 0.0f, m_Viewport.y, -1.0f, 1.0f);
	m_ProjectionView = proj * glm::mat4(1.0f); // proj * view (Camera Pos(1.0f,1.0f))
}

void Game::OnMousePressed(MouseButtonPressedEvent& event)
{
	s_PressedX = event.GetXPosition();
	s_PressedY = m_Viewport.y - event.GetYPosition();// Mouse Position beginn from TOP-Left, but it should be from Bottom-Left

	Debug::Log("Grid {0}", m_GridSystem.HasChessPiece(m_GridSystem.GetChessPieceIndex(s_PressedX, s_PressedY, m_Viewport)) != nullptr);
}

void Game::OnMouseReleased(MouseButtonReleasedEvent& event)
{
	s_SelectedEntity = nullptr;
	s_PressedX = 0.0f;
	s_PressedY = 0.0f;
}

void Game::OnMouseMove(MouseMoveEvent& event)
{
	if (s_SelectedEntity == nullptr)
		return;

	double xOffset = (event.GetXPos() - s_PressedX);
	double yOffset = ((m_Viewport.y - event.GetYPos()) - s_PressedY);

	auto& location = s_SelectedEntity->GetTranslation();
	location.x += (float)xOffset;
	location.y += (float)yOffset;

	s_PressedX = event.GetXPos();
	s_PressedY = m_Viewport.y - event.GetYPos();
}

void Game::UpdateViewport(int width, int height)
{
	m_Viewport.x = (float)width;
	m_Viewport.y = (float)height;

	CalculateProjectionViewMatrix();
	AdjustBackgroundImage();
}