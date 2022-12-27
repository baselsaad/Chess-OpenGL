#pragma once

struct TransformComponent;
class Entity;

struct CellData
{
	Entity* ChessPiece = nullptr;

	CellData() = default;
	inline Entity* GetOwnedEntity() const { return ChessPiece; }
};

class Grid
{

public:
	Grid(int rowsCount = 8, int columnsCount = 8);
	~Grid();

public:
	void UpdateChessPiecePosition(Entity* piece, const glm::vec2& newPosition);

	Entity* HasChessPiece(int index);

	int GetChessPieceIndex(double mouseX, double mouseY, const glm::vec2& viewport);
	void AddNewChessPiece(Entity* piece, int index);

private:
	int m_Rows;
	int m_Columns;

	std::vector<CellData> m_GridSystem;
};