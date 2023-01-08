#include "pch.h"
#include "OpenGL-Core.h"
#include "King.h"

#include "Chessboard.h"

const Array King::GetPossibleMoves(const Chessboard& board) const
{
	Array outMoves;

	int moveDir = m_PieceColor == PieceColor::Black ? moveDir = -1 : 1;
	int maxRows = board.GetRowsCount();

	// Forward
	{
		int step = GetCellIndex(m_RowIndex, m_ColumnIndex + (1 * moveDir), maxRows);
		bool success = TryToAddMove(board, step);
		if (success)
			outMoves.Add(step);
	}

	// Left
	{
		int step = GetCellIndex(m_RowIndex - 1, m_ColumnIndex, maxRows);
		bool success = TryToAddMove(board, step);
		if (success)
			outMoves.Add(step);
	}

	// Right
	{
		int step = GetCellIndex(m_RowIndex + 1, m_ColumnIndex, maxRows);
		bool success = TryToAddMove(board, step);
		if (success)
			outMoves.Add(step);
	}

	// Back
	{
		int step = GetCellIndex(m_RowIndex, m_ColumnIndex - (1 * moveDir), maxRows);
		bool success = TryToAddMove(board, step);
		if (success)
			outMoves.Add(step);
	}

	// Top-Left
	{
		int step = GetCellIndex(m_RowIndex - 1, m_ColumnIndex + (1 * moveDir), maxRows);
		bool success = TryToAddMove(board, step);
		if (success)
			outMoves.Add(step);
	}

	//Top-Right
	{
		int step = GetCellIndex(m_RowIndex + 1, m_ColumnIndex + (1 * moveDir), maxRows);
		bool success = TryToAddMove(board, step);
		if (success)
			outMoves.Add(step);
	}

	// Bottom-Left
	{
		int step = GetCellIndex(m_RowIndex - 1, m_ColumnIndex - (1 * moveDir), maxRows);
		bool success = TryToAddMove(board, step);
		if (success)
			outMoves.Add(step);
	}

	// Bottom-Right
	{
		int step = GetCellIndex(m_RowIndex + 1, m_ColumnIndex - (1 * moveDir), maxRows);
		bool success = TryToAddMove(board, step);
		if (success)
			outMoves.Add(step);
	}


	return outMoves;
}

bool King::TryToAddMove(const Chessboard& board, int cellIndex) const
{
	using CellState = Chessboard::CellState;

	if (board.GetCellState(cellIndex) != CellState::NotValidCell)
	{
		const ChessPiece* piece = board.GetChessPiece(cellIndex);
		// if there no piece forward, or the piece for the other team
		if (piece == nullptr || piece->GetPieceColor() != m_PieceColor)
			return true;
	}

	return false;
}
