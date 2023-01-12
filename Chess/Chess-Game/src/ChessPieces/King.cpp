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
		{
			Move move;
			move.TargetCell = targetCell;
			outMoves.Add(move);
		}
	}

	// Check for "is king in check before"
	{
		TryKingSideCastle(board, outMoves);
		TryQueenSideCastle(board, outMoves);
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

void King::TryQueenSideCastle(const Chessboard& board, Array& outMoves) const
{
	if (!m_FirstMove)
		return;

	// rook was killed or moved before
	const ChessPiece* rook = board.GetChessPiece(GetCellIndex(m_RowIndex - 4, m_ColumnIndex, board.GetRowsCount()));
	if (rook == nullptr || !rook->IsActive() || !rook->IsFirstMove())
		return;

	for (int i = 1; i <= 3; i++)
	{
		int row = m_RowIndex - i;
		int cellIndex = GetCellIndex(row, m_ColumnIndex, board.GetRowsCount());

		if (board.GetChessPiece(cellIndex) != nullptr)
			return;
	}

	Move move;
	move.TargetCell = GetCellIndex(m_RowIndex - 2, m_ColumnIndex, board.GetRowsCount());
	move.Flag = MovesFlag::QueenSideCastling;
	outMoves.Add(move);

}

void King::TryKingSideCastle(const Chessboard& board, Array& outMoves) const
{
	if (!m_FirstMove)
		return;

	// rook was killed or moved before

	const ChessPiece* rook = board.GetChessPiece(GetCellIndex(m_RowIndex + 3, m_ColumnIndex, board.GetRowsCount()));
	if (rook == nullptr || !rook->IsActive() || !rook->IsFirstMove())
		return;

	for (int i = 1; i <= 2; i++)
	{
		int row = m_RowIndex + i;
		int cellIndex = GetCellIndex(row, m_ColumnIndex, board.GetRowsCount());

		if (board.GetChessPiece(cellIndex) != nullptr)
			return;
	}

	Move move;
	move.TargetCell = GetCellIndex(m_RowIndex + 2, m_ColumnIndex, board.GetRowsCount());
	move.Flag = MovesFlag::KingSideCastling;
	outMoves.Add(move);
}

