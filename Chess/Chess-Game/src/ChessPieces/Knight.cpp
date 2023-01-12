#include "pch.h"
#include "OpenGL-Core.h"
#include "Knight.h"
#include "Chessboard.h"

const Array Knight::GetPossibleMoves(const Chessboard& board) const
{
	Array outMoves;
	int moveDir = (int)GetTeamColor();

	std::array<std::pair<int, int>, 4> possibleMoves =
	{
		std::pair(-2, (+1 * moveDir)),	// L-Up-Left
		std::pair(+2, (+1 * moveDir)),	// L-Up-Right

		std::pair(-2, (-1 * moveDir)),	// L-Down-Left
		std::pair(+2, (-1 * moveDir)),	// L-Down-Right
	};

	
	for (const auto& target : possibleMoves)
	{
		TryToAddMoves(target.first, target.second, board, outMoves);
	}

	for (const auto& target : possibleMoves)
	{
		TryToAddMoves(target.second, target.first, board, outMoves);
	}

	return outMoves;
}

void Knight::TryToAddMoves(int row, int column, const Chessboard& board, Array& outMoves) const
{
	using CellState = Chessboard::CellState;

	int targetCell = GetCellIndex(m_RowIndex + row, m_ColumnIndex + column, board.GetRowsCount());
	bool notValidCell = board.GetCellState(targetCell) == CellState::NotValidCell;
	if (notValidCell)
		return;

	const ChessPiece* piece = board.GetChessPiece(targetCell);
	if (piece && piece->GetTeamColor() == GetTeamColor())
		return;

	outMoves.Add(targetCell);
}