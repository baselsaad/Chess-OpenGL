#include "pch.h"

bool SpriteSheetComponent::BindTexture() 
{
	if (Sprite == nullptr)
		return false;

	Sprite->Bind(0);
	return true;
}

bool SpriteSheetComponent::BindTexture() const
{
	if (Sprite == nullptr)
		return false;

	Sprite->Bind(0);
	return true;
}
