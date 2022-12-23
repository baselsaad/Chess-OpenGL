#pragma once
#include "Entity.h"


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
	void DrawBackground();
	void AdjustBackgroundImage();

private:
	int m_WindowHeight, m_WindowWidth;
	glm::mat4 m_ProjectionView;

	std::vector<Entity> m_EntityPool;

	// Move to entity rendering container
	VertexArray m_VertexArray;
	VertexBuffer m_EntityVB;
	VertexBufferLayout m_EntityLayout;
	IndexBuffer m_EntityIB;
	Shader m_EntityShader;
	Texture m_TextureTest;

	Texture m_BackgroundTexture;
	Entity m_BackgroundImage;
};

