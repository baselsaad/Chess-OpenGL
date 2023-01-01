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
		const Texture* texture = m_EntityPool[i]->GetTexture();

		if (texture)
			Renderer::DrawQuad(m_EntityPool[i]->GetTransformationMatrix(), texture);
		else
			Renderer::DrawQuad(m_EntityPool[i]->GetTransformationMatrix(), m_EntityPool[i]->GetColor());
	}
}
