#pragma once
#include "vec3.hpp"
#include "mat4x4.hpp"
#include "gtx\transform.hpp"

class Texutre;
namespace Colors { struct RGBA; };

struct TransformComponent
{
	glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(const glm::vec3& translation)
		: Translation(translation)
	{
	}

	glm::mat4 GetTransform() const
	{
		return glm::translate(glm::mat4(1.0f), Translation) //Location
			* glm::mat4(1.0f) //Rotation
			* glm::scale(glm::mat4(1.0f), Scale); //Scale
	}

};

struct Quad
{
	TransformComponent Transform;
	Texture* Sprite;
	Colors::RGBA Color;

	Quad(const TransformComponent& transform, Texture* texture = nullptr, Colors::RGBA color = Colors::White)
		: Transform(transform)
		, Sprite(texture)
		, Color(color)
	{
	}

	Quad(const TransformComponent& transform, Colors::RGBA color = Colors::White)
		: Transform(transform)
		, Sprite(nullptr)
		, Color(color)
	{
	}

	bool BindTexture();
	bool IsInQuad(int x, int y);
	
};
