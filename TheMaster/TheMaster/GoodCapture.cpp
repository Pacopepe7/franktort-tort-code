#include "chessgame.h"




bool ChessGame::isGoodCapture(ChessMove cm)		
	{
		if ( !isCapture(cm)) return false;

		if ( getPiece(getToSquare(cm)) == PAWN ) return true;

		if (getPiece(getToSquare(cm)) <= (getCapture(cm) )) return true; 
		
		return false;
	};

ChessMove ChessGame::RetrieveOrderedMove(void)
{
	return mstack[ply].pop();
}