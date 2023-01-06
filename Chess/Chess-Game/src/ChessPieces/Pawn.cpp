#include "pch.h"
#include "OpenGL-Core.h"
#include "Pawn.h"

#include "Chessboard.h"

const std::vector<int> Pawn::GetPossibleMoves(const Chessboard& board) const
{
	int maxRows = board.GetRowsCount();
	std::vector<int> outMoves;
	outMoves.reserve(4);

	int moveDir = m_PieceColor == PieceColor::Black ? moveDir = -1 : +1;

	// Forward Move
	{
		int oneStepForward = GetValidCell(m_RowIndex, m_ColumnIndex + (1 * moveDir), maxRows);

		if (!board.DoesCellHavePiece(oneStepForward))
		{
			outMoves.emplace_back(oneStepForward);

			// Tow-Step Forward Move
			if (m_FirstMove)
			{
				int towStepForward = GetValidCell(m_RowIndex, m_ColumnIndex + (2 * moveDir), maxRows);
				if (!board.DoesCellHavePiece(towStepForward))
					outMoves.emplace_back(towStepForward);
			}
		}
	}

	// Attack Moves
	{
		int topLeft = GetValidCell(m_RowIndex - 1, m_ColumnIndex + (1 * moveDir), maxRows);
		int topRight = GetValidCell(m_RowIndex + 1, m_ColumnIndex + (1 * moveDir), maxRows);

		const ChessPiece* topLeftPiece = board.GetChessPiece(topLeft);
		const ChessPiece* topRightPiece = board.GetChessPiece(topRight);

		// if it has diffrent color then it is valid to attack 
		if (topLeftPiece && topLeftPiece->GetPieceColor() != m_PieceColor)
			outMoves.emplace_back(topLeft);

		if (topRightPiece && topRightPiece->GetPieceColor() != m_PieceColor)
			outMoves.emplace_back(topRight);
	}


	return outMoves;
}