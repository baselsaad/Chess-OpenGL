#pragma once
#include <glm/vec2.hpp>
#include <unordered_map>

struct TransformComponent;
class Entity;

struct Cell
{
	Entity* ChessPiece = nullptr;

	Cell() = default;

	inline void ResetData() { ChessPiece = nullptr; }
	inline bool HasEntity() const { return ChessPiece != nullptr; }
};

// TODO: Simplify the logic after finish the whole project
class Grid
{
public:
	static constexpr int INVALID_ID = -1;

	Grid(const glm::vec2& viewportResolution = { 700.0f,700.0f }, int rowsCount = 8, int columnsCount = 8);
	~Grid();

public:
	void AddNewChessPiece(Entity* entity, int rowIndex, int colIndex);
	void MoveEntityToNewCell(Entity* entity,int oldID, const glm::vec2& newPosition);
	void GetEntity(double mouseX, double mouseY, int& outGridID, Entity** outEntity);

	inline void SetViewPort(const glm::vec2& viewport) { m_ViewportResolution = viewport; }

private:
	const glm::vec2& GetRowAndColumn(double mouseX, double mouseY);
	const glm::vec2 GetCellPosition(int row,int column);

	void ComputeCorrectCellPosition(const glm::vec2& screenSpacePosition, glm::vec2& outCellPosition, int& outNewIndex);
	int GetCellIndex(double mouseX, double mouseY);

private:
	int m_Rows;
	int m_Columns;
	glm::vec2 m_ViewportResolution;

	std::vector<Cell> m_Cells;
};