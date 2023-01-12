#pragma once
#include "Entity.h"
class Chessboard;

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

enum class TeamColor
{
	// (-1 moveDir = Bottom, 1 moveDir = Up)
	Black = -1,
	None = 0,
	White = 1
};

enum class PieceType
{
	Pawn = 0, Knight, Rook, Bishop, Queen, King
};


class ChessPiece : public Entity
{
public:
	ChessPiece(const glm::vec3& position = { 1.0f, 1.0f, 1.0f }, const glm::vec3& scale = { 1.0f, 1.0f, 1.0f });
	~ChessPiece() = default;
public:
	/*
	* returns Array of Possible Cells that can move to
	*/
	virtual const Array GetPossibleMoves(const Chessboard& board) const { ASSERT(false, "No Impl!!"); return {}; }
	virtual PieceType GetPieceType() const { ASSERT(false, "No Impl!!"); return {}; };

	void OnMoveToNewPosition(const glm::vec2& newPosition); // used for valid movement
	void OnDragToNewPosition(const glm::vec2& newPosition); // used for DragAndDrop

	inline void SetRowIndex(int rowIndex) { m_RowIndex = rowIndex; }
	inline int GetRowIndex() const { return m_RowIndex; }

	inline void SetColumnIndex(int colIndex) { m_ColumnIndex = colIndex; }
	inline int GetColumnIndex() const { return m_ColumnIndex; }

	inline void SetTeamColor(TeamColor color) { m_PieceColor = color; }
	inline TeamColor GetTeamColor() const { return m_PieceColor; }

	inline bool IsFirstMove() const { return m_FirstMove; }

protected:
	static int GetCellIndex(const int& targetRow, const int& targetColumn, const int& maxRows);

	int m_RowIndex;
	int m_ColumnIndex;
	bool m_FirstMove;
	TeamColor m_PieceColor;


};
