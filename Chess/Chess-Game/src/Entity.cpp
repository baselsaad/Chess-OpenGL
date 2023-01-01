#include "pch.h"
#include "OpenGL-Core.h"
#include "Entity.h"

#include "Renderer\Defaults.h"

Entity::Entity(const glm::vec3& position, const glm::vec3& scale)
	: m_Position(position)
	, m_Scale(scale)
	, m_Texture(nullptr)
	, m_Color()
{
}

bool Entity::IsInBound(int x, int y)
{
	// Calculate PixelData (Pixel Positions of Vertics)
	float minX = m_Position.x + (Defaults::MIN_POSITION_OFFSET * m_Scale.x);
	float maxX = m_Position.x + (Defaults::MAX_POSITION_OFFSET * m_Scale.x);

	float minY = m_Position.y + (Defaults::MIN_POSITION_OFFSET * m_Scale.y);
	float maxY = m_Position.y + (Defaults::MAX_POSITION_OFFSET * m_Scale.y);

	return (x > minX && x < maxX) && (y > minY && y < maxY);
}

const glm::mat4 Entity::GetTransformationMatrix() const
{
	return glm::translate(glm::mat4(1.0f), m_Position) //Location
		* glm::mat4(1.0f) //Rotation
		* glm::scale(glm::mat4(1.0f), m_Scale); //Scale
}

const glm::vec2 Entity::GetCenterPositionInScreenSpace() const
{
	return glm::vec2
	(
		m_Position.x + ((Defaults::MAX_POSITION_OFFSET * m_Scale.x) / 2.0f),
		m_Position.y + ((Defaults::MAX_POSITION_OFFSET * m_Scale.y) / 2.0f)
	);
}
