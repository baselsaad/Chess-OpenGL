#pragma once
#include "Entity.h"
class Chessboard;

// Costum stack Array to avoid Heap-Allocations every frame using std::vector
struct Array
{
	// maximum number of squares that a piece can potentially move to
	static constexpr int MAX_CELLS = 30;

	std::array<int8_t, MAX_CELLS> MovesArray;
	int Count = 0;

	using Iterator = std::array<int8_t, MAX_CELLS>::iterator;
	using ConstIterator = std::array<int8_t, MAX_CELLS>::const_iterator;

	Array()
		: MovesArray(std::array<int8_t, MAX_CELLS>())
	{
	}

	Array(const Array& other)
	{
		// no need to Copy the whole array, only the valid
		std::copy(other.begin(), other.end(), MovesArray.begin());
		Count = other.Count;
	}

	void Add(const int8_t& element)
	{
		MovesArray[Count++] = element;
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



enum class PieceColor
{
	White, Black
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
	virtual const Array GetPossibleMoves(const Chessboard& board) const
	{
		ASSERT(false, "There is no Implementation for the Possible Moves!!");
		return {};
	}

	void OnMoveToNewPosition(const glm::vec2& newPosition); // used for valid movement
	void OnDragToNewPosition(const glm::vec2& newPosition); // used for DragAndDrop

	inline void SetRowIndex(int rowIndex) { m_RowIndex = rowIndex; }
	inline int GetRowIndex() { return m_RowIndex; }

	inline void SetColumnIndex(int colIndex) { m_ColumnIndex = colIndex; }
	inline int GetColumnIndex() { return m_ColumnIndex; }

	inline void SetPieceColor(PieceColor color) { m_PieceColor = color; }
	inline PieceColor GetPieceColor() const { return m_PieceColor; }

protected:
	static int GetCellIndex(const int& targetRow, const int& targetColumn, const int& maxRows);

	int m_RowIndex;
	int m_ColumnIndex;
	bool m_FirstMove;
	PieceColor m_PieceColor;


};
