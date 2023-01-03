#include "pch.h"
#include "OpenGL-Core.h"
#include "ChessPiece.h"

ChessPiece::ChessPiece(const glm::vec3& position, const glm::vec3& scale)
	: Entity(position, scale)
{
}

const std::vector<int> ChessPiece::GetPossibleMoves() const
{
	ASSERT(m_GetPossibleMoves, "There is no Implemention for PossibleMoves Function!!");
	return m_GetPossibleMoves();
}
