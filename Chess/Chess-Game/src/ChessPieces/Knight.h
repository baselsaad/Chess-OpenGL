#pragma once
#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
	virtual const Array GetPossibleMoves(const Chessboard& board) const override;
	virtual PieceType GetPieceType() const override { return PieceType::Knight; }

private:
	void TryToAddMoves(int row, int column, const Chessboard& board, Array& outMoves) const;
};