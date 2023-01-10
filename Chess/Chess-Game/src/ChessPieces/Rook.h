#pragma once
#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
	virtual const Array GetPossibleMoves(const Chessboard& board) const override;
	virtual PieceType GetPieceType() const override { return PieceType::Rook; }

private:
	void TryToAddMoves(int row, int column, const Chessboard& board, Array& outMoves) const;
};