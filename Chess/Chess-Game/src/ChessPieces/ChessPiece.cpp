#include "pch.h"
#include "OpenGL-Core.h"
#include "ChessPiece.h"

ChessPiece::ChessPiece(const glm::vec3& position, const glm::vec3& scale)
	: Entity(position, scale)
{
}
