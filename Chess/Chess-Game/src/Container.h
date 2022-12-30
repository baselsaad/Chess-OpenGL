#pragma once

class Entity;
class TransformComponent;
class SpriteSheetComponent;

class EntityContainer
{
public:
	EntityContainer();

public:
	Entity* CreateNewEntity(const TransformComponent& transform, const SpriteSheetComponent& sprite);
	void OnRender();

private:
	std::vector<Entity> m_EntityPool;
	int m_EntityCount;
};
