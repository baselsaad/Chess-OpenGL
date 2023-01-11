#include "pch.h"
#include "OpenGL-Core.h"
#include "Pawn.h"

#include "Chessboard.h"

const Array Pawn::GetPossibleMoves(const Chessboard& board) const
{
	using CellState = Chessboard::CellState;
	Array outMoves;

	int moveDir = (int)m_PieceColor;
	int maxRows = board.GetRowsCount();

	// Forward Move
	{
		int oneStepForward = GetCellIndex(m_RowIndex, m_ColumnIndex + (1 * moveDir), maxRows);

		if (board.GetCellState(oneStepForward) == CellState::EmptyCell)
		{
			outMoves.Add(oneStepForward);

			// Tow-Step Forward Move
			if (m_FirstMove)
			{
				int towStepForward = GetCellIndex(m_RowIndex, m_ColumnIndex + (2 * moveDir), maxRows);
				if (board.GetCellState(towStepForward) == CellState::EmptyCell)
					outMoves.Add(towStepForward);
			}
		}
	}

	// Attack Moves
	{
		int topLeft = GetCellIndex(m_RowIndex - 1, m_ColumnIndex + (1 * moveDir), maxRows);
		int topRight = GetCellIndex(m_RowIndex + 1, m_ColumnIndex + (1 * moveDir), maxRows);

		const ChessPiece* topLeftPiece = board.GetChessPiece(topLeft);
		const ChessPiece* topRightPiece = board.GetChessPiece(topRight);

		// if it has diffrent color then it is valid to attack 
		if (topLeftPiece && topLeftPiece->GetTeamColor() != m_PieceColor)
			outMoves.Add(topLeft);

		if (topRightPiece && topRightPiece->GetTeamColor() != m_PieceColor)
			outMoves.Add(topRight);
	}


	return outMoves;
}

