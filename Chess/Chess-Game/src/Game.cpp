#include "pch.h"
#include "OpenGL-Core.h"
#include "Game.h"

#include "Renderer\Defaults.h"
#include "Utilities\DeltaTime.h"
#include "Utilities\Log.h"
#include "Utilities\Debug.h"
#include "Utilities\Timer.h"	
#include "Event.h"
#include "PlayerInput.h"

#include "ChessPieces\ChessPiece.h"
#include "ChessPieces\Pawn.h"

ChessTextures::ChessTextures(const Color& color)
	: SelectedColor(color == Color::Black ? "Black" : "White")
	, Pawn("res/textures/" + SelectedColor + "Pawn.png")
	, Bishop("res/textures/" + SelectedColor + "Bishop.png")
	, Knight("res/textures/" + SelectedColor + "Knight.png")
	, Rook("res/textures/" + SelectedColor + "Rook.png")
	, Queen("res/textures/" + SelectedColor + "Queen.png")
	, King("res/textures/" + SelectedColor + "King.png")
{
}

// Mouse Drag and Drop
struct DragAndDrop
{
	glm::vec3 OrginalPosition;
	ChessPieceUtil::Array PossibleMovesToDraw;

	int EntityID = Chessboard::INVALID;
	ChessPiece* EntityPtr = nullptr;
};
static DragAndDrop s_DragDropData;

Game::Game(int height, int width)
	: m_BackgroundTexture("res/textures/background.png")
	, m_PossibleMovesTexture("res/textures/PossibleMoves.png")
	, m_BackgroundEntity()
	, m_WhitePieces(ChessTextures::Color::White)
	, m_BlackPieces(ChessTextures::Color::Black)
{
}

void Game::SetupPlayerInput(PlayerInput& input)
{
	input.BindActionEvent(EventType::MouseButtonPressed, this, &Game::OnMousePressed);
	input.BindActionEvent(EventType::MouseButtonReleased, this, &Game::OnMouseReleased);
	input.BindActionEvent(EventType::MouseMove, this, &Game::OnMouseMove);
}

void Game::OnStart()
{
	m_Chessboard.OnUpdateViewPort();
	m_BackgroundEntity.SetTexture(&m_BackgroundTexture);
	AdjustBackgroundImage();

	CreateChessPieces(m_EntityContainer, m_WhitePieces, 1, 0);
	CreateChessPieces(m_EntityContainer, m_BlackPieces, 6, 7);
}

void Game::CreateChessPieces(const EntityContainer& container, ChessTextures& textures, int pawns, int rest)
{
	PieceColor color = textures.SelectedColor == "Black" ? PieceColor::Black : PieceColor::White;

	for (int i = 0; i < 8; i++)
	{
		if (i == 0 || i == 7) //Rook
		{
			// Create New Entity and bind the move function in constructur
			ChessPiece* rook = container.CreateNewEntity<ChessPiece>();
			rook->SetTransform(Defaults::DefaultPosition, Defaults::DefaultScale);
			rook->SetTexture(&textures.Rook);
			rook->SetPieceColor(color);

			m_Chessboard.AddNewChessPiece(rook, i, rest);
		}
		else if (i == 1 || i == 6) //Knight
		{
			ChessPiece* knight = container.CreateNewEntity<ChessPiece>();
			knight->SetTransform(Defaults::DefaultPosition, Defaults::DefaultScale);
			knight->SetTexture(&textures.Knight);
			knight->SetPieceColor(color);

			m_Chessboard.AddNewChessPiece(knight, i, rest);
		}
		else if (i == 2 || i == 5) //Bishop
		{
			ChessPiece* bishop = container.CreateNewEntity<ChessPiece>();
			bishop->SetTransform(Defaults::DefaultPosition, Defaults::DefaultScale);
			bishop->SetTexture(&textures.Bishop);
			bishop->SetPieceColor(color);

			m_Chessboard.AddNewChessPiece(bishop, i, rest);
		}
		else if (i == 3) // Queen
		{
			ChessPiece* queen = container.CreateNewEntity<ChessPiece>();
			queen->SetTransform(Defaults::DefaultPosition, Defaults::DefaultScale);
			queen->SetTexture(&textures.Queen);
			queen->SetPieceColor(color);

			m_Chessboard.AddNewChessPiece(queen, i, rest);
		}
		else if (i == 4) //King
		{
			ChessPiece* king = container.CreateNewEntity<ChessPiece>();
			king->SetTransform(Defaults::DefaultPosition, Defaults::DefaultScale);
			king->SetTexture(&textures.King);
			king->SetPieceColor(color);

			m_Chessboard.AddNewChessPiece(king, i, rest);
		}
	}

	// Pawns
	for (int i = 0; i < 8; i++)
	{
		Pawn* pawn = container.CreateNewEntity<Pawn>();
		pawn->SetTransform(Defaults::DefaultPosition, Defaults::DefaultScale);
		pawn->SetTexture(&textures.Pawn);
		pawn->SetPieceColor(color);

		m_Chessboard.AddNewChessPiece(pawn, i, pawns);
	}

}

void Game::OnUpdate(const DeltaTime& deltaTime)
{
	// Background
	{
		Renderer::DrawQuad(m_BackgroundEntity.GetTransformationMatrix(), m_BackgroundEntity.GetTexture());
		//DrawBackgroundManually();
	}

	// DrawPossibleMoves
	if (s_DragDropData.EntityPtr != nullptr)
	{
		const float quadWidth = Renderer::GetViewport().x / m_Chessboard.GetRowsCount();
		const float quadHeight = Renderer::GetViewport().y / m_Chessboard.GetColumnCount();

		const float xNewScale = (quadWidth - 10.0f) / (Defaults::MAX_POSITION_OFFSET);
		const float yNewScale = (quadHeight - 10.0f) / (Defaults::MAX_POSITION_OFFSET);

		for (const int8_t& i : s_DragDropData.PossibleMovesToDraw)
		{
			glm::vec2 position2d = m_Chessboard.GetCellScreenPosition(i);
			glm::vec3 position3d(position2d.x + 5.0f, position2d.y + 5.0f, 1.0f);

			//Renderer::DrawQuad(position3d, glm::vec3(xNewScale, yNewScale, 1.0f), &m_PossibleMovesTexture);
			Renderer::DrawQuad(position3d, glm::vec3(xNewScale, yNewScale, 1.0f), Colors::HighLightColor);
		}
	}

	// ChessPieces
	m_EntityContainer.OnRender();
}

void Game::OnDestroy()
{
}

void Game::AdjustBackgroundImage()
{
	const glm::vec2& viewport = Renderer::GetViewport();
	// Calculate the Scale for the background to fit to the window
	const float xNewScale = viewport.x / Defaults::MAX_POSITION_OFFSET;
	const float yNewScale = viewport.y / Defaults::MAX_POSITION_OFFSET;

	m_BackgroundEntity.GetScale().x = xNewScale;
	m_BackgroundEntity.GetScale().y = yNewScale;

	// center of the window
	const float windowCenterX = viewport.x / 2.0f;
	const float windowCenterY = viewport.y / 2.0f;

	// center of the quad
	float quadCenterX = m_BackgroundEntity.GetPositionCenteredInScreenSpace().x;
	float quadCenterY = m_BackgroundEntity.GetPositionCenteredInScreenSpace().y;

	m_BackgroundEntity.GetPosition().x += windowCenterX - quadCenterX;
	m_BackgroundEntity.GetPosition().y += windowCenterY - quadCenterY;
}

void Game::OnMousePressed(MouseButtonPressedEvent& event)
{
	// event.GetYPosition() will get position from TOP-LEFT, viewport.y - event.GetYPosition will get from BOTTOM-LEFT
	double yPos = Renderer::GetViewport().y - event.GetYPosition();
	int& outEntityID = s_DragDropData.EntityID;
	s_DragDropData.EntityPtr = m_Chessboard.GetChessPiece(event.GetXPosition(), yPos, outEntityID);

	// copy the location in case the move was invalid, so we set it back 
	if (s_DragDropData.EntityPtr != nullptr)
	{
		s_DragDropData.OrginalPosition = s_DragDropData.EntityPtr->GetPositionCenteredInScreenSpace();
		s_DragDropData.PossibleMovesToDraw = m_Chessboard.GetPossibleMoves(s_DragDropData.EntityID);
	}

}

void Game::OnMouseReleased(MouseButtonReleasedEvent& event)
{
	if (s_DragDropData.EntityPtr != nullptr)
	{
		glm::vec3 entityLocation = s_DragDropData.EntityPtr->GetPositionCenteredInScreenSpace();
		// target cell has allready entity, then move the seleceted entity to his orginal location back
		glm::vec3 targetLocation = m_Chessboard.DoesCellHavePiece(entityLocation.x, entityLocation.y) ? s_DragDropData.OrginalPosition : entityLocation;

		m_Chessboard.MoveToNewCell(s_DragDropData.EntityID, targetLocation, s_DragDropData.OrginalPosition);
	}

	// reset
	s_DragDropData.EntityID = Chessboard::INVALID;
	s_DragDropData.EntityPtr = nullptr;
	s_DragDropData.PossibleMovesToDraw.Clear();
}

void Game::OnMouseMove(MouseMoveEvent& event)
{
	if (s_DragDropData.EntityPtr == nullptr)
		return;

	double xOffset = event.GetXPosition();
	double yOffset = (Renderer::GetViewport().y - event.GetYPosition());

	auto& position = s_DragDropData.EntityPtr->GetPosition();
	auto& orginPosition = s_DragDropData.EntityPtr->GetPositionCenteredInScreenSpace();
	position.x += (xOffset - orginPosition.x);
	position.y += (yOffset - orginPosition.y);
}

void Game::OnUpdateViewport()
{
	AdjustBackgroundImage();
	m_Chessboard.OnUpdateViewPort();// To Update Cells
}

void Game::DrawBackgroundManually()
{
	const float quadWidth = Renderer::GetViewport().x / m_Chessboard.GetRowsCount();
	const float quadHeight = Renderer::GetViewport().y / m_Chessboard.GetColumnCount();

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
				color = Colors::Black;
			else
				color = Colors::White;

			const glm::vec3 transform(xOffset, yOffset, 1.0f);
			const glm::vec3 scale(xNewScale, yNewScale, 1.0f);
			const glm::mat4 model = glm::translate(glm::mat4(1.0f), transform) * glm::scale(glm::mat4(1.0f), scale);

			Renderer::DrawQuad(model, color);

			xOffset += quadWidth;
		}

		xOffset = 0.0f;
		yOffset += quadHeight;
	}
}
