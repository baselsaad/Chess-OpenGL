#pragma once
#include "Chessboard.h"
#include "Container.h"
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
class MouseButtonPressedEvent;
class MouseButtonReleasedEvent;
class MouseMoveEvent;

// Assets
struct ChessTextures
{
	std::string SelectedColor;
	Texture Pawn;
	Texture Bishop;
	Texture Knight;
	Texture Rook;
	Texture Queen;
	Texture King;

	enum class Color
	{
		White, Black
	};

	ChessTextures(const Color& color);
};

class Game
{
public:
	Game(int height = 700, int width = 700);
	~Game() = default;

public:
	void OnStart();
	void CreateChessPieces(const EntityContainer& container, ChessTextures& textures, int pawns, int rest);
	void OnUpdate(const DeltaTime& deltaTime);
	void SetupPlayerInput(PlayerInput& input);
	void OnDestroy();

	void OnMousePressed(MouseButtonPressedEvent& event);
	void OnMouseReleased(MouseButtonReleasedEvent& event);
	void OnMouseMove(MouseMoveEvent& event);

	void OnUpdateViewport();

	void AdjustBackgroundImage();
	void DrawBackgroundManually();


private:
	// Test
	ChessTextures m_WhitePieces;
	ChessTextures m_BlackPieces;
	Texture m_BackgroundTexture;

	Entity m_BackgroundEntity;
	Chessboard m_Chessboard;
	EntityContainer m_EntityContainer;
};

