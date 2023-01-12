#pragma once
#include "ChessPiece.h"


class King : public ChessPiece
{
public:
	virtual const Array GetPossibleMoves(const Chessboard& board) const override;
	bool CheckMove(const Chessboard& board, int cellIndex) const;

	void TryQueenSideCastle(const Chessboard& board, Array& outMoves) const;
	void TryKingSideCastle(const Chessboard& board, Array& outMoves) const;

	virtual PieceType GetPieceType() const override { return PieceType::King; }
};

