#include "pch.h"
#include "OpenGL-Core.h"
#include "MovesGen.h"

#include "Chessboard.h"

using CellState = Chessboard::CellState;

static int GetCellIndex(const int& targetRow, const int& targetColumn, const int& maxRows)
{
	//Edge Case
	if (targetRow < 0 || targetRow >= maxRows || targetColumn < 0 || targetColumn >= maxRows)
		return Chessboard::INVALID;

	return targetColumn * maxRows + targetRow;
}

static void TryToAddMoves(const ChessPiece* p, int row, int column, const Chessboard& board, MovesGen::Array& outMoves)
{
	int targetRow = p->GetRowIndex() + row;
	int targetCol = p->GetColumnIndex() + column;
	int targetCell = GetCellIndex(targetRow, targetCol, board.GetRowsCount());

	while (board.GetCellState(targetCell) != CellState::NotValidCell)
	{
		const ChessPiece* piece = board.GetChessPiece(targetCell);
		if (piece != nullptr)// => there is a piece and we can not move anymore
		{
			if (piece->GetTeamColor() != p->GetTeamColor())
				outMoves.Add(targetCell);

			break;
		}

		outMoves.Add(targetCell);

		targetRow += row;
		targetCol += column;
		targetCell = GetCellIndex(targetRow, targetCol, board.GetRowsCount());
	}
}

static void TryQueenSideCastle(const ChessPiece* king, const Chessboard& board, MovesGen::Array& outMoves)
{
	if (!king->IsFirstMove())
		return;

	int rowIndex = king->GetRowIndex();
	int colIndex = king->GetColumnIndex();

	// rook was killed or moved before
	const ChessPiece* rook = board.GetChessPiece(GetCellIndex(rowIndex - 4, colIndex, board.GetRowsCount()));
	if (rook == nullptr || !rook->IsActive() || !rook->IsFirstMove())
		return;

	for (int i = 1; i <= 3; i++)
	{
		int row = rowIndex - i;
		int cellIndex = GetCellIndex(row, colIndex, board.GetRowsCount());

		if (board.GetChessPiece(cellIndex) != nullptr)
			return;
	}

	MovesGen::Move move;
	move.TargetCell = GetCellIndex(rowIndex - 2, colIndex, board.GetRowsCount());
	move.Flag = MovesGen::MovesFlag::QueenSideCastling;
	outMoves.Add(move);
}

static void TryKingSideCastle(const ChessPiece* king, const Chessboard& board, MovesGen::Array& outMoves)
{
	if (!king->IsFirstMove())
		return;

	int rowIndex = king->GetRowIndex();
	int colIndex = king->GetColumnIndex();

	// rook was killed or moved before
	const ChessPiece* rook = board.GetChessPiece(GetCellIndex(rowIndex + 3, colIndex, board.GetRowsCount()));
	if (rook == nullptr || !rook->IsActive() || !rook->IsFirstMove())
		return;

	for (int i = 1; i <= 2; i++)
	{
		int row = rowIndex + i;
		int cellIndex = GetCellIndex(row, colIndex, board.GetRowsCount());

		if (board.GetChessPiece(cellIndex) != nullptr)
			return;
	}

	MovesGen::Move move;
	move.TargetCell = GetCellIndex(rowIndex + 2, colIndex, board.GetRowsCount());
	move.Flag = MovesGen::MovesFlag::KingSideCastling;
	outMoves.Add(move);
}

namespace MovesGen
{
	Array GetPossibleMoves(const ChessPiece* piece, Chessboard& board)
	{
		switch (piece->GetPieceType())
		{
			case PieceType::Pawn:       return GeneratePawnMoves(piece, board);
			case PieceType::Knight:     return GenerateKnightMoves(piece, board);
			case PieceType::Rook:       return GenerateRookMoves(piece, board);
			case PieceType::Bishop:     return GenerateBishopMoves(piece, board);
			case PieceType::Queen:      return GenerateQueenMoves(piece, board);
			case PieceType::King:       return GenerateKingMoves(piece, board);

			default:					ASSERT(false, "Unknown Type!!");	break;
		}
	}

	Array GeneratePawnMoves(const ChessPiece* pawn, Chessboard& board)
	{
		Array outMoves;

		const int moveDir = (int)pawn->GetTeamColor();
		const int maxRows = board.GetRowsCount();

		const int rowIndex = pawn->GetRowIndex();
		const int colIndex = pawn->GetColumnIndex();
		const int currentCell = GetCellIndex(rowIndex, colIndex, maxRows);

		// Forward Move
		int oneStepForward = GetCellIndex(rowIndex, colIndex + (1 * moveDir), maxRows);

		if (board.GetCellState(oneStepForward) == CellState::EmptyCell)
		{
			outMoves.Add(oneStepForward);

			// Tow-Step Forward Move
			if (pawn->IsFirstMove())
			{
				int towStepForward = GetCellIndex(rowIndex, colIndex + (2 * moveDir), maxRows);
				if (board.GetCellState(towStepForward) == CellState::EmptyCell)
					outMoves.Add(towStepForward);
			}
		}

		// Attack Moves
		int topLeft = GetCellIndex(rowIndex - 1, colIndex + (1 * moveDir), maxRows);
		int topRight = GetCellIndex(rowIndex + 1, colIndex + (1 * moveDir), maxRows);

		const ChessPiece* topLeftPiece = board.GetChessPiece(topLeft);
		const ChessPiece* topRightPiece = board.GetChessPiece(topRight);

		// if it has diffrent color then it is valid to attack 
		if (topLeftPiece && topLeftPiece->GetTeamColor() != pawn->GetTeamColor())
			outMoves.Add(topLeft);

		if (topRightPiece && topRightPiece->GetTeamColor() != pawn->GetTeamColor())
			outMoves.Add(topRight);


		return outMoves;
	}

	Array GenerateKnightMoves(const ChessPiece* kngiht, Chessboard& board)
	{
		Array outMoves;
		int moveDir = (int)kngiht->GetTeamColor();

		std::array<std::pair<int, int>, 4> possibleMoves =
		{
			std::pair(-2, (+1 * moveDir)),	// L-Up-Left
			std::pair(+2, (+1 * moveDir)),	// L-Up-Right

			std::pair(-2, (-1 * moveDir)),	// L-Down-Left
			std::pair(+2, (-1 * moveDir)),	// L-Down-Right
		};

		auto tryToAddMoves = [kngiht](int row, int column, const Chessboard& board, Array& outMoves) -> void
		{
			int targetCell = GetCellIndex(kngiht->GetRowIndex() + row, kngiht->GetColumnIndex() + column, board.GetRowsCount());
			bool notValidCell = board.GetCellState(targetCell) == CellState::NotValidCell;
			if (notValidCell)
				return;

			const ChessPiece* piece = board.GetChessPiece(targetCell);
			if (piece && piece->GetTeamColor() == kngiht->GetTeamColor())
				return;

			outMoves.Add(targetCell);
		};

		for (const auto& target : possibleMoves)
		{
			tryToAddMoves(target.first, target.second, board, outMoves);
		}

		for (const auto& target : possibleMoves)
		{
			tryToAddMoves(target.second, target.first, board, outMoves);
		}

		return outMoves;
	}

	Array GenerateRookMoves(const ChessPiece* rook, Chessboard& board)
	{
		Array outMoves;
		int moveDir = (int)rook->GetTeamColor();
		std::array<std::pair<int, int>, 4> possibleMoves =
		{
			std::pair(0, (+1 * moveDir)),	// Up
			std::pair(-1, 0),				// Left
			std::pair(+1, 0),				// Right
			std::pair(0, (-1 * moveDir)),	// Down
		};

		for (const auto& targetCell : possibleMoves)
		{
			TryToAddMoves(rook, targetCell.first, targetCell.second, board, outMoves);
		}

		return outMoves;
	}

	Array GenerateBishopMoves(const ChessPiece* bishop, Chessboard& board)
	{
		Array outMoves;
		int moveDir = (int)bishop->GetTeamColor();

		std::array<std::pair<int, int>, 4> possibleMoves =
		{
			std::pair(-1, (+1 * moveDir)),	// Diagonal-Up-Left
			std::pair(+1, (+1 * moveDir)),	// Diagonal-Up-Right

			std::pair(-1, (-1 * moveDir)),	// Diagonal-Down-Left
			std::pair(+1, (-1 * moveDir)),	// Diagonal-Down-Right
		};

		for (const auto& targetCell : possibleMoves)
		{
			TryToAddMoves(bishop, targetCell.first, targetCell.second, board, outMoves);
		}

		return outMoves;
	}

	Array GenerateQueenMoves(const ChessPiece* queen, Chessboard& board)
	{
		Array outMoves = GenerateRookMoves(queen, board);

		for (const auto& move : GenerateBishopMoves(queen, board))
			outMoves.Add(move);

		return outMoves;
	}

	Array GenerateKingMoves(const ChessPiece* king, Chessboard& board)
	{
		Array outMoves;

		const int moveDir = (int)king->GetTeamColor();
		const int maxRows = board.GetRowsCount();

		const int rowIndex = king->GetRowIndex();
		const int colIndex = king->GetColumnIndex();

		std::array<int, 8> possibleMoves =
		{
			GetCellIndex(rowIndex, colIndex + (1 * moveDir), maxRows),		// Up
			GetCellIndex(rowIndex - 1, colIndex, maxRows),					// Left
			GetCellIndex(rowIndex + 1, colIndex, maxRows),					// Right
			GetCellIndex(rowIndex, colIndex - (1 * moveDir), maxRows),		// Down

			GetCellIndex(rowIndex - 1, colIndex + (1 * moveDir), maxRows),	// Forward-Left
			GetCellIndex(rowIndex + 1, colIndex + (1 * moveDir), maxRows),	// Forward-Right

			GetCellIndex(rowIndex - 1, colIndex - (1 * moveDir), maxRows),	// Down-Left
			GetCellIndex(rowIndex + 1, colIndex - (1 * moveDir), maxRows),	// Down-Right
		};

		auto checkMove = [king](const Chessboard& board, int cellIndex) -> bool
		{
			if (board.GetCellState(cellIndex) != CellState::NotValidCell)
			{
				const ChessPiece* piece = board.GetChessPiece(cellIndex);
				// if there is no piece , or the piece is for the other team
				if (piece == nullptr || piece->GetTeamColor() != king->GetTeamColor())
					return true;
			}

			return false;
		};

		for (const int& targetCell : possibleMoves)
		{
			if (checkMove(board, targetCell))
			{
				outMoves.Add(targetCell);
			}
		}

		// Check for "is king in check before"
		{
			TryKingSideCastle(king, board, outMoves);
			TryQueenSideCastle(king, board, outMoves);
		}

		return outMoves;
	}

	bool IsKingInCheck(Chessboard& board, const ChessPiece* king)
	{
		const int maxRows = board.GetRowsCount();
		const int moveDir = (int)king->GetTeamColor();

		int xKing = king->GetRowIndex();
		int yKing = king->GetColumnIndex();

		// check horizontal and vertical spaces
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (i == 0 && j == 0)
					continue;

				int x = xKing + (i * moveDir);
				int y = yKing + (j * moveDir);
				int cell = GetCellIndex(x, y, maxRows);
				if (board.GetCellState(cell) != CellState::NotValidCell)
				{
					const ChessPiece* piece = board.GetChessPiece(cell);
					if (piece)
					{
						if (piece->GetTeamColor() == king->GetTeamColor())
							break;

						if (piece->GetPieceType() == PieceType::Queen || piece->GetPieceType() == PieceType::Rook)
							return true;
					}
				}
			}
		}

		// check diagonal spaces
		for (int i = -1; i <= 1; i += 2)
		{
			for (int j = -1; j <= 1; j += 2)
			{
				int x = xKing + (i * moveDir);
				int y = yKing + (j * moveDir);
				int cell = GetCellIndex(x, y, maxRows);
				while (board.GetCellState(cell) != CellState::NotValidCell)
				{
					const ChessPiece* piece = board.GetChessPiece(cell);
					if (piece)
					{
						if (piece->GetTeamColor() == king->GetTeamColor())
							break;

						if (piece->GetPieceType() == PieceType::Queen || piece->GetPieceType() == PieceType::Bishop)
							return true;
					}

					x += i;
					y += j;
					cell = GetCellIndex(x, y, maxRows);
				}
			}
		}

		// check knight moves
		for (int i = -2; i <= 2; i++)
		{
			for (int j = -2; j <= 2; j++)
			{

				if (glm::abs(i) == glm::abs(j) || i == 0 || j == 0)
					continue;

				int x = xKing + (i * moveDir);
				int y = yKing + (j * moveDir);
				int cell = GetCellIndex(x, y, maxRows);
				if (board.GetCellState(cell) != CellState::NotValidCell)
				{
					const ChessPiece* piece = board.GetChessPiece(cell);
					if (piece)
					{
						if (piece->GetTeamColor() == king->GetTeamColor())
							break;

						if (piece->GetPieceType() == PieceType::Knight)
							return true;
					}
				}
			}
		}
		return false;
	}
}