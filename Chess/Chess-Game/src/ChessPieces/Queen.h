#pragma once
#include "ChessPiece.h"

class Queen : public ChessPiece
{


public:
	virtual const Array GetPossibleMoves(const Chessboard& board) const override;
	virtual PieceType GetPieceType() const override { return PieceType::Queen; }


private:
	void TryToAddMoves(int row, int column, const Chessboard& board, Array& outMoves) const;
};