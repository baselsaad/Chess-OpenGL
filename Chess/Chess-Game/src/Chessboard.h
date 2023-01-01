#pragma once
#include "ChessPieces\ChessPiece.h"

struct Cell
{
	ChessPiece* ChessPiece = nullptr;
	int RowIndex = -1;
	int ColIndex = -1;

	inline void ResetData() 
	{
		ChessPiece = nullptr;
		RowIndex = -1;
		ColIndex = -1;
	}

	inline bool CellHasEntity() const { return ChessPiece != nullptr; }

};

class Chessboard
{
public:
	static constexpr int INVALID = -1;

	Chessboard(int rowsCount = 8, int columnsCount = 8);
	~Chessboard();

public:
	// TODO: Texture ref just for now, will change later when we move every thing to opengl core
	void AddNewChessPiece(ChessPiece* entity, int rowIndex, int colIndex);
	bool CellHasEntity(double mouseX, double mouseY);
	int GetEntityID(double mouseX, double mouseY);

	void MoveEntityToCell(int entityID, const glm::vec2& newPosition);
	void MoveEntityToCell(int entityID, int cellNum);
	void MoveEntityByOffset(const int& entityID, const float& xOffset, const float& yOffset);
	void MoveEntityToNewPosition(const int entityID, const glm::vec3& positionOffset);

	void OnUpdateViewPort();

	inline const glm::vec2 GetEntityLocation(int entityID) const { return m_Cells[entityID].ChessPiece->GetTransformComponent().GetCenterPositionInScreenSpace(); }

private:
	const glm::vec2 GetRowAndColumn(double mouseX, double mouseY);
	const glm::vec2 GetCellPosition(int row, int column);
	//Another way to computer
	void ComputeCorrectCellPosition(const glm::vec2& screenSpacePosition, glm::vec2& outCellPosition, glm::vec2& outRowColumn,int& outNewIndex);
	int GetCellIndex(double mouseX, double mouseY);

private:
	int m_Rows;
	int m_Columns;

	std::vector<Cell> m_Cells; // contains only a pointer to an existing entity
};