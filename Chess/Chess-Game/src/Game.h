#pragma once

#include "Event.h"
#include "PlayerInput.h"


class Entity;

class Game
{
public:
	Game();
	~Game() = default;

public:
	void SetupPlayerInput(PlayerInput* input);
	void OnUpdate(float deltaTime);

	void OnMousePressed(Event& event);
	void OnMouseReleased(Event& event);
	void OnMouseMove(Event& event);

private:
	std::vector<Entity*> m_EntityPool;
};

