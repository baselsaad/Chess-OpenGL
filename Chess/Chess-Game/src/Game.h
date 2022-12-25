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
class DeltaTime;
class OpenGLWindow;
class MouseButtonPressedEvent;
class MouseButtonReleasedEvent;
class MouseMoveEvent;

class Game
{
public:
	Game();
	Game(int height, int width);
	~Game() = default;

public:
	void OnStart();
	void OnRender();
	void OnUpdate(const DeltaTime& deltaTime);
	void SetupPlayerInput(PlayerInput* input);
	void OnDestroy();

	void OnMousePressed(MouseButtonPressedEvent& event);
	void OnMouseReleased(MouseButtonReleasedEvent& event);
	void OnMouseMove(MouseMoveEvent& event);

	void UpdateWindowSize(int height, int width);

	void DrawBackground();
	void AdjustBackgroundImage();

	void DrawEntites();

	void CalculateProjectionViewMatrix(); 

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

	// Test
	Texture m_TextureTest;
	Texture m_BackgroundTexture;

	Entity m_BackgroundImage;
};

