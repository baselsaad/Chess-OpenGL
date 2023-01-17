#pragma once
#include "ChessPieces/ChessPiece.h"
#include "ChessPieces/MovesGen.h"

class Chessboard
{
public:
	static constexpr int INVALID = -1;

	Chessboard(int rowsCount = 8, int columnsCount = 8);
	~Chessboard();

	enum class CellState
	{
		EmptyCell, OccupiedCell, NotValidCell
	};

public:
	void OnUpdateViewPort();

	void AddNewChessPiece(ChessPiece* piece, int rowIndex, int colIndex);
	bool MoveToNewCell(int pieceID, const glm::vec2& newPosition, const MovesGen::Array& possibleMoves);

	ChessPiece* GetChessPiece(double mouseX, double mouseY, int& outpieceID);
	const ChessPiece* GetChessPiece(double mouseX, double mouseY) const;
	const ChessPiece* GetChessPiece(int cellIndex) const;
	const CellState GetCellState(int cellIndex) const;

	glm::vec2 CalcCellScreenPosition(int cellIndex) const;
	glm::vec2 CalcCellScreenPosition(int rowIndex, int columnIndex) const;
	glm::vec2 CalcCellCenterPosition(float xPos, float yPos);

	inline int GetRowsCount() const { return m_Rows; }
	inline int GetColumnCount() const { return m_Columns; }

	inline const ChessPiece* GetKing(TeamColor color)
	{
		switch (color)
		{
			case TeamColor::White: return m_WhiteKing;
			case TeamColor::Black: return m_BlackKing;
		}
	}

	inline void SetKing(TeamColor color, ChessPiece* piece)
	{
		switch (color)
		{
			case TeamColor::White: m_WhiteKing = piece; return;
			case TeamColor::Black: m_BlackKing = piece; return;
		}
	}

private:
	void MoveToNewCell(ChessPiece* piece, int targetCell, const glm::vec2& rowAndColumnIndex);
	glm::vec2 GetRowAndColumnIndex(double mouseX, double mouseY) const;

	void HandleCastling(const MovesGen::MovesFlag& flag, int kingTargetCell, ChessPiece* king);
	bool IsCheckAfterMoving(int startCell, int targetCell);

private:
	int m_Rows;
	int m_Columns;

	float m_RowWidth , m_ColHeight;

	std::vector<ChessPiece*> m_Cells; // contains only a pointer to an existing entity

	ChessPiece* m_WhiteKing;
	ChessPiece* m_BlackKing;
};