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
	void OnStart();
	void OnRender();
	void OnUpdate(float deltaTime);
	void SetupPlayerInput(PlayerInput* input);
	void OnDestroy();

	void OnMousePressed(Event& event);
	void OnMouseReleased(Event& event);
	void OnMouseMove(Event& event);

private:
	std::vector<Entity*> m_EntityPool;
};

