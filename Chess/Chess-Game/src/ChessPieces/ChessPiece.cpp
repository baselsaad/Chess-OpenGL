#include "pch.h"
#include "OpenGL-Core.h"
#include "ChessPiece.h"

ChessPiece::ChessPiece(const glm::vec3& position, const glm::vec3& scale)
	: Entity(position, scale)
{
}

ChessPiece::ChessPiece(const FuncType& func, const glm::vec3& position, const glm::vec3& scale)
	: m_GetPossibleMoves(func)
	, Entity(position, scale)
{
}

const std::vector<int> ChessPiece::GetPossibleMoves(const int& maxRows) const
{
	ASSERT(m_GetPossibleMoves, "There is no Implementation for the Possible Moves!!");
	return m_GetPossibleMoves(m_RowIndex, m_ColumnIndex, maxRows);
}
