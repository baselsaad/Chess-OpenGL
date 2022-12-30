#include "pch.h"
#include "Entity.h"

#include "Chessboard.h"


Chessboard::Chessboard(const glm::vec2& viewportResolution, int rowsCount, int columnsCount)
	: m_Rows(rowsCount)
	, m_Columns(columnsCount)
	, m_ViewportResolution(viewportResolution)
{
	m_Cells.resize(rowsCount * columnsCount);
	m_EntityPool.reserve(32);
}

Chessboard::~Chessboard()
{
}

void Chessboard::AddNewChessPiece(Texture& test, int rowIndex, int colIndex)
{
	ASSERT(rowIndex >= 0 && rowIndex < m_Rows, "row Index is out of range!");
	ASSERT(colIndex >= 0 && colIndex < m_Columns, "column Index is out of range!");

	Entity& entity = m_EntityPool.emplace_back(Entity(TransformComponent({ 0.0f,0.0f,0.0f }, { 75.0f,75.0f,1.0f }), SpriteSheetComponent(&test)));

	int index = colIndex * m_Rows + rowIndex;

	m_Cells[index].ChessPiece = &entity;
	m_Cells[index].RowIndex = rowIndex;
	m_Cells[index].ColIndex = colIndex;

	MoveEntityToCell(index, GetCellPosition(rowIndex + 1, colIndex + 1));
}

int Chessboard::GetEntityID(double mouseX, double mouseY)
{
	int index = GetCellIndex(mouseX, mouseY);

	if (!m_Cells[index].HasEntity())
		return Chessboard::INVALID;

	return index;
}

bool Chessboard::HasEntity(double mouseX, double mouseY)
{
	return GetEntityID(mouseX, mouseY) != Chessboard::INVALID;
}

void Chessboard::MoveEntityToCell(int entityID, const glm::vec2& newPosition)
{
	ASSERT(entityID >= 0 && entityID < m_Cells.size(), "Invalid Entity ID!!");

	Entity* entity = m_Cells[entityID].ChessPiece;

	// Get Cell Center-Position
	glm::vec2 outCellPosition;
	glm::vec2 outRowColumn;
	int outTargetCell = 0;
	ComputeCorrectCellPosition(newPosition, outCellPosition, outRowColumn, outTargetCell);
	ASSERT(outTargetCell >= 0 && outTargetCell < m_Cells.size(), "Invalid Entity ID!!");

	// Translate Entity
	auto& translation = entity->GetTranslation();
	auto& entityOrgin = entity->GetTransformComponent().GetCenterPositionInScreenSpace();
	translation.x += outCellPosition.x - entityOrgin.x;
	translation.y += outCellPosition.y - entityOrgin.y;

	// Add Entity to Cell and delete old one 
	m_Cells[entityID].ResetData();

	m_Cells[outTargetCell].ChessPiece = entity;
	m_Cells[outTargetCell].RowIndex = outRowColumn.x;
	m_Cells[outTargetCell].ColIndex = outRowColumn.y;
}

//TODO: Another way to compute
void Chessboard::ComputeCorrectCellPosition(const glm::vec2& screenSpacePosition, glm::vec2& outCellPosition, glm::vec2& outRowColumn, int& outNewIndex)
{
	glm::vec2 indices = GetRowAndColumn(screenSpacePosition.x, screenSpacePosition.y);
	outRowColumn.x = indices.x;
	outRowColumn.y = indices.y;
	outNewIndex = indices.y * m_Rows + indices.x;

	// Start from 1 to 8 so can know which cell is wanted by multiplication
	indices += 1.0f;
	const glm::vec2 center = GetCellPosition(indices.x, indices.y);

	outCellPosition.x = center.x;
	outCellPosition.y = center.y;
}

int Chessboard::GetCellIndex(double mouseX, double mouseY)
{
	const auto& indecis = GetRowAndColumn(mouseX, mouseY);
	const float& rowIndex = indecis.x;
	const float& columnIndex = indecis.y;

	return (int)(columnIndex * m_Rows + rowIndex);
}

const glm::vec2 Chessboard::GetRowAndColumn(double mouseX, double mouseY)
{
	float rowWidth = m_ViewportResolution.x / m_Rows;
	float colHeight = m_ViewportResolution.y / m_Columns;

	int rowIndex = mouseX / rowWidth;
	int columnIndex = mouseY / colHeight;

	return glm::vec2(rowIndex, columnIndex);
}

const glm::vec2 Chessboard::GetCellPosition(int row, int column)
{
	// width and height are the Top-Right Position of the first Cell in Screen Space
	float rowWidth = m_ViewportResolution.x / m_Rows;
	float colHeight = m_ViewportResolution.y / m_Columns;

	// Top-Right Position of the selected cell (Screen Space)
	float selectedRightPosition = (rowWidth * row);
	float selectedTopPosition = (colHeight * column);

	// Center Position of the wanted cell (Screen Space)
	float centerPosX = selectedRightPosition - (rowWidth / 2.0f);
	float centerPosY = selectedTopPosition - (colHeight / 2.0f);

	return glm::vec2(centerPosX, centerPosY);
}

void Chessboard::MoveEntityByOffset(const int& entityID, const float& xOffset, const float& yOffset)
{
	ASSERT(entityID >= 0 && entityID < m_Cells.size(), "Invalid Entity ID!!");

	auto& entityLocation = m_Cells[entityID].ChessPiece->GetTranslation();
	entityLocation.x += xOffset;
	entityLocation.y += yOffset;
}

void Chessboard::MoveEntityToNewPosition(int entityID, const glm::vec3& positionOffset)
{
	ASSERT(entityID >= 0 && entityID < m_Cells.size(), "Invalid Entity ID!!");
	m_Cells[entityID].ChessPiece->SetTranslation(positionOffset);
}

void Chessboard::UpdateViewPort(const glm::vec2& viewport)
{
	m_ViewportResolution = viewport;

	for (auto& cell : m_Cells)
	{
		if (cell.ChessPiece == nullptr)
			continue;

		const glm::vec2 center = GetCellPosition(cell.RowIndex + 1, cell.ColIndex + 1);

		auto& translation = cell.ChessPiece->GetTranslation();
		auto& entityOrgin = cell.ChessPiece->GetTransformComponent().GetCenterPositionInScreenSpace();

		translation.x += center.x - entityOrgin.x;
		translation.y += center.y - entityOrgin.y;
	}

}