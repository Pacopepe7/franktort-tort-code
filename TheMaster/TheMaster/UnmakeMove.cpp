/*******************************************************************
* MakeIntMove (unsigned int)
* Makes the selected move on the board, returns true if this move can actually be made
* false otherwise.
* 
*/
#include "ChessGame.h"


void ChessGame::UnmakeMove( ChessMove cm)
{
	Square from = getFromSquare(cm);
	Square to = getToSquare(cm);
	Square epsq =  getEPSquare(cm);
	MoveType mt = getMoveType(cm);

	if ( mt == MT_NORMAL)
	{
		MovePiece(to, from); // going backwards...
		
	}
	
	/************************************************/
	//Update move info
	state.m_bWhitetomove = state.m_bWhitetomove? false: true;

	//if ( mt != MT_CAPTURE )
	//			state.fiftymoverule ++;
	
	state.ply--;
}