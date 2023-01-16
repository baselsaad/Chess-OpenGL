#include "pch.h"
#include "OpenGL-Core.h"
#include "ChessPiece.h"

#include "Chessboard.h"

ChessPiece::ChessPiece(TeamColor teamColor, PieceType pieceType, const glm::vec3& position, const glm::vec3& scale)
	: Entity(position, scale)
	, m_RowIndex(0), m_ColumnIndex(0)
	, m_FirstMove(true)
	, m_PieceColor(teamColor)
	, m_PieceType(pieceType)
{
}

void ChessPiece::OnMoveToNewPosition(const glm::vec2& newPosition)
{
	m_FirstMove = false;

	auto entityOrgin = GetPositionCenteredInScreenSpace();
	m_Position.x += newPosition.x - entityOrgin.x;
	m_Position.y += newPosition.y - entityOrgin.y;
}

void ChessPiece::OnDragToNewPosition(const glm::vec2& newPosition)
{
	auto entityOrgin = GetPositionCenteredInScreenSpace();
	m_Position.x += newPosition.x - entityOrgin.x;
	m_Position.y += newPosition.y - entityOrgin.y;
}