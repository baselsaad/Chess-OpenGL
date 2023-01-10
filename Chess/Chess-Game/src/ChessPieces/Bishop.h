#pragma once
#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
	virtual const Array GetPossibleMoves(const Chessboard& board) const override;

	virtual PieceType GetPieceType() const override { return PieceType::Bishop; }

private:
	void TryToAddMoves(int row, int column, const Chessboard& board, Array& outMoves) const;
};