#include "pch.h"
#include "OpenGL-Core.h"
#include "Entity.h"

#include "Renderer\Defaults.h"


Entity::Entity(const TransformComponent& transform, const SpriteSheetComponent& sprite)
	: m_Transform(transform)
	, m_Sprite(sprite)
{
}

bool Entity::IsInBound(int x, int y)
{
    // Calculate PixelData (Pixel Positions of Vertics)
	float minX = m_Transform.Translation.x + (Defaults::MIN_POSITION_OFFSET * m_Transform.Scale.x);
	float maxX = m_Transform.Translation.x + (Defaults::MAX_POSITION_OFFSET * m_Transform.Scale.x);

	float minY = m_Transform.Translation.y + (Defaults::MIN_POSITION_OFFSET * m_Transform.Scale.y);
	float maxY = m_Transform.Translation.y + (Defaults::MAX_POSITION_OFFSET * m_Transform.Scale.y);

	return (x > minX && x < maxX) && (y > minY && y < maxY);
}
