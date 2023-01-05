#include "pch.h"
#include "OpenGL-Core.h"
#include "Pawn.h"

constexpr int INVALID_MOVE = -1;

int GetCell(const int& targetRow, const int& targetColumn, const int& maxRows)
{
	//Edge Case
	if (targetRow < 0 || targetRow >= maxRows || targetColumn < 0 || targetColumn >= maxRows)
		return INVALID_MOVE;

	return targetColumn * maxRows + targetRow;
}

const std::vector<int> Pawn::GetPossibleMoves(const int& maxRows) const
{
	std::vector<int> outMoves;
	outMoves.reserve(3);

	outMoves.emplace_back(GetCell(m_RowIndex, m_ColumnIndex + 1, maxRows)); // first move forward
	outMoves.emplace_back(GetCell(m_RowIndex + 1, m_ColumnIndex + 1, maxRows)); // Attack Move TOP-RIGHT
	outMoves.emplace_back(GetCell(m_RowIndex - 1, m_ColumnIndex + 1, maxRows)); // Attack Move TOP-LEFT

	return outMoves;
}