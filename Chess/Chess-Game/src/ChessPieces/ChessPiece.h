#pragma once
#include "Entity.h"
#include "Chessboard.h"
class Chessboard;

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
	virtual const std::vector<int> GetPossibleMoves(const Chessboard& board) const
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
