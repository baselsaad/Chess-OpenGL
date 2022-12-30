#include "pch.h"
#include "OpenGL-Core.h"

bool SpriteSheetComponent::BindTexture() 
{
	if (SpriteTexture == nullptr)
		return false;

	SpriteTexture->Bind(0);
	return true;
}

bool SpriteSheetComponent::BindTexture() const
{
	if (SpriteTexture == nullptr)
		return false;

	SpriteTexture->Bind(0);
	return true;
}
