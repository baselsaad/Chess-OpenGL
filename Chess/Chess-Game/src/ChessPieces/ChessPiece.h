#pragma once
#include "..\Entity.h"
#include "Utilities\Debug.h"

class ChessPiece : public Entity
{
public:
	ChessPiece(const glm::vec3& position = { 1.0f, 1.0f, 1.0f }, const glm::vec3& scale ={ 1.0f, 1.0f, 1.0f });
	virtual ~ChessPiece() = default;

public:
	virtual std::vector<int> GetPossibleMoves() { ASSERT(false, "Not Implmented!!"); return std::vector<int>(); }

	inline int GetCurrentCell() const { return m_CurrentCell; }
	inline void SetCurrentCell(int cell) { m_CurrentCell = cell; };

private:
	int m_CurrentCell = 0;
};
