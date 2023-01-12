#pragma once
#include "ChessPieces\ChessPiece.h"

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
	bool MoveToNewCell(int pieceID, const glm::vec2& newPosition);
	const Array GetPossibleMoves(int pieceID);

	ChessPiece* GetChessPiece(double mouseX, double mouseY, int& outpieceID);
	const ChessPiece* GetChessPiece(double mouseX, double mouseY) const;
	const ChessPiece* GetChessPiece(int cellIndex) const;
	const CellState GetCellState(int cellIndex) const;

	glm::vec2 CalcCellScreenPosition(int cellIndex) const;
	glm::vec2 CalcCellScreenPosition(int rowIndex, int columnIndex) const;

	inline int GetRowsCount() const { return m_Rows; }
	inline int GetColumnCount() const { return m_Columns; }

private:
	void MoveToNewCell(ChessPiece* piece, int targetCell, const glm::vec2& rowAndColumnIndex);
	glm::vec2 GetRowAndColumnIndex(double mouseX, double mouseY) const;

	void HandleCastling(const MovesFlag& flag, int kingTargetCell, ChessPiece* king);

private:
	int m_Rows;
	int m_Columns;

	std::vector<ChessPiece*> m_Cells; // contains only a pointer to an existing entity
};