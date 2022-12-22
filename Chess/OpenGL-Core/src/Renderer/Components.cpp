#include "pch.h"
#include "Defaults.h"


bool SpriteSheetComponent::BindTexture()
{
	if (Sprite == nullptr)
		return false;

	Sprite->Bind(0);
	Sprite->EnableBlending();
	return true;
}
