#include "pch.h"
#include "OpenGL-Core.h"
#include "Container.h"

#include "Entity.h"

EntityContainer::EntityContainer()
	: m_EntityCount(0)
{
	m_EntityPool.reserve(96);// to avoid resizing, we need max 96 
}

EntityContainer::~EntityContainer()
{
	for (auto* entity : m_EntityPool)
		delete entity;
}

void EntityContainer::OnRender()
{
	for (int i = 0; i < m_EntityCount; i++)
	{
		const TransformComponent& transform = m_EntityPool[i]->GetTransformComponent();
		const SpriteSheetComponent& sprite = m_EntityPool[i]->GetSpriteSheetComponent();

		if (sprite.SpriteTexture)
			Renderer::DrawQuad(transform.GetTransformationMatrix(), sprite.SpriteTexture);
		else
			Renderer::DrawQuad(transform.GetTransformationMatrix(), sprite.Color);
	}
}
