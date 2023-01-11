#include "pch.h"
#include "OpenGL-Core.h"
#include "Bishop.h"
#include "Chessboard.h"

const Array Bishop::GetPossibleMoves(const Chessboard& board) const
{
	Array outMoves;
	int moveDir = (int)GetTeamColor();

	std::array<std::pair<int, int>, 4> possibleMoves =
	{
		std::pair(-1, (+1 * moveDir)),	// Diagonal-Up-Left
		std::pair(+1, (+1 * moveDir)),	// Diagonal-Up-Right

		std::pair(-1, (-1 * moveDir)),	// Diagonal-Down-Left
		std::pair(+1, (-1 * moveDir)),	// Diagonal-Down-Right
	};

	for (const auto& targetCell : possibleMoves)
	{
		TryToAddMoves(targetCell.first, targetCell.second, board, outMoves);
	}


	return outMoves;
}

void Bishop::TryToAddMoves(int row, int column, const Chessboard& board, Array& outMoves) const
{
	using CellState = Chessboard::CellState;

	int targetRow = m_RowIndex + row;
	int targetCol = m_ColumnIndex + column;
	int targetCell = GetCellIndex(targetRow, targetCol, board.GetRowsCount());

	while (board.GetCellState(targetCell) != CellState::NotValidCell)
	{
		const ChessPiece* piece = board.GetChessPiece(targetCell);
		if (piece != nullptr)// => there is a piece and we can not move anymore
		{
			if (piece->GetTeamColor() != GetTeamColor())
				outMoves.Add(targetCell);

			break;
		}

		outMoves.Add(targetCell);

		targetRow += row;
		targetCol += column;
		targetCell = GetCellIndex(targetRow, targetCol, board.GetRowsCount());
	}

}