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
	enum class Color
	{
		White, Black
	};

	Color SelectedColor;

	Texture Pawn;
	Texture Bishop;
	Texture Knight;
	Texture Rook;
	Texture Queen;
	Texture King;

	ChessTextures(const Color& color);

	inline static std::string ToString(Color color)
	{
		switch (color)
		{
			case Color::Black: return "Black";
			case Color::White: return "White";
		}
	}
};

class Game
{
public:
	Game();
	~Game() = default;

public:
	void OnStart();
	void CreateChessPieces(const EntityContainer& container, ChessTextures& textures, int pawns, int rest);
	void OnUpdate(const DeltaTime& deltaTime);
	void SetupPlayerInput(PlayerInput& input);
	void OnDestroy();

	void OnMousePressed(const MouseButtonPressedEvent& event);
	void OnMouseReleased(const MouseButtonReleasedEvent& event);
	void OnMouseMove(const MouseMoveEvent& event);

	void OnUpdateViewport();

	void AdjustBackgroundImage();
	void DrawBackgroundManually();


private:
	ChessTextures m_WhitePiecesTex;
	ChessTextures m_BlackPiecesTex;
	Texture m_BackgroundTexture;
	Texture m_PossibleMovesTexture;

	Entity m_BackgroundEntity;
	Chessboard m_Chessboard;
	EntityContainer m_EntityContainer;
};

