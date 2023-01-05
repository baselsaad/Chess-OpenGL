#pragma once
#include "Entity.h"

class ChessPiece : public Entity
{
public:
	ChessPiece(const glm::vec3& position = { 1.0f, 1.0f, 1.0f }, const glm::vec3& scale = { 1.0f, 1.0f, 1.0f });

public:

	/*
	* returns Array of Possible Cells that can move to
	*/
	virtual const std::vector<int> GetPossibleMoves(const int& maxRows) const;

	inline void SetRowIndex(int rowIndex) { m_RowIndex = rowIndex; }
	inline void SetColumnIndex(int colIndex) { m_ColumnIndex = colIndex; }
	inline int GetRowIndex() { return m_RowIndex; }
	inline int GetColumnIndex() { return m_ColumnIndex; }

protected:
	int m_RowIndex;
	int m_ColumnIndex;
	bool m_FirstMove;
};
