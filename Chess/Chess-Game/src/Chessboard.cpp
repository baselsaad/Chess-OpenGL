#include "pch.h"
#include "OpenGL-Core.h"
#include "Chessboard.h"
#include "ChessPieces\ChessPiece.h"


Chessboard::Chessboard(int rowsCount, int columnsCount)
	: m_Rows(rowsCount)
	, m_Columns(columnsCount)
{
	m_Cells.resize(rowsCount * columnsCount);
}

Chessboard::~Chessboard()
{
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
	glm::vec2 newPosition = GetCellScreenPosition(rowIndex, colIndex);

	// Translate Entity
	auto& translation = entity->GetPosition();
	auto& entityOrgin = entity->GetPositionCenteredInScreenSpace();
	translation.x += newPosition.x - entityOrgin.x;
	translation.y += newPosition.y - entityOrgin.y;
}

void Chessboard::GetChessPiece(double mouseX, double mouseY, int& outPieceID, ChessPiece** outPiecePtr)
{
	const auto& indecis = GetRowAndColumnIndex(mouseX, mouseY);
	const float& rowIndex = indecis.x;
	const float& columnIndex = indecis.y;
	int index = (int)(columnIndex * m_Rows + rowIndex);

	ASSERT(index >= 0 && index < m_Cells.size(), "Index is out of Range!!!");

	if (m_Cells[index] == nullptr)
	{
		outPieceID = Chessboard::INVALID;
		*outPiecePtr = nullptr;
		return;
	}

	outPieceID = index;
	*outPiecePtr = m_Cells[index];
}

std::vector<int> Chessboard::GetPossibleMoves(int entityID)
{
	return m_Cells[entityID]->GetPossibleMoves(m_Rows, *this);
}

bool Chessboard::DoesCellHaveEntity(double mouseX, double mouseY)
{
	int unUsedEntityID = 0;
	ChessPiece* ptr = nullptr;
	GetChessPiece(mouseX, mouseY, unUsedEntityID, &ptr);

	return ptr != nullptr;
}

void Chessboard::MoveToNewCell(int entityID, const glm::vec2& newPosition, const glm::vec3& orginalPosition)
{
	ASSERT(entityID >= 0 && entityID < m_Cells.size(), "Invalid Entity ID!!");

	ChessPiece* entity = m_Cells[entityID];

	// Get Cell Center-Position
	glm::vec2 outCellPosition;
	glm::vec2 outRowColumn;
	int outTargetCell = 0;
	ComputeCorrectCellPosition(newPosition, outCellPosition, outRowColumn, outTargetCell);
	std::vector<int> possibleMoves = entity->GetPossibleMoves(m_Rows, *this);

	for (int& i : possibleMoves)
	{
		if (i == outTargetCell)
		{
			// Translate Entity
			auto& translation = entity->GetPosition();
			auto& entityOrgin = entity->GetPositionCenteredInScreenSpace();
			translation.x += outCellPosition.x - entityOrgin.x;
			translation.y += outCellPosition.y - entityOrgin.y;

			// Add Entity to Cell
			m_Cells[entityID] = nullptr;
			m_Cells[outTargetCell] = entity;
			entity->SetRowIndex(outRowColumn.x);
			entity->SetColumnIndex(outRowColumn.y);
			return;
		}
	}

	// Move back 
	ComputeCorrectCellPosition(orginalPosition, outCellPosition, outRowColumn, outTargetCell);
	// Translate Entity
	auto& translation = entity->GetPosition();
	auto& entityOrgin = entity->GetPositionCenteredInScreenSpace();
	translation.x += outCellPosition.x - entityOrgin.x;
	translation.y += outCellPosition.y - entityOrgin.y;
}

//TODO: Another way to compute
void Chessboard::ComputeCorrectCellPosition(const glm::vec2& targetPosInScreenSpcae, glm::vec2& outCellPosition, glm::vec2& outRowColumn, int& outNewIndex)
{
	glm::vec2 indices = GetRowAndColumnIndex(targetPosInScreenSpcae.x, targetPosInScreenSpcae.y);
	outRowColumn.x = indices.x;
	outRowColumn.y = indices.y;
	outNewIndex = indices.y * m_Rows + indices.x;

	const glm::vec2 center = GetCellScreenPosition(indices.x, indices.y);

	outCellPosition.x = center.x;
	outCellPosition.y = center.y;
}

const glm::vec2 Chessboard::GetRowAndColumnIndex(double mouseX, double mouseY)
{
	float rowWidth = Renderer::GetViewport().x / m_Rows;
	float colHeight = Renderer::GetViewport().y / m_Columns;

	int rowIndex = mouseX / rowWidth;
	int columnIndex = mouseY / colHeight;

	int safeRowIndex = glm::min(m_Rows - 1, rowIndex);
	int safeColumnIndex = glm::min(m_Columns - 1, columnIndex);

	return glm::vec2(safeRowIndex, safeColumnIndex);
}

const glm::vec2 Chessboard::GetCellScreenPosition(int row, int column)
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

const glm::vec2 Chessboard::GetCellScreenPosition(int cellIndex)
{
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

void Chessboard::OnUpdateViewPort()
{
	for (auto& piece : m_Cells)
	{
		if (piece == nullptr)
			continue;

		const glm::vec2 center = GetCellScreenPosition(piece->GetRowIndex(), piece->GetColumnIndex());

		auto& translation = piece->GetPosition();
		auto& entityOrgin = piece->GetPositionCenteredInScreenSpace();

		translation.x += center.x - entityOrgin.x;
		translation.y += center.y - entityOrgin.y;
	}
}

