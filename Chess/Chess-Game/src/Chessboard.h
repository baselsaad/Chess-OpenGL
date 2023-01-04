#pragma once
class ChessPiece;

class Chessboard
{
public:
	static constexpr int INVALID = -1;

	Chessboard(int rowsCount = 8, int columnsCount = 8);
	~Chessboard();

public:
	void AddNewChessPiece(ChessPiece* entity, int rowIndex, int colIndex);
	void MoveToNewCell(int entityID, const glm::vec2& newPosition, const glm::vec3& orginalPosition);
	std::vector<int> GetPossibleMoves(int entityID);

	void OnUpdateViewPort();

	void GetChessPiece(double mouseX, double mouseY, int& outEntityID, ChessPiece** outEntity);
	bool DoesCellHaveEntity(double mouseX, double mouseY);
	const glm::vec2 GetCellScreenPosition(int cellIndex);

	inline int GetRowsCount() const { return m_Rows; }
	inline int GetColumnCount() const { return m_Columns; }

private:
	//Another way to compute
	void ComputeCorrectCellPosition(const glm::vec2& targetPosInScreenSpcae, glm::vec2& outCellPosition, glm::vec2& outRowColumn, int& outNewIndex);
	const glm::vec2 GetRowAndColumnIndex(double mouseX, double mouseY);
	const glm::vec2 GetCellScreenPosition(int rowIndex, int columnIndex);

private:
	int m_Rows;
	int m_Columns;

	std::vector<ChessPiece*> m_Cells; // contains only a pointer to an existing entity
};