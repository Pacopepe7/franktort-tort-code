#include "chessgame.h"




bool ChessGame::isGoodCapture(ChessMove cm)		
	{
		if ( !isCapture(cm)) return false;

		if ( getPiece(getToSquare(cm)) == PAWN ) return true;

			//if (getPiece(getToSquare(cm)) < (getCapture(cm) + 180)) return true; 
		return false;
	};