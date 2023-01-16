#include "pch.h"
#include "OpenGL-Core.h"
#include "Game.h"

#include "Renderer/Defaults.h"
#include "Utilities/DeltaTime.h"
#include "Utilities/Log.h"
#include "Utilities/Debug.h"
#include "Utilities/Timer.h"

#include "Event/Event.h"
#include "Event/Input.h"
#include "Event/PlayerInput.h"

#include "ChessPieces/ChessPiece.h"
#include "ChessPieces/MovesGen.h"

ChessTextures::ChessTextures(const Color& color)
	: SelectedColor(color)
	, Pawn("res/textures/" + ToString(color) + "Pawn.png")
	, Bishop("res/textures/" + ToString(color) + "Bishop.png")
	, Knight("res/textures/" + ToString(color) + "Knight.png")
	, Rook("res/textures/" + ToString(color) + "Rook.png")
	, Queen("res/textures/" + ToString(color) + "Queen.png")
	, King("res/textures/" + ToString(color) + "King.png")
{
}

// Mouse Drag and Drop
struct DragAndDrop
{
	glm::vec3 OrginalPosition = { 0.0f,0.0f,0.0f };
	MovesGen::Array PossibleMovesToDraw;

	int PieceID = Chessboard::INVALID;
	ChessPiece* SelectedPiece = nullptr;
	TeamColor CurrentTurn = TeamColor::White;

	void Reset()
	{
		// reset
		PieceID = Chessboard::INVALID;
		SelectedPiece = nullptr;
		PossibleMovesToDraw.Clear();
	}

	void ChangeTurn()
	{
		CurrentTurn = CurrentTurn == TeamColor::Black ? TeamColor::White : TeamColor::Black;
	}
};
static DragAndDrop s_DragDropData;

Game::Game()
	: m_BackgroundTexture("res/textures/background.png")
	, m_PossibleMovesTexture("res/textures/PossibleMoves.png")
	, m_BackgroundEntity()
	, m_WhitePiecesTex(ChessTextures::Color::White)
	, m_BlackPiecesTex(ChessTextures::Color::Black)
{
}

void Game::SetupPlayerInput(PlayerInput& input)
{
	input.BindAction(EventType::MouseButtonPressed, this, &Game::OnMousePressed);
	input.BindAction(EventType::MouseButtonReleased, this, &Game::OnMouseReleased);
}

void Game::OnStart()
{
	m_Chessboard.OnUpdateViewPort();
	m_BackgroundEntity.SetTexture(&m_BackgroundTexture);
	AdjustBackgroundImage();

	CreateChessPieces(m_EntityContainer, m_WhitePiecesTex, 1, 0);
	CreateChessPieces(m_EntityContainer, m_BlackPiecesTex, 6, 7);
}

void Game::CreateChessPieces(const EntityContainer& container, ChessTextures& textures, int pawns, int rest)
{
	TeamColor color = textures.SelectedColor == ChessTextures::Color::Black ? TeamColor::Black : TeamColor::White;

	for (int i = 0; i < 8; i++)
	{
		if (i == 0 || i == 7) //Rook
		{
			// Create New Entity and bind the move function in constructur
			ChessPiece* rook = container.CreateNewEntity(color, PieceType::Rook);
			rook->SetTexture(&textures.Rook);

			m_Chessboard.AddNewChessPiece(rook, i, rest);
		}
		else if (i == 1 || i == 6) //Knight
		{
			ChessPiece* knight = container.CreateNewEntity(color, PieceType::Knight);
			knight->SetTexture(&textures.Knight);

			m_Chessboard.AddNewChessPiece(knight, i, rest);
		}
		else if (i == 2 || i == 5) //Bishop
		{
			ChessPiece* bishop = container.CreateNewEntity(color, PieceType::Bishop);
			bishop->SetTexture(&textures.Bishop);

			m_Chessboard.AddNewChessPiece(bishop, i, rest);
		}
		else if (i == 3) // Queen
		{
			ChessPiece* queen = container.CreateNewEntity(color, PieceType::Queen);
			queen->SetTexture(&textures.Queen);

			m_Chessboard.AddNewChessPiece(queen, i, rest);
		}
		else if (i == 4) //King
		{
			ChessPiece* king = container.CreateNewEntity(color, PieceType::King);
			king->SetTexture(&textures.King);

			m_Chessboard.AddNewChessPiece(king, i, rest);
		}
	}

	// Pawns
	for (int i = 0; i < 8; i++)
	{
		ChessPiece* pawn = container.CreateNewEntity(color, PieceType::Pawn);
		pawn->SetTexture(&textures.Pawn);

		m_Chessboard.AddNewChessPiece(pawn, i, pawns);
	}

}

void Game::OnUpdate(const DeltaTime& deltaTime)
{
	OnRender();

	if (Input::IsMouseButtonDown(MouseButtonKey::Left))
	{
		if (s_DragDropData.SelectedPiece != nullptr)
		{
			s_DragDropData.SelectedPiece->OnDragToNewPosition(Input::GetMousePosition());
		}
	}
}

void Game::OnRender()
{
	// Background
	Renderer::Draw(m_BackgroundEntity.GetTransformationMatrix(), m_BackgroundEntity.GetTexture());
	//DrawBackgroundManually();

	DrawPossibleMoves();

	// ChessPieces
	m_EntityContainer.OnRender();
}

void Game::OnDestroy()
{
}

void Game::OnMousePressed(const MouseButtonPressedEvent& event)
{
	OnSelect(event.GetXPosition(), event.GetYPosition());
}

void Game::OnMouseReleased(const MouseButtonReleasedEvent& event)
{
	OnDeselect(event.GetXPosition(), event.GetYPosition());
}

void Game::OnSelect(float xPos, float yPos)
{
	if (s_DragDropData.SelectedPiece != nullptr)
	{
		OnDeselect(xPos, yPos);
	}

	int& outPieceID = s_DragDropData.PieceID;
	s_DragDropData.SelectedPiece = m_Chessboard.GetChessPiece(xPos, yPos, outPieceID);

	// copy the location in case the move was invalid, so we set it back 
	if (s_DragDropData.SelectedPiece != nullptr && s_DragDropData.SelectedPiece->GetTeamColor() == s_DragDropData.CurrentTurn)
	{
		s_DragDropData.OrginalPosition = s_DragDropData.SelectedPiece->GetPositionCenteredInScreenSpace();
		s_DragDropData.PossibleMovesToDraw = MovesGen::GetPossibleMoves(s_DragDropData.SelectedPiece, m_Chessboard);
	}
	else
	{
		s_DragDropData.Reset();
	}
}

void Game::OnDeselect(float xPos, float yPos)
{
	if (s_DragDropData.SelectedPiece != nullptr)
	{
		glm::vec2 targetLocation(xPos, yPos);
		bool success = m_Chessboard.MoveToNewCell(s_DragDropData.PieceID, targetLocation, s_DragDropData.PossibleMovesToDraw);

		if (success)
		{
			s_DragDropData.ChangeTurn();
			s_DragDropData.Reset();
		}
		else
		{
			s_DragDropData.SelectedPiece->OnDragToNewPosition(s_DragDropData.OrginalPosition);
		}
	}
}

void Game::OnUpdateViewport()
{
	AdjustBackgroundImage();
	m_Chessboard.OnUpdateViewPort();// Update Cells
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

			Renderer::Draw(transform, scale, color);

			xOffset += quadWidth;
		}

		xOffset = 0.0f;
		yOffset += quadHeight;
	}
}

void Game::DrawPossibleMoves()
{
	if (s_DragDropData.SelectedPiece == nullptr)
		return;

	const float quadWidth = Renderer::GetViewport().x / m_Chessboard.GetRowsCount();
	const float quadHeight = Renderer::GetViewport().y / m_Chessboard.GetColumnCount();

	const float xNewScale = (quadWidth - 10.0f) / (Defaults::MAX_POSITION_OFFSET);
	const float yNewScale = (quadHeight - 10.0f) / (Defaults::MAX_POSITION_OFFSET);

	for (const auto& i : s_DragDropData.PossibleMovesToDraw)
	{
		glm::vec2 position2d = m_Chessboard.CalcCellScreenPosition(i.TargetCell);
		glm::vec3 position3d(position2d.x + 5.0f, position2d.y + 5.0f, 1.0f);

		Renderer::Draw(position3d, glm::vec3(xNewScale, yNewScale, 1.0f), Colors::HighLightColor);
	}

}
