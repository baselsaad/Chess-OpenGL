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

// Mouse Drag and Drop
struct DragAndDrop
{
	glm::vec2 OrginalPosition;
	double PressedX = 0.0f;
	double PressedY = 0.0f;
	int EntityID = Chessboard::INVALID;
};
static DragAndDrop s_DragDropData;

Game::Game(int height, int width)
	: m_EntityVB(Defaults::Positions, Defaults::PositionsSize)
	, m_EntityIB(Defaults::Indices, Defaults::IndicesCount)
	, m_EntityShader("res/shaders/Texture.shader")
	, m_Viewport(width, height)
	, m_TextureTest("res/textures/1024_13.png")
	, m_BackgroundTexture("res/textures/background.png")
	, m_BackgroundImage(TransformComponent({ 0.0f,0.0f,0.0f }), SpriteSheetComponent(&m_BackgroundTexture))
{
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

	m_Chessboard.UpdateViewPort(m_Viewport);
	AdjustBackgroundImage();

	m_Chessboard.AddNewChessPiece(m_TextureTest, 0, 0);
	m_Chessboard.AddNewChessPiece(m_TextureTest, 1, 0);
}

void Game::OnUpdate(const DeltaTime& deltaTime)
{
}

void Game::OnRender()
{
	DrawBackgroundManually();
	//DrawBackground();
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
	// Calculate the Scale for the background to fit to the window
	const float xNewScale = m_Viewport.x / Defaults::MAX_POSITION_OFFSET;
	const float yNewScale = m_Viewport.y / Defaults::MAX_POSITION_OFFSET;

	m_BackgroundImage.GetScale().x = xNewScale;
	m_BackgroundImage.GetScale().y = yNewScale;

	// center of the window
	const float windowCenterX = m_Viewport.x / 2.0f;
	const float windowCenterY = m_Viewport.y / 2.0f;

	// center of the quad
	float quadCenterX = m_BackgroundImage.GetTransformComponent().GetCenterPositionInScreenSpace().x;
	float quadCenterY = m_BackgroundImage.GetTransformComponent().GetCenterPositionInScreenSpace().y;

	m_BackgroundImage.GetTranslation().x += windowCenterX - quadCenterX;
	m_BackgroundImage.GetTranslation().y += windowCenterY - quadCenterY;
}

void Game::DrawBackgroundManually()
{
	static Shader backgroundShader("res/shaders/Color.shader");
	backgroundShader.Bind();

	const float quadWidth = m_Viewport.x / 8;
	const float quadHeight = m_Viewport.y / 8;

	const float xNewScale = quadWidth / (Defaults::MAX_POSITION_OFFSET);
	const float yNewScale = quadHeight / (Defaults::MAX_POSITION_OFFSET);

	float xOffset = 0.0f;
	float yOffset = 0.0f;

	Colors::RGBA color = Colors::White;//Default

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			if ((y + x) % 2 == 0)
				color = Colors::White;
			else
				color = Colors::Black;

			// Later Submit to renderer (OpenGL-Core)
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(xOffset, yOffset, 1.0f))
					* glm::scale(glm::mat4(1.0f), glm::vec3(xNewScale, yNewScale, 1.0f));

				glm::mat4 mvp = m_ProjectionView * model;
				backgroundShader.SetUniformMat4f("u_MVP", mvp);
				backgroundShader.SetUniform4f("u_Color", color);
				Renderer::Get().Draw(m_VertexArray, m_EntityIB);
			}

			xOffset += quadWidth;
		}

		xOffset = 0.0f;
		yOffset += quadHeight;
	}
}

void Game::DrawEntites()
{
	const auto& entityPool = m_Chessboard.GetChessPieces();
	m_EntityShader.Bind();

	for (int i = 0; i < entityPool.size(); i++)
	{
		const Entity& entity = entityPool[i];
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
	s_DragDropData.PressedX = event.GetXPosition();
	s_DragDropData.PressedY = m_Viewport.y - event.GetYPosition();// Mouse Position beginn from TOP-Left, but it should be from Bottom-Left

	//Debug::Log("X: {0}, Y: {1}", s_PressedX, s_PressedY);

	s_DragDropData.EntityID = m_Chessboard.GetEntityID(s_DragDropData.PressedX, s_DragDropData.PressedY);

	// copy the location in case the move was invalid, so we set it back 
	if (s_DragDropData.EntityID != Chessboard::INVALID)
		s_DragDropData.OrginalPosition = m_Chessboard.GetEntityLocation(s_DragDropData.EntityID);

}

void Game::OnMouseReleased(MouseButtonReleasedEvent& event)
{
	if (s_DragDropData.EntityID != Chessboard::INVALID)
	{
		glm::vec2 entityLocation = m_Chessboard.GetEntityLocation(s_DragDropData.EntityID);
		glm::vec2 targetLocation = m_Chessboard.HasEntity(entityLocation.x, entityLocation.y) ? s_DragDropData.OrginalPosition : entityLocation;

		m_Chessboard.MoveEntityToCell(s_DragDropData.EntityID, targetLocation);
	}

	// reset
	s_DragDropData.PressedX = 0.0f;
	s_DragDropData.PressedY = 0.0f;
	s_DragDropData.EntityID = Chessboard::INVALID;
}

void Game::OnMouseMove(MouseMoveEvent& event)
{
	if (s_DragDropData.EntityID == Chessboard::INVALID)
		return;

	float xOffset = event.GetXPosition() - s_DragDropData.PressedX;
	float yOffset = (m_Viewport.y - event.GetYPosition()) - s_DragDropData.PressedY;
	m_Chessboard.MoveEntityByOffset(s_DragDropData.EntityID, xOffset, yOffset);

	s_DragDropData.PressedX = event.GetXPosition();
	s_DragDropData.PressedY = m_Viewport.y - event.GetYPosition();
}

void Game::OnUpdateViewport(int width, int height)
{
	m_Viewport.x = (float)width;
	m_Viewport.y = (float)height;

	CalculateProjectionViewMatrix();
	AdjustBackgroundImage();
	m_Chessboard.UpdateViewPort(m_Viewport);// To Update Cells
}