#pragma once

struct TransformComponent;
struct SpriteSheetComponent;


class Entity
{
public:
	Entity() = default;
	Entity(const TransformComponent& transform, const SpriteSheetComponent& sprite);

public:
	bool IsInBox(int x, int y);

	inline TransformComponent& GetTransformComponent() { return m_Transform; }
	inline SpriteSheetComponent& GetSpriteSheetComponent() { return m_Sprite; }

	inline glm::vec3& GetTranslation() { return m_Transform.Translation; }
	inline glm::vec3& GetScale() { return m_Transform.Scale; }

private:
	TransformComponent m_Transform;
	SpriteSheetComponent m_Sprite;
};