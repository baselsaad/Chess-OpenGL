#pragma once
#include "ChessPieces/ChessPiece.h"

class EntityContainer
{
public:
	EntityContainer();
	~EntityContainer();

public:
	void OnRender();

	//template<class T, typename ...Args>
	//T* CreateNewEntity(Args... args) const
	//{
	//	static_assert(std::is_base_of<Entity, T>::value, "T must be drived from Entity!!");

	//	m_EntityCount++;
	//	Entity* entity = m_EntityPool.emplace_back(new T(std::forward<Args>(args)...));
	//	return static_cast<T*>(entity);
	//}

	template<typename ...Args>
	ChessPiece* CreateNewEntity(Args... args) const
	{
		m_EntityCount++;
		return &m_EntityPool.emplace_back(std::forward<Args>(args)...);
	}

private:
	mutable std::vector<ChessPiece> m_EntityPool;
	mutable int m_EntityCount;
};