#pragma once
#include "ChessPiece.h"
class King : public ChessPiece
{
public:
	virtual const Array GetPossibleMoves(const Chessboard& board) const override;

	bool TryToAddMove(const Chessboard& board,int cellIndex) const;
};

