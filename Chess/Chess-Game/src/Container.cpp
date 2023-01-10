#include "pch.h"
#include "OpenGL-Core.h"
#include "Container.h"

#include "Entity.h"

EntityContainer::EntityContainer()
	: m_EntityCount(0)
{
	m_EntityPool.reserve(32);// to avoid resizing, we need max 32 ChessPieces 
}

EntityContainer::~EntityContainer()
{
	for (Entity* entity : m_EntityPool)
		delete entity;
}

void EntityContainer::OnRender()
{
	for (Entity* entity : m_EntityPool)
	{
		if (entity->IsActive())
			Renderer::Draw(entity->GetTransformationMatrix(), entity->GetTexture());
	}
}