#include "pch.h"
#include "OpenGL-Core.h"
#include "Chessboard.h"
#include "Utilities/Timer.h"

using CellState = Chessboard::CellState;

Chessboard::Chessboard(int rowsCount, int columnsCount)
	: m_Rows(rowsCount)
	, m_Columns(columnsCount)
	, m_RowWidth(Renderer::GetViewport().x / rowsCount)
	, m_ColHeight(Renderer::GetViewport().y / columnsCount)
	, m_WhiteKing(nullptr)
	, m_BlackKing(nullptr)
{
	m_Cells.resize(rowsCount * columnsCount);
	std::fill(&m_Cells[0], &m_Cells[0] + rowsCount * columnsCount, nullptr);
}

Chessboard::~Chessboard()
{
}

void Chessboard::OnUpdateViewPort()
{
	// width and height are the Top-Right Position of the first Cell in Screen Space
	m_RowWidth = Renderer::GetViewport().x / m_Rows;
	m_ColHeight = Renderer::GetViewport().y / m_Columns;

	for (auto& piece : m_Cells)
	{
		if (piece == nullptr)
			continue;

		glm::vec2 center = CalcCellScreenPosition(piece->GetRowIndex(), piece->GetColumnIndex());
		center = CalcCellCenterPosition(center.x, center.y);

		piece->OnDragToNewPosition(center);
	}
}

void Chessboard::AddNewChessPiece(ChessPiece* entity, int rowIndex, int colIndex)
{
	ASSERT(rowIndex >= 0 && rowIndex < m_Rows, "row Index is out of range!");
	ASSERT(colIndex >= 0 && colIndex < m_Columns, "column Index is out of range!");

	int index = colIndex * m_Rows + rowIndex;
	ASSERT(index >= 0 && index < m_Cells.size(), "Index is out of Range!!!");

	m_Cells[index] = entity;
	entity->SetRowIndex(rowIndex);
	entity->SetColumnIndex(colIndex);

	// Get Cell Center-Position
	glm::vec2 newPosition = CalcCellScreenPosition(rowIndex, colIndex);
	glm::vec2 center = CalcCellCenterPosition(newPosition.x, newPosition.y);

	// Translate Entity
	auto& translation = entity->GetPosition();
	auto& entityOrgin = entity->GetPositionCenteredInScreenSpace();
	translation.x += center.x - entityOrgin.x;
	translation.y += center.y - entityOrgin.y;
}

ChessPiece* Chessboard::GetChessPiece(double mouseX, double mouseY, int& outPieceID)
{
	const auto& indecis = GetRowAndColumnIndex(mouseX, mouseY);
	const float& rowIndex = indecis.x;
	const float& columnIndex = indecis.y;
	int index = (int)(columnIndex * m_Rows + rowIndex);

	ASSERT(index >= 0 && index < m_Cells.size(), "Index is out of Range!!!");

	if (m_Cells[index] == nullptr)
	{
		outPieceID = Chessboard::INVALID;
		return nullptr;
	}

	outPieceID = index;
	return m_Cells[index];
}

const ChessPiece* Chessboard::GetChessPiece(double mouseX, double mouseY) const
{
	const auto& indecis = GetRowAndColumnIndex(mouseX, mouseY);
	const float& rowIndex = indecis.x;
	const float& columnIndex = indecis.y;
	int index = (int)(columnIndex * m_Rows + rowIndex);

	if (index <  0 || index > m_Cells.size())
		return nullptr;


	return m_Cells[index];
}

const ChessPiece* Chessboard::GetChessPiece(int cellIndex) const
{
	if (cellIndex <  0 || cellIndex > m_Cells.size())
		return nullptr;

	return m_Cells[cellIndex];
}

const CellState Chessboard::GetCellState(int cellIndex) const
{
	if (cellIndex < 0 || cellIndex > m_Cells.size())
		return CellState::NotValidCell;
	else if (m_Cells[cellIndex] == nullptr)
		return CellState::EmptyCell;
	else
		return CellState::OccupiedCell;
}

bool Chessboard::MoveToNewCell(int startCell, const glm::vec2& newPosition, const MovesGen::Array& possibleMoves)
{
	ASSERT(startCell >= 0 && startCell < m_Cells.size(), "Invalid Entity ID!!");

	ChessPiece* piece = m_Cells[startCell];

	// Calculate the target cell based on the position where the mouse drops the piece
	glm::vec2 indices = GetRowAndColumnIndex(newPosition.x, newPosition.y);
	int targetCell = indices.y * m_Rows + indices.x;

	for (const auto& move : possibleMoves)
	{
		if (move.TargetCell == targetCell)
		{
			if (IsCheckAfterMoving(startCell, targetCell))
				return false;

			m_Cells[startCell] = nullptr;
			MoveToNewCell(piece, targetCell, indices);

			switch (move.Flag)
			{
				case MovesGen::MovesFlag::KingSideCastling:
				case MovesGen::MovesFlag::QueenSideCastling: HandleCastling(move.Flag, targetCell, piece); break;
			}

			return true;
		}
	}

	return false;
}

void Chessboard::MoveToNewCell(ChessPiece* piece, int targetCell, const glm::vec2& rowAndColumnIndex)
{
	const glm::vec2 cell = CalcCellScreenPosition(rowAndColumnIndex.x, rowAndColumnIndex.y);
	const glm::vec2 center = CalcCellCenterPosition(cell.x, cell.y);

	// Translate Entity
	piece->OnMoveToNewPosition(center);

	// Kill
	if (m_Cells[targetCell] != nullptr)
	{
		m_Cells[targetCell]->SetActive(false);
	}

	m_Cells[targetCell] = piece;
	piece->SetRowIndex(rowAndColumnIndex.x);
	piece->SetColumnIndex(rowAndColumnIndex.y);
}

glm::vec2 Chessboard::GetRowAndColumnIndex(double mouseX, double mouseY) const
{
	int rowIndex = mouseX / m_RowWidth;
	int columnIndex = mouseY / m_ColHeight;

	int safeRowIndex = glm::min(m_Rows - 1, rowIndex);
	int safeColumnIndex = glm::min(m_Columns - 1, columnIndex);

	return glm::vec2(safeRowIndex, safeColumnIndex);
}

void Chessboard::HandleCastling(const MovesGen::MovesFlag& flag, int kingTargetCell, ChessPiece* king)
{
	using namespace MovesGen;

	int rookRow = -1;
	int rookColumn = king->GetColumnIndex();

	int targetRow = -1;

	//King is allready moved
	switch (flag)
	{
		case MovesFlag::KingSideCastling:
		rookRow = king->GetRowIndex() + 1; // one cell right from King
		targetRow = king->GetRowIndex() - 1; // one cell left from King
		break;

		case MovesFlag::QueenSideCastling:
		rookRow = king->GetRowIndex() - 2;// tow cells right from King
		targetRow = king->GetRowIndex() + 1;// one cell right from King
		break;
	}

	int rookIndex = rookColumn * m_Rows + rookRow;
	int rookTargetCell = rookColumn * m_Rows + targetRow;

	//Move Rook
	ChessPiece* rook = m_Cells[rookIndex];
	m_Cells[rookIndex] = nullptr;// Clear orginal cell
	MoveToNewCell(rook, rookTargetCell, { targetRow,rookColumn });
}

bool Chessboard::IsCheckAfterMoving(int startCell, int targetCell)
{
	// Copy the start and target values
	ChessPiece* startPiece = m_Cells[startCell];
	ChessPiece* targetPiece = m_Cells[targetCell];

	int startPieceX = m_Cells[startCell]->GetRowIndex();
	int startPieceY = m_Cells[startCell]->GetColumnIndex();

	int targetPieceX = targetCell % m_Columns;
	int targetPieceY = targetCell / m_Columns;

	const ChessPiece* king = GetKing(startPiece->GetTeamColor());

	// Simulate the move and check if king in check 
	m_Cells[startCell] = nullptr;
	m_Cells[targetCell] = startPiece;
	startPiece->SetRowIndex(targetPieceX);
	startPiece->SetColumnIndex(targetPieceY);

	bool state = MovesGen::IsKingInCheck(*this, king);

	//Undo
	m_Cells[startCell] = startPiece;
	m_Cells[targetCell] = targetPiece;
	startPiece->SetRowIndex(startPieceX);
	startPiece->SetColumnIndex(startPieceY);

	return state;
}

glm::vec2 Chessboard::CalcCellScreenPosition(int row, int column) const
{
	// Top-Right Position of the selected cell (Screen Space)
	float selectedRightPosition = (m_RowWidth * row);
	float selectedTopPosition = (m_ColHeight * column);

	return glm::vec2(selectedRightPosition, selectedTopPosition);
}

glm::vec2 Chessboard::CalcCellCenterPosition(float xPos, float yPos)
{
	// Center Position of the wanted cell (Screen Space)
	float centerPosX = xPos + (m_RowWidth / 2.0f);
	float centerPosY = yPos + (m_ColHeight / 2.0f);

	return glm::vec2(centerPosX, centerPosY);
}

glm::vec2 Chessboard::CalcCellScreenPosition(int cellIndex) const
{
	ASSERT(cellIndex >= 0 && cellIndex < m_Cells.size(), "Index is out of range!");

	int row = cellIndex % m_Columns;
	int col = cellIndex / m_Columns;

	return CalcCellScreenPosition(row, col);
}