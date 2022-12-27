#include "pch.h"
#include "Grid.h"

Grid::Grid(int rowsCount, int columnsCount)
	: m_Rows(rowsCount), m_Columns(columnsCount)
{
	m_GridSystem.resize(rowsCount * columnsCount);
}

Grid::~Grid()
{
}

void Grid::UpdateChessPiecePosition(Entity* piece, const glm::vec2& newPosition)
{
}

Entity* Grid::HasChessPiece(int index)
{
	return m_GridSystem[index].ChessPiece;
}

int Grid::GetChessPieceIndex(double mouseX, double mouseY, const glm::vec2& viewport)
{
	float colHeight = viewport.y / m_Columns;
	float rowWidth = viewport.x / m_Rows;

	int rowIndex = mouseX / rowWidth;
	int columnIndex = mouseY / colHeight;

	return columnIndex * m_Rows + rowIndex;
}

void Grid::AddNewChessPiece(Entity* piece, int index)
{
	m_GridSystem[index].ChessPiece = piece;
}
