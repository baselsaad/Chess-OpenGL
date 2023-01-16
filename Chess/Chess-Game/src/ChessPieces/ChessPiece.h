#pragma once
#include "Entity.h"
#include "Renderer/Defaults.h"
class Chessboard;

enum class TeamColor
{
	// (-1 moveDir = Bottom, 1 moveDir = Up)
	Black = -1,
	None = 0,
	White = 1
};

enum class PieceType
{
	Pawn = 0, Knight, Rook, Bishop, Queen, King
};

class ChessPiece : public Entity
{
public:
	ChessPiece(TeamColor teamColor, PieceType pieceType, const glm::vec3& position = Defaults::DefaultPosition, const glm::vec3& scale = Defaults::DefaultScale);
	~ChessPiece() = default;
public:
	void OnMoveToNewPosition(const glm::vec2& newPosition); // used for valid movement
	void OnDragToNewPosition(const glm::vec2& newPosition); // used for DragAndDrop

	inline void SetRowIndex(int rowIndex) { m_RowIndex = rowIndex; }
	inline int GetRowIndex() const { return m_RowIndex; }

	inline void SetColumnIndex(int colIndex) { m_ColumnIndex = colIndex; }
	inline int GetColumnIndex() const { return m_ColumnIndex; }

	inline void SetTeamColor(TeamColor color) { m_PieceColor = color; }
	inline TeamColor GetTeamColor() const { return m_PieceColor; }

	inline bool IsFirstMove() const { return m_FirstMove; }

	inline PieceType GetPieceType() const { return m_PieceType; }
	inline void SetPieceType(PieceType pieceType) { m_PieceType = pieceType; }

protected:
	int m_RowIndex;
	int m_ColumnIndex;
	bool m_FirstMove;
	TeamColor m_PieceColor;
	PieceType m_PieceType;
};
