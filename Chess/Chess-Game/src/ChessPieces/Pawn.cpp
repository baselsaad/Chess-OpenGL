#include "pch.h"
#include "OpenGL-Core.h"
#include "Pawn.h"

#include "Chessboard.h"

const Array Pawn::GetPossibleMoves(const Chessboard& board) const
{
	using State = Chessboard::CellState;

	Array outMoves;

	int maxRows = board.GetRowsCount();
	int moveDir = m_PieceColor == PieceColor::Black ? moveDir = -1 : 1;

	// Forward Move
	{
		int oneStepForward = GetCellIndex(m_RowIndex, m_ColumnIndex + (1 * moveDir), maxRows);

		if (board.GetCellState(oneStepForward) == State::EmptyCell)
		{
			outMoves.Add(oneStepForward);

			// Tow-Step Forward Move
			if (m_FirstMove)
			{
				int towStepForward = GetCellIndex(m_RowIndex, m_ColumnIndex + (2 * moveDir), maxRows);
				if (board.GetCellState(towStepForward) == State::EmptyCell)
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
		if (topLeftPiece && topLeftPiece->GetPieceColor() != m_PieceColor)
			outMoves.Add(topLeft);

		if (topRightPiece && topRightPiece->GetPieceColor() != m_PieceColor)
			outMoves.Add(topRight);
	}


	return outMoves;
}