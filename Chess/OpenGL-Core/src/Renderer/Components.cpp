#include "pch.h"
#include "Defaults.h"


bool Quad::IsInQuad(int x, int y)
{
	// Calculate PixelData (World Positions of Vertics)
	float minX = Transform.Translation.x + (Defaults::MIN_POSITION_OFFSET * Transform.Scale.x);
	float maxX = Transform.Translation.x + (Defaults::MAX_POSITION_OFFSET * Transform.Scale.x);

	float minY = Transform.Translation.y + (Defaults::MIN_POSITION_OFFSET * Transform.Scale.y);
	float maxY = Transform.Translation.y + (Defaults::MAX_POSITION_OFFSET * Transform.Scale.y);

	return (x > minX && x < maxX) && (y > minY && y < maxY);
}

bool Quad::BindTexture()
{
	if (Sprite == nullptr)
		return false;

	Sprite->Bind(0);
	Sprite->EnableBlending();
	return true;
}
