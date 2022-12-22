#pragma once

class Entity;
class PlayerInput;
class Event;
class Renderer;
class VertexBuffer;
class VertexArray;
class VertexBufferLayout;
class IndexBuffer;
class Shader;

class Game
{
public:
	Game();
	Game(int height, int width);
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

	void UpdateWindowResolution(int height, int width);

private:
	std::vector<Entity*> m_EntityPool;

	VertexArray m_VertexArray;
	VertexBuffer m_VertexBuffer;
	VertexBufferLayout m_Layout;
	IndexBuffer m_IndexBuffer;
	Shader m_Shader;

	int m_WindowHeight, m_WindowWidth;
};

