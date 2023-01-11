#include "pch.h"
#include "OpenGL-Core.h"
#include "Rook.h"
#include "Chessboard.h"

const Array Rook::GetPossibleMoves(const Chessboard& board) const
{
	Array outMoves;
	int moveDir = (int)GetPieceColor();

	std::array<std::pair<int, int>, 4> possibleMoves =
	{
		std::pair(0, (+1 * moveDir)),	// Up
		std::pair(-1, 0),				// Left
		std::pair(+1, 0),				// Right
		std::pair(0, (-1 * moveDir)),	// Down
	};


	for (const auto& targetCell : possibleMoves)
	{
		TryToAddMoves(targetCell.first, targetCell.second, board, outMoves);
	}

	return outMoves;
}

void Rook::TryToAddMoves(int row, int column, const Chessboard& board, Array& outMoves) const
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
			if (piece->GetPieceColor() != GetPieceColor())
				outMoves.Add(targetCell);

			break;
		}

		outMoves.Add(targetCell);

		targetRow += row;
		targetCol += column;
		targetCell = GetCellIndex(targetRow, targetCol, board.GetRowsCount());
	}

}