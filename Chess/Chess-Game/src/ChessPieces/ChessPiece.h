#pragma once
#include "Entity.h"

class ChessPiece : public Entity
{
public:
	using FuncType = std::function<std::vector<int>(const int& currentRowIndex, const int& currentColumnIndex, const int& maxRows)>;
	ChessPiece(const glm::vec3& position = { 1.0f, 1.0f, 1.0f }, const glm::vec3& scale = { 1.0f, 1.0f, 1.0f });
	ChessPiece(const FuncType& func, const glm::vec3& position = { 1.0f, 1.0f, 1.0f }, const glm::vec3& scale = { 1.0f, 1.0f, 1.0f });
	virtual ~ChessPiece() = default;

public:
	const std::vector<int> GetPossibleMoves(const int& maxRows) const;
	inline void SetMovementFunction(const FuncType& func) { m_GetPossibleMoves = func; };

	inline void SetRowIndex(int rowIndex) { m_RowIndex = rowIndex; }
	inline void SetColumnIndex(int colIndex) { m_ColumnIndex = colIndex; }
	inline int GetRowIndex() { return m_RowIndex; }
	inline int GetColumnIndex() { return m_ColumnIndex; }


private:
	int m_RowIndex;
	int m_ColumnIndex;
	bool m_FirstMove = true;

	FuncType m_GetPossibleMoves;
};
