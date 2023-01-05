#include "pch.h"
#include "OpenGL-Core.h"
#include "ChessPiece.h"

#include "Chessboard.h"

ChessPiece::ChessPiece(const glm::vec3& position, const glm::vec3& scale)
	: Entity(position, scale)
	, m_RowIndex(0), m_ColumnIndex(0), m_FirstMove(true)
{
}

int ChessPiece::GetValidCell(const int& targetRow, const int& targetColumn, const int& maxRows)
{
	//Edge Case
	if (targetRow < 0 || targetRow >= maxRows || targetColumn < 0 || targetColumn >= maxRows)
		return Chessboard::INVALID;

	return targetColumn * maxRows + targetRow;
}
