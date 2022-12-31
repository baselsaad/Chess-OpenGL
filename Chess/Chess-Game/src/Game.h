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

// Assets
struct ChessTextures
{
	std::string SelectedColor;
	Texture Pawn;
	Texture Bishop;
	Texture Knight;
	Texture Rock;
	Texture Queen;
	Texture King;

	enum class Color
	{
		White, Black
	};

	ChessTextures(const Color& color)
		: SelectedColor(color == Color::Black ? "Black" : "White")
		, Pawn("res/textures/" + SelectedColor + "Pawn.png")
		, Bishop("res/textures/" + SelectedColor + "Bishop.png")
		, Knight("res/textures/" + SelectedColor + "Knight.png")
		, Rock("res/textures/" + SelectedColor + "Rook.png")
		, Queen("res/textures/" + SelectedColor + "Queen.png")
		, King("res/textures/" + SelectedColor + "King.png")
	{
	}

};

class Game
{
public:
	Game(int height = 700, int width = 700);
	~Game() = default;

public:
	void OnStart(EntityContainer& container);
	void CreateChessPieces(EntityContainer& container, ChessTextures& textures, int pawns, int rest);
	void OnUpdate(const DeltaTime& deltaTime);
	void SetupPlayerInput(PlayerInput* input);
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

	Entity* m_BackgroundImage;
	Chessboard m_Chessboard;
};

