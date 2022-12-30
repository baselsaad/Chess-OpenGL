#include "pch.h"
#include "OpenGL-Core.h"
#include "Game.h"

#include "Utilities\DeltaTime.h"
#include "Renderer\Defaults.h"
#include "Utilities\Log.h"
#include "Utilities\Debug.h"
#include "Utilities\Timer.h"	
#include "Event.h"
#include "PlayerInput.h"
#include "Container.h"

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
	: m_Viewport(width, height)
	, m_TextureTest("res/textures/1024_13.png")
	, m_BackgroundTexture("res/textures/background.png")
	, m_BackgroundImage(nullptr)
{
}

void Game::SetupPlayerInput(PlayerInput* input)
{
	ASSERT(input, "input can not be null!!");

	input->BindActionEvent(EventType::MouseButtonPressed, this, &Game::OnMousePressed);
	input->BindActionEvent(EventType::MouseButtonReleased, this, &Game::OnMouseReleased);
	input->BindActionEvent(EventType::MouseMove, this, &Game::OnMouseMove);
}

void Game::OnStart(EntityContainer& container)
{
	m_Chessboard.UpdateViewPort(m_Viewport);

	m_BackgroundImage = container.CreateNewEntity(TransformComponent({ 0.0f,0.0f,0.0f }), SpriteSheetComponent(&m_BackgroundTexture));
	AdjustBackgroundImage();

	Entity* test = container.CreateNewEntity(TransformComponent({ 0.0f,0.0f,0.0f }, { 75.0f,75.0f,1.0f }), SpriteSheetComponent(&m_TextureTest));
	m_Chessboard.AddNewChessPiece(test, 0, 0);
}

void Game::OnUpdate(const DeltaTime& deltaTime)
{
	//DrawBackgroundManually();

}

void Game::OnDestroy()
{
}

void Game::AdjustBackgroundImage()
{
	// Calculate the Scale for the background to fit to the window
	const float xNewScale = m_Viewport.x / Defaults::MAX_POSITION_OFFSET;
	const float yNewScale = m_Viewport.y / Defaults::MAX_POSITION_OFFSET;

	m_BackgroundImage->GetScale().x = xNewScale;
	m_BackgroundImage->GetScale().y = yNewScale;

	// center of the window
	const float windowCenterX = m_Viewport.x / 2.0f;
	const float windowCenterY = m_Viewport.y / 2.0f;

	// center of the quad
	float quadCenterX = m_BackgroundImage->GetTransformComponent().GetCenterPositionInScreenSpace().x;
	float quadCenterY = m_BackgroundImage->GetTransformComponent().GetCenterPositionInScreenSpace().y;

	m_BackgroundImage->GetTranslation().x += windowCenterX - quadCenterX;
	m_BackgroundImage->GetTranslation().y += windowCenterY - quadCenterY;
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

	AdjustBackgroundImage();
	m_Chessboard.UpdateViewPort(m_Viewport);// To Update Cells
}

void Game::DrawBackgroundManually()
{
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

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(xOffset, yOffset, 1.0f))
					* glm::scale(glm::mat4(1.0f), glm::vec3(xNewScale, yNewScale, 1.0f));

				Renderer::DrawQuad(model, color);
			}

			xOffset += quadWidth;
		}

		xOffset = 0.0f;
		yOffset += quadHeight;
	}
}