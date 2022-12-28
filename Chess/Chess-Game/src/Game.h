#pragma once
#include "Entity.h"
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

	void UpdateViewport(int width, int height);
	void CalculateProjectionViewMatrix(); 

	void DrawBackground();
	void AdjustBackgroundImage();

	//+64 DrawCalls
	void DrawBackgroundManually();

	void DrawEntites();

private:
	glm::vec2 m_Viewport;
	glm::mat4 m_ProjectionView;

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
	Chessboard m_Chessboard;
};

