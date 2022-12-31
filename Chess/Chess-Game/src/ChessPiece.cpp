#include "pch.h"
#include "OpenGL-Core.h"

#include "ChessPiece.h"

ChessPiece::ChessPiece(const TransformComponent& transform, const SpriteSheetComponent& sprite, int cell)
	: Entity(transform, sprite)
	, m_CurrentCell(cell)
{
}