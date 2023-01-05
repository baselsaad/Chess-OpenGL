#include "pch.h"
#include "OpenGL-Core.h"
#include "ChessPiece.h"

ChessPiece::ChessPiece(const glm::vec3& position, const glm::vec3& scale)
	: Entity(position, scale)
	, m_RowIndex(0), m_ColumnIndex(0), m_FirstMove(true)
{
}

const std::vector<int> ChessPiece::GetPossibleMoves(const int& maxRows) const
{
	ASSERT(false, "There is no Implementation for the Possible Moves!!");
	return {};
}
