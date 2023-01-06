#include "pch.h"
#include "OpenGL-Core.h"
#include "Chessboard.h"

using CellState = Chessboard::CellState;

Chessboard::Chessboard(int rowsCount, int columnsCount)
	: m_Rows(rowsCount)
	, m_Columns(columnsCount)
{
	m_Cells.resize(rowsCount * columnsCount);
}

Chessboard::~Chessboard()
{
}

void Chessboard::OnUpdateViewPort()
{
	for (auto& piece : m_Cells)
	{
		if (piece == nullptr)
			continue;

		const glm::vec2 center = CalcCellScreenPosition(piece->GetRowIndex(), piece->GetColumnIndex());
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

	// Translate Entity
	auto& translation = entity->GetPosition();
	auto& entityOrgin = entity->GetPositionCenteredInScreenSpace();
	translation.x += newPosition.x - entityOrgin.x;
	translation.y += newPosition.y - entityOrgin.y;
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

const Array Chessboard::GetPossibleMoves(int entityID)
{
	return m_Cells[entityID]->GetPossibleMoves(*this);
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

bool Chessboard::MoveToNewCell(int entityID, const glm::vec2& newPosition)
{
	ASSERT(entityID >= 0 && entityID < m_Cells.size(), "Invalid Entity ID!!");

	ChessPiece* entity = m_Cells[entityID];

	glm::vec2 indices = GetRowAndColumnIndex(newPosition.x, newPosition.y);
	int targetCell = indices.y * m_Rows + indices.x;

	Array possibleMoves = entity->GetPossibleMoves(*this);

	for (const auto& cell : possibleMoves)
	{
		if (cell == targetCell)
		{
			// Clear orginal cell
			m_Cells[entityID] = nullptr;
			MoveToNewCell(entity, targetCell, indices);

			return true;
		}
	}

	return false;
}

void Chessboard::MoveToNewCell(ChessPiece* entity, int targetCell, const glm::vec2& rowAndColumnIndex)
{
	const glm::vec2 centerCell = CalcCellScreenPosition(rowAndColumnIndex.x, rowAndColumnIndex.y);

	// Translate Entity
	entity->OnMoveToNewPosition(glm::vec2(centerCell.x, centerCell.y));

	// Kill
	if (m_Cells[targetCell] != nullptr)
	{
		m_Cells[targetCell]->SetActive(false);
	}

	m_Cells[targetCell] = entity;
	entity->SetRowIndex(rowAndColumnIndex.x);
	entity->SetColumnIndex(rowAndColumnIndex.y);
}

glm::vec2 Chessboard::GetRowAndColumnIndex(double mouseX, double mouseY) const
{
	float rowWidth = Renderer::GetViewport().x / m_Rows;
	float colHeight = Renderer::GetViewport().y / m_Columns;

	int rowIndex = mouseX / rowWidth;
	int columnIndex = mouseY / colHeight;

	int safeRowIndex = glm::min(m_Rows - 1, rowIndex);
	int safeColumnIndex = glm::min(m_Columns - 1, columnIndex);

	return glm::vec2(safeRowIndex, safeColumnIndex);
}

glm::vec2 Chessboard::CalcCellScreenPosition(int row, int column) const
{
	// width and height are the Top-Right Position of the first Cell in Screen Space
	float rowWidth = Renderer::GetViewport().x / m_Rows;
	float colHeight = Renderer::GetViewport().y / m_Columns;

	// Top-Right Position of the selected cell (Screen Space)
	float selectedRightPosition = (rowWidth * row);
	float selectedTopPosition = (colHeight * column);

	// Center Position of the wanted cell (Screen Space)
	float centerPosX = selectedRightPosition + (rowWidth / 2.0f);
	float centerPosY = selectedTopPosition + (colHeight / 2.0f);

	return glm::vec2(centerPosX, centerPosY);
}

glm::vec2 Chessboard::CalcCellScreenPosition(int cellIndex) const
{
	ASSERT(cellIndex >= 0 && cellIndex < m_Cells.size(), "Index is out of range!");

	int row = cellIndex % m_Columns;
	int col = cellIndex / m_Columns;

	// width and height are the Top-Right Position of the first Cell in Screen Space
	float rowWidth = Renderer::GetViewport().x / m_Rows;
	float colHeight = Renderer::GetViewport().y / m_Columns;

	// Top-Right Position of the selected cell (Screen Space)
	float selectedRightPosition = (rowWidth * row);
	float selectedTopPosition = (colHeight * col);

	return glm::vec2(selectedRightPosition, selectedTopPosition);
}