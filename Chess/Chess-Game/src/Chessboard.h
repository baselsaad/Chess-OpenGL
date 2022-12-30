#pragma once
class Entity;

struct Cell
{
	Entity* ChessPiece = nullptr;
	int RowIndex = -1;
	int ColIndex = -1;

	inline void ResetData() 
	{
		ChessPiece = nullptr;
		RowIndex = -1;
		ColIndex = -1;
	}

	inline bool HasEntity() const { return ChessPiece != nullptr; }

};

class Chessboard
{
public:
	static constexpr int INVALID = -1;

	Chessboard(const glm::vec2& viewportResolution = { 700.0f,700.0f }, int rowsCount = 8, int columnsCount = 8);
	~Chessboard();

public:
	// TODO: Texture ref just for now, will change later when we move every thing to opengl core
	void AddNewChessPiece(Entity* entity, int rowIndex, int colIndex);
	bool HasEntity(double mouseX, double mouseY);
	int GetEntityID(double mouseX, double mouseY);

	void MoveEntityToCell(int entityID, const glm::vec2& newPosition);
	void MoveEntityByOffset(const int& entityID, const float& xOffset, const float& yOffset);
	void MoveEntityToNewPosition(const int entityID, const glm::vec3& positionOffset);

	void UpdateViewPort(const glm::vec2& viewport);

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
	glm::vec2 m_ViewportResolution;

	std::vector<Cell> m_Cells; // contains only a pointer to an existing entity
};