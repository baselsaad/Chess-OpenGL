#pragma once
struct TransformComponent;
struct SpriteSheetComponent;


class Entity
{
public:
	Entity() = default;
	Entity(const TransformComponent& transform, const SpriteSheetComponent& sprite);

public:
	bool IsInBound(int x, int y);

	inline TransformComponent& GetTransformComponent() { return m_Transform; }
	inline const TransformComponent& GetTransformComponent() const { return m_Transform; }

	inline SpriteSheetComponent& GetSpriteSheetComponent() { return m_Sprite; }
	inline const SpriteSheetComponent& GetSpriteSheetComponent() const { return m_Sprite; }

	inline glm::vec3& GetTranslation() { return m_Transform.Translation; }
	inline glm::vec3& GetScale() { return m_Transform.Scale; }

	inline void SetTranslation(const glm::vec3& translation) { m_Transform.Translation = translation; }
private:
	TransformComponent m_Transform;
	SpriteSheetComponent m_Sprite;
};