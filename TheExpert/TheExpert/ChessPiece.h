#pragma once

#include "chess.h"
#include "Color.h"
#include "Pieces.h"
#include "ChessMove.h"

struct ChessPiece
{
	Color cColor;
	Piece pPiece;
	Location lLocation; // 0x88
	int index; //this is the index the piece is on the array
	Location nextPiece;
	Location PreviousPiece;
};

bool IsChessPieceOK(ChessPiece * piece);