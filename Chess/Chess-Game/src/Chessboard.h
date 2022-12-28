#pragma once
class Entity;

struct Cell
{
	Entity* ChessPiece = nullptr;

	inline void ResetData() { ChessPiece = nullptr; }
	inline bool HasEntity() const { return ChessPiece != nullptr; }
};

class Chessboard
{
public:
	static constexpr int INVALID_ID = -1;

	Chessboard(const glm::vec2& viewportResolution = { 700.0f,700.0f }, int rowsCount = 8, int columnsCount = 8);
	~Chessboard();

public:
	// TODO: Just for now, will change later when we move every thing to opengl core
	void AddNewChessPiece(Texture& entity, int rowIndex, int colIndex);
	void MoveEntityToCell(int entityID, const glm::vec2& newPosition);
	int GetEntityID(double mouseX, double mouseY);
	bool HasEntity(double mouseX, double mouseY);

	void MoveEntityByOffset(const int& entityID, const float& xOffset, const float& yOffset);
	void MoveEntityToNewPosition(const int& entityID, const glm::vec3& positionOffset);

	inline void SetViewPort(const glm::vec2& viewport) { m_ViewportResolution = viewport; }
	inline const std::vector<Entity>& GetChessPieces() const { return m_EntityPool; }

	inline const glm::vec3& GetEntityLocation(int entityID) const { return m_Cells[entityID].ChessPiece->GetTranslation(); }

private:
	const glm::vec2& GetRowAndColumn(double mouseX, double mouseY);
	const glm::vec2 GetCellPosition(int row, int column);
	//Another way to computer
	void ComputeCorrectCellPosition(const glm::vec2& screenSpacePosition, glm::vec2& outCellPosition, int& outNewIndex);
	int GetCellIndex(double mouseX, double mouseY);

private:
	int m_Rows;
	int m_Columns;
	glm::vec2 m_ViewportResolution;

	std::vector<Cell> m_Cells;
	std::vector<Entity> m_EntityPool;
};