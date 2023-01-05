#include "pch.h"
#include "OpenGL-Core.h"
#include "Pawn.h"

#include "Chessboard.h"

const std::vector<int> Pawn::GetPossibleMoves(const int& maxRows, const Chessboard& board) const
{
	std::vector<int> outMoves;
	outMoves.reserve(3);

	outMoves.emplace_back(GetValidCell(m_RowIndex, m_ColumnIndex + 1, maxRows)); // first move forward
	outMoves.emplace_back(GetValidCell(m_RowIndex + 1, m_ColumnIndex + 1, maxRows)); // Attack Move TOP-RIGHT
	outMoves.emplace_back(GetValidCell(m_RowIndex - 1, m_ColumnIndex + 1, maxRows)); // Attack Move TOP-LEFT

	return outMoves;
}