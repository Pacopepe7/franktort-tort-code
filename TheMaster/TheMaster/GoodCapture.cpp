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
	int score = -INFINITY;;
	ChessMove cm;
	int c;
	int bestsofar;
	for (c = 0; c < mstack[ply].size(); c++)
	{
		if (mstack[ply].inspect(c).score > score)
		{
			bestsofar = c;
		}
	}
	return mstack[ply].Remove(bestsofar).cm;
}