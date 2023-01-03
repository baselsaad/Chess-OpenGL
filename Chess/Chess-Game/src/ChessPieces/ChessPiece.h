#pragma once
#include "Entity.h"

class ChessPiece : public Entity
{
public:
	using FuncType = std::function<std::vector<int>()>;
	ChessPiece(const glm::vec3& position = { 1.0f, 1.0f, 1.0f }, const glm::vec3& scale = { 1.0f, 1.0f, 1.0f });
	virtual ~ChessPiece() = default;

public:
	inline int GetCurrentCell() const { return m_CurrentCell; }
	inline void SetCurrentCell(int cell) { m_CurrentCell = cell; };

	const std::vector<int> GetPossibleMoves() const;
	inline void SetMovementFunction(const FuncType& func) { m_GetPossibleMoves = func; };

private:
	int m_CurrentCell = 0;
	bool m_FirstMove = true;

	FuncType m_GetPossibleMoves;
};
