#pragma once
#include "Renderer/Components.h"


class Entity
{

public:
	Entity() = default;
	Entity(const TransformComponent& transform, const SpriteSheetComponent& sprite);
	virtual ~Entity() = default;

public:
	bool IsInBound(int x, int y);

	inline void SetTransformComponent(TransformComponent& transform) { m_Transform = transform; }
	inline TransformComponent& GetTransformComponent() { return m_Transform; }
	inline const TransformComponent& GetTransformComponent() const { return m_Transform; }

	inline void SetSpriteSheetComponent(SpriteSheetComponent& sprite) { m_Sprite = sprite; }
	inline SpriteSheetComponent& GetSpriteSheetComponent() { return m_Sprite; }
	inline const SpriteSheetComponent& GetSpriteSheetComponent() const { return m_Sprite; }

	inline glm::vec3& GetTranslation() { return m_Transform.Translation; }
	inline glm::vec3& GetScale() { return m_Transform.Scale; }

	inline void SetTranslation(const glm::vec3& translation) { m_Transform.Translation = translation; }

private:
	TransformComponent m_Transform;
	SpriteSheetComponent m_Sprite;
};