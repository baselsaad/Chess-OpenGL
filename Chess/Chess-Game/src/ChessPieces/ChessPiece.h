#pragma once
#include "Entity.h"
class Chessboard;

namespace ChessPieceUtil
{
	struct ArrayListConstIterator : public std::iterator<std::input_iterator_tag, int8_t>
	{
		using ValueType = int8_t;
		using PointerType = const ValueType*;
		using RefrenceType = const ValueType&;
		PointerType m_Ptr;

		ArrayListConstIterator(PointerType ptr)
			: m_Ptr(ptr)
		{
		}

		ArrayListConstIterator& operator++ ()
		{
			m_Ptr++;
			return *this;
		}

		ArrayListConstIterator operator++ (int)
		{
			ArrayListConstIterator it = *this;
			++(*this);
			return it;
		}

		ArrayListConstIterator& operator-- ()
		{
			m_Ptr--;
			return *this;
		}

		ArrayListConstIterator operator-- (int)
		{
			ArrayListConstIterator it = *this;
			--(*this);
			return it;
		}

		RefrenceType operator[] (int index)
		{
			return *(m_Ptr + index);
		}

		PointerType operator->()
		{
			return m_Ptr;
		}

		RefrenceType operator* ()
		{
			return *m_Ptr;
		}

		bool operator== (const ArrayListConstIterator& other) const
		{
			return m_Ptr == other.m_Ptr;
		}

		bool operator!= (const ArrayListConstIterator& other) const
		{
			return !(*this == other);
		}
	};

	// Costum stack Array to avoid Heap-Allocations every frame using std::vector
	struct Array
	{
		// maximum number of squares that a piece can potentially move to
		static constexpr int MAX_POSSIBLE_CELLS_TO_MOVE = 30;

		std::array<int8_t, MAX_POSSIBLE_CELLS_TO_MOVE> MovesArray;
		int Count = 0;

		Array()
			: MovesArray(std::array<int8_t, MAX_POSSIBLE_CELLS_TO_MOVE>())
		{
		}

		Array(const Array& other)
		{
			// no need to Copy the whole array, only the valid
			std::copy(other.begin(), other.end(), &MovesArray[0]);
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

		ArrayListConstIterator begin() const
		{
			return ArrayListConstIterator(&MovesArray[0]);
		}

		ArrayListConstIterator end() const
		{
			return ArrayListConstIterator(&MovesArray[0] + Count);
		}

	};

}

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
	virtual const ChessPieceUtil::Array GetPossibleMoves(const Chessboard& board) const
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
	static int GetValidCell(const int& targetRow, const int& targetColumn, const int& maxRows);

	int m_RowIndex;
	int m_ColumnIndex;
	bool m_FirstMove;
	PieceColor m_PieceColor;


};
