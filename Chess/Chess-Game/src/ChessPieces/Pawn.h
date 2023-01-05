#pragma once
#include "ChessPiece.h"


class Pawn : public ChessPiece
{

public:
	virtual const std::vector<int> GetPossibleMoves(const int& maxRows) const override;
};
