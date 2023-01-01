#pragma once
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

#include "Defaults.h"
#include "Utilities\Colors.h"

class Texutre;

struct TransformComponent
{
	glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

	TransformComponent(const TransformComponent&) = default;

	TransformComponent(const glm::vec3& translation = glm::vec3(1.0f), const glm::vec3& scale = glm::vec3(1.0f))
		: Translation(translation), Scale(scale)
	{
	}

	glm::mat4 GetTransformationMatrix() const
	{
		return glm::translate(glm::mat4(1.0f), Translation) //Location
			* glm::mat4(1.0f) //Rotation
			* glm::scale(glm::mat4(1.0f), Scale); //Scale
	}

	glm::vec2 GetCenterPositionInScreenSpace() const
	{
		return glm::vec2
		(
			Translation.x + ((Defaults::MAX_POSITION_OFFSET * Scale.x) / 2.0f),
			Translation.y + ((Defaults::MAX_POSITION_OFFSET * Scale.y) / 2.0f)
		);
	}

};

struct SpriteSheetComponent
{
	Texture* SpriteTexture = nullptr;
	Colors::RGBA Color;

	SpriteSheetComponent(Texture* texture = nullptr, Colors::RGBA color = Colors::White)
		: SpriteTexture(texture)
		, Color(color)
	{
	}

	SpriteSheetComponent(const SpriteSheetComponent&) = default;

	bool BindTexture();
	bool BindTexture() const;
};
