#pragma once
#include "Chessboard.h"

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
class Chessboard;
class EntityContainer;

class Game
{
public:
	Game(int height = 700, int width = 700);
	~Game() = default;

public:
	void OnStart(EntityContainer& container);
	void OnUpdate(const DeltaTime& deltaTime);
	void SetupPlayerInput(PlayerInput* input);
	void OnDestroy();

	void OnMousePressed(MouseButtonPressedEvent& event);
	void OnMouseReleased(MouseButtonReleasedEvent& event);
	void OnMouseMove(MouseMoveEvent& event);

	void OnUpdateViewport(int width, int height);
	void AdjustBackgroundImage();

	void Game::DrawBackgroundManually();
private:
	glm::vec2 m_Viewport;

	// Test
	Texture m_TextureTest;
	Texture m_BackgroundTexture;

	Entity* m_BackgroundImage;
	Chessboard m_Chessboard;
};

