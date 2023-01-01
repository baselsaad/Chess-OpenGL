#pragma once
class Entity;

class EntityContainer
{
public:
	EntityContainer();
	~EntityContainer();

public:
	void OnRender();

	template<class T, typename ...Args>
	T* CreateNewEntity(Args&&... args) const
	{
		static_assert(std::is_base_of<Entity, T>::value, "T must be a subclass of Entity");

		m_EntityCount++;
		Entity* e = m_EntityPool.emplace_back(new T(std::forward<Args>(args)...));
		return static_cast<T*>(e);
	}

private:
	mutable std::vector<Entity*> m_EntityPool;
	mutable int m_EntityCount;
};