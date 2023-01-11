#pragma once
#include "ChessPiece.h"


class King : public ChessPiece
{
public:
	virtual const Array GetPossibleMoves(const Chessboard& board) const override;
	bool CheckMove(const Chessboard& board, int cellIndex) const;

	virtual PieceType GetPieceType() const override { return PieceType::King; }
};

