#pragma once
#include "Renderer\Entity.h"

class ChessPiece : public Entity
{
public:
	ChessPiece(const TransformComponent& transform, const SpriteSheetComponent& sprite, int cell = 0);
	virtual ~ChessPiece() = default;

public:
	virtual std::vector<int> GetPossibleMoves() { ASSERT(false, "Not Implmented!!"); return std::vector<int>(); }

	inline int GetCurrentCell() const { return m_CurrentCell; }
	inline void SetCurrentCell(int cell) { m_CurrentCell = cell; };

private:
	int m_CurrentCell;
};

