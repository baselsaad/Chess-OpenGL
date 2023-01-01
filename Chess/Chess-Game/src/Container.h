#pragma once
class ChessPiece;

class EntityContainer
{
public:
	EntityContainer();
	~EntityContainer();

public:
	void OnRender();

	template<class T, typename ...Args>
	ChessPiece* CreateNewEntity(Args... args) const
	{
		m_EntityCount++;
		return (T*)&m_EntityPool.emplace_back(std::forward<Args>(args)...);
	}

private:
	mutable std::vector<ChessPiece> m_EntityPool;
	mutable int m_EntityCount;
};