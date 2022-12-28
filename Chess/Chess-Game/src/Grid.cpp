#include "pch.h"
#include "Grid.h"
#include "Entity.h"
#include "Renderer\Defaults.h"



Grid::Grid(const glm::vec2& viewportResolution, int rowsCount, int columnsCount)
	: m_Rows(rowsCount), m_Columns(columnsCount), m_ViewportResolution(viewportResolution)
{
	m_Cells.resize(rowsCount * columnsCount);
}

Grid::~Grid()
{
}

void Grid::AddNewChessPiece(Entity* piece, int rowIndex, int colIndex)
{
	ASSERT(rowIndex >= 0 && rowIndex < m_Rows, "row Index is out of range!");
	ASSERT(colIndex >= 0 && colIndex < m_Columns, "colIndex Index is out of range!");

	int index = colIndex * m_Rows + rowIndex;
	MoveEntityToNewCell(piece, index, GetCellPosition(rowIndex + 1, colIndex + 1));
}

void Grid::GetEntity(double mouseX, double mouseY, int& outGridID, Entity** outEntity)
{
	int index = GetCellIndex(mouseX, mouseY);

	if (!m_Cells[index].HasEntity())
	{
		*outEntity = nullptr;
		outGridID = Grid::INVALID_ID;
		return;
	}

	*outEntity = m_Cells[index].ChessPiece;
	outGridID = index;
}

void Grid::MoveEntityToNewCell(Entity* entity, int oldID, const glm::vec2& newPosition)
{
	glm::vec2 outPosition;
	int outCellIndex = 0;
	ComputeCorrectCellPosition(newPosition, outPosition, outCellIndex);

	auto& translation = entity->GetTranslation();
	auto& entityOrgin = entity->GetTransformComponent().GetCenterPositionInScreenSpace();

	translation.x += outPosition.x - entityOrgin.x;
	translation.y += outPosition.y - entityOrgin.y;

	m_Cells[oldID].ResetData();
	m_Cells[outCellIndex].ChessPiece = entity;
}

void Grid::ComputeCorrectCellPosition(const glm::vec2& screenSpacePosition, glm::vec2& outCellPosition, int& outNewIndex)
{
	glm::vec2 indices = GetRowAndColumn(screenSpacePosition.x, screenSpacePosition.y);
	indices += 1.0f; // Start from 1 to 8 so can know which cell is wanted by multiplication

	const glm::vec2 center = GetCellPosition(indices.x, indices.y);

	outCellPosition.x = center.x;
	outCellPosition.y = center.y;

	outNewIndex = GetCellIndex(center.x, center.y);
}

int Grid::GetCellIndex(double mouseX, double mouseY)
{
	const auto& indecis = GetRowAndColumn(mouseX, mouseY);
	const float& rowIndex = indecis.x;
	const float& columnIndex = indecis.y;

	return columnIndex * m_Rows + rowIndex;
}

const glm::vec2& Grid::GetRowAndColumn(double mouseX, double mouseY)
{
	float rowWidth = m_ViewportResolution.x / m_Rows;
	float colHeight = m_ViewportResolution.y / m_Columns;

	int rowIndex = mouseX / rowWidth;
	int columnIndex = mouseY / colHeight;

	return glm::vec2(rowIndex, columnIndex);
}

const glm::vec2 Grid::GetCellPosition(int row, int column)
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
