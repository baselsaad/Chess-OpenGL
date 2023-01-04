#pragma once
class ChessPiece;

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
	void AddNewChessPiece(ChessPiece* entity, int rowIndex, int colIndex);
	bool CellHasEntity(double mouseX, double mouseY);
	int GetEntityID(double mouseX, double mouseY);
	std::vector<int> GetEntityPossibleMoves(int entityID);

	//Movement
	void MoveEntityToCell(int entityID, const glm::vec2& newPosition);
	void MoveEntityToNewCell(int entityID, const glm::vec2& newPosition, const glm::vec3& orginalPosition);
	void MoveEntityByOffset(const int& entityID, const float& xOffset, const float& yOffset);

	void OnUpdateViewPort();

	const glm::vec3 GetEntityLocation(int entityID) const;

	const glm::vec2 GetRowAndColumn(double mouseX, double mouseY);
	const glm::vec2 GetCellPosition(int row, int column);
	const glm::vec2 GetCellPosition(int cellIndex);

	inline int GetRowsCount() const { return m_Rows; }
	inline int GetColumnCount() const { return m_Columns; }

private:
	//Another way to compute
	void ComputeCorrectCellPosition(const glm::vec2& screenSpacePosition, glm::vec2& outCellPosition, glm::vec2& outRowColumn, int& outNewIndex);
	int GetCellIndex(double mouseX, double mouseY);

private:
	int m_Rows;
	int m_Columns;

	std::vector<Cell> m_Cells; // contains only a pointer to an existing entity
};