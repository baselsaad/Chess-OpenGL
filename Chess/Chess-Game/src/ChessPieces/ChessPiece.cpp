#include "pch.h"
#include "OpenGL-Core.h"
#include "ChessPiece.h"

#include "Chessboard.h"

ChessPiece::ChessPiece(const glm::vec3& position, const glm::vec3& scale)
	: Entity(position, scale)
	, m_RowIndex(0), m_ColumnIndex(0)
	, m_PieceColor(PieceColor::None)
	, m_FirstMove(true)
{
}

void ChessPiece::OnMoveToNewPosition(const glm::vec2& newPosition)
{
	m_FirstMove = false;

	auto entityOrgin = GetPositionCenteredInScreenSpace();
	m_Position.x += newPosition.x - entityOrgin.x;
	m_Position.y += newPosition.y - entityOrgin.y;
}

void ChessPiece::OnDragToNewPosition(const glm::vec2& newPosition)
{
	auto entityOrgin = GetPositionCenteredInScreenSpace();
	m_Position.x += newPosition.x - entityOrgin.x;
	m_Position.y += newPosition.y - entityOrgin.y;
}

int ChessPiece::GetCellIndex(const int& targetRow, const int& targetColumn, const int& maxRows)
{
	//Edge Case
	if (targetRow < 0 || targetRow >= maxRows || targetColumn < 0 || targetColumn >= maxRows)
		return Chessboard::INVALID;

	return targetColumn * maxRows + targetRow;
}
