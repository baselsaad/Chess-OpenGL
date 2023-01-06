#pragma once
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Texture;
namespace Colors { struct RGBA; }

class Entity
{

public:
	Entity(const glm::vec3& position = { 1.0f, 1.0f, 1.0f }, const glm::vec3& scale = { 1.0f, 1.0f, 1.0f });
	virtual ~Entity() = default;

public:
	bool IsInBound(int x, int y);

	const glm::mat4 GetTransformationMatrix() const;
	const glm::vec3 GetPositionCenteredInScreenSpace() const;

	inline void SetPosition(const glm::vec3& position) { m_Position = position; }
	inline glm::vec3& GetPosition() { return m_Position; }

	inline void SetScale(const glm::vec3& scale) { m_Scale = scale; }
	inline glm::vec3& GetScale() { return m_Scale; }

	inline void SetTexture(Texture* texture) { m_Texture = texture; }
	inline Texture* GetTexture() { return m_Texture; }

	inline void SetColor(const Colors::RGBA& color) { m_Color = color; }
	inline const Colors::RGBA& GetColor() { return m_Color; }

	inline void SetTransform(const glm::vec3& position, const glm::vec3& scale) { m_Position = position; m_Scale = scale; }

protected:
	// Transform
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	// Sprite
	Texture* m_Texture;
	Colors::RGBA m_Color;
};