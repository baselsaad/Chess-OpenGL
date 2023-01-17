#pragma once
#include "ChessPiece.h"

namespace MovesGen
{

	enum class MovesFlag
	{
		KingSideCastling,
		QueenSideCastling,
		EnPassantCapture,
		PromoteToQueen,
		PromoteToKnight,
		PromoteToRook,
		PromoteToBishop,
		PawnTwoForward,
		None
	};

	struct Move
	{
		int16_t TargetCell = -1;
		MovesFlag Flag = MovesFlag::None;
	};

	// Costum stack Array to avoid Heap-Allocations every frame using std::vector
	struct Array
	{
		// maximum number of squares that a piece can potentially move to in single move
		static constexpr int MAX_CELLS = 30;

		std::array<Move, MAX_CELLS> MovesArray;
		int Count = 0;

		using Iterator = std::array<Move, MAX_CELLS>::iterator;
		using ConstIterator = std::array<Move, MAX_CELLS>::const_iterator;

		Array()
			: MovesArray(std::array<Move, MAX_CELLS>())
		{
		}

		Array(const Array& other)
		{
			ASSERT(Count < MAX_CELLS, "");

			// no need to Copy the whole array, only the valid
			std::copy(other.begin(), other.end(), MovesArray.begin());
			Count = other.Count;
		}

		void Add(const Move& element)
		{
			MovesArray[Count++] = element;
		}

		void Add(const int16_t& element)
		{
			Move move;
			move.TargetCell = element;
			MovesArray[Count++] = move;
		}

		void Clear()
		{
			Count = 0;
		}

		Iterator begin()
		{
			return MovesArray.begin();
		}

		ConstIterator begin() const
		{
			return MovesArray.begin();
		}

		Iterator end()
		{
			return MovesArray.begin() + Count;
		}

		ConstIterator end() const
		{
			return MovesArray.begin() + Count;
		}

	};

	Array GetPossibleMoves(const ChessPiece* piece, Chessboard& board);

	Array GeneratePawnMoves(const ChessPiece* piece, Chessboard& board);
	Array GenerateKnightMoves(const ChessPiece* piece, Chessboard& board);
	Array GenerateRookMoves(const ChessPiece* piece, Chessboard& board);
	Array GenerateQueenMoves(const ChessPiece* piece, Chessboard& board);
	Array GenerateKingMoves(const ChessPiece* piece, Chessboard& board);
	Array GenerateBishopMoves(const ChessPiece* piece, Chessboard& board);

	bool IsKingInCheck(Chessboard& board, const ChessPiece* king);
}
