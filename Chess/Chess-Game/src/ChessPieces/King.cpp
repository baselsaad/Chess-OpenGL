#include "pch.h"
#include "OpenGL-Core.h"
#include "King.h"

#include "Chessboard.h"

const Array King::GetPossibleMoves(const Chessboard& board) const
{
	Array outMoves;

	const int moveDir = (int)m_PieceColor;
	const int maxRows = board.GetRowsCount();

	std::array<int, 8> possibleMoves =
	{
		GetCellIndex(m_RowIndex, m_ColumnIndex + (1 * moveDir), maxRows),		// Up
		GetCellIndex(m_RowIndex - 1, m_ColumnIndex, maxRows),					// Left
		GetCellIndex(m_RowIndex + 1, m_ColumnIndex, maxRows),					// Right
		GetCellIndex(m_RowIndex, m_ColumnIndex - (1 * moveDir), maxRows),		// Down

		GetCellIndex(m_RowIndex - 1, m_ColumnIndex + (1 * moveDir), maxRows),	// Forward-Left
		GetCellIndex(m_RowIndex + 1, m_ColumnIndex + (1 * moveDir), maxRows),	// Forward-Right

		GetCellIndex(m_RowIndex - 1, m_ColumnIndex - (1 * moveDir), maxRows),	// Down-Left
		GetCellIndex(m_RowIndex + 1, m_ColumnIndex - (1 * moveDir), maxRows),	// Down-Right
	};

	for (const int& targetCell : possibleMoves)
	{
		if (CheckMove(board, targetCell))
			outMoves.Add(targetCell);
	}

	return outMoves;
}

bool King::CheckMove(const Chessboard& board, int cellIndex) const
{
	using CellState = Chessboard::CellState;

	if (board.GetCellState(cellIndex) != CellState::NotValidCell)
	{
		const ChessPiece* piece = board.GetChessPiece(cellIndex);
		// if there is no piece , or the piece is for the other team
		if (piece == nullptr || piece->GetTeamColor() != m_PieceColor)
			return true;
	}

	return false;
}

