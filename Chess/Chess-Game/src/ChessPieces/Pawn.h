#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece
{

public:
	virtual const Array GetPossibleMoves(const Chessboard& board) const override;
	virtual PieceType GetPieceType() const override { return PieceType::Pawn; }
};
