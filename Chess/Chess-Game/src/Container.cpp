#include "pch.h"
#include "OpenGL-Core.h"
#include "Container.h"

#include "ChessPieces\ChessPiece.h"

EntityContainer::EntityContainer()
	: m_EntityCount(0)
{
	m_EntityPool.reserve(32);// to avoid resizing, we need max 32 ChessPieces 
}

EntityContainer::~EntityContainer()
{

}

void EntityContainer::OnRender()
{
	for (auto& entity : m_EntityPool)
	{
		Renderer::DrawQuad(entity.GetTransformationMatrix(), entity.GetTexture());
	}
}