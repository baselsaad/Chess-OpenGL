#include "pch.h"
#include "OpenGL-Core.h"
#include "Rook.h"
#include "Chessboard.h"

const Array Rook::GetPossibleMoves(const Chessboard& board) const
{
	Array outMoves;
	int moveDir = (int)GetPieceColor();

	std::array<std::pair<int, int>, 8> possibleMoves =
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

	int increamentRow = GetRowIndex();
	int increamentCol = GetColumnIndex();

	while (true)
	{
		increamentRow += row;
		increamentCol += column;
		int targetCell = GetCellIndex(increamentRow, increamentCol, board.GetRowsCount());

		bool notValidCell = board.GetCellState(targetCell) == CellState::NotValidCell;
		if (notValidCell)
			break;

		const ChessPiece* piece = board.GetChessPiece(targetCell);
		if (piece && piece->GetPieceColor() == GetPieceColor())
		{
			return;
		}
		else if (piece && piece->GetPieceColor() != GetPieceColor())
		{
			outMoves.Add(targetCell);
			break;
		}


		outMoves.Add(targetCell);
	}

}