#pragma once
#include "ChessPiece.h"

namespace MovesGen
{
	Array GetPossibleMoves(const ChessPiece* piece, Chessboard& board);
	
	Array GeneratePawnMoves(const ChessPiece* piece, Chessboard& board);
	Array GenerateKnightMoves(const ChessPiece* piece, Chessboard& board);
	Array GenerateRookMoves(const ChessPiece* piece, Chessboard& board);
	Array GenerateQueenMoves(const ChessPiece* piece, Chessboard& board);
	
}
