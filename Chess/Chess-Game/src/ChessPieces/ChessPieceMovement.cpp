#include "pch.h"
#include "OpenGL-Core.h"
#include "ChessPieceMovement.h"

namespace ChessPieceMovement
{
	constexpr int INVALID_MOVE = -1;

	int GetCell(const int& targetRow, const int& targetColumn, const int& maxRows)
	{
		//Edge Case
		if (targetRow < 0 || targetRow >= maxRows || targetColumn < 0 || targetColumn >= maxRows)
			return INVALID_MOVE;

		return targetColumn * maxRows + targetRow;
	}

	std::vector<int> PawnMovement(const int& currentRowIndex, const int& currentColumnIndex, const int& maxRows)
	{
		std::vector<int> outMoves;
		outMoves.reserve(3);

		outMoves.emplace_back(GetCell(currentRowIndex, currentColumnIndex + 1, maxRows)); // first move forward
		outMoves.emplace_back(GetCell(currentRowIndex + 1, currentColumnIndex + 1, maxRows)); // Attack Move TOP-RIGHT
		outMoves.emplace_back(GetCell(currentRowIndex - 1, currentColumnIndex + 1, maxRows)); // Attack Move TOP-LEFT

		return outMoves;
	}

}