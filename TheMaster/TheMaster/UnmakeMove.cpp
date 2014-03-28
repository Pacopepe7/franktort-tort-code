/*******************************************************************
* MakeIntMove (unsigned int)
* Makes the selected move on the board, returns true if this move can actually be made
* false otherwise.
* 
*/
#include "ChessGame.h"
#include <iostream>
using namespace std;

void ChessGame::UnmakeMove( ChessMove cm)
{
	Square from = getFromSquare(cm);
	Square to = getToSquare(cm);
	Square data =  getDataSquare(cm);
	MoveType mt = getMoveType(cm);

	if ( mt == MT_NORMAL)
	{
		MovePiece(to, from); // going backwards...
		
	}
	if ( mt == MT_CAPTURE)
	{
		MovePiece(to, from);
		Set(data, ColorOnMove(),to);

	}
	/************************************************/
	//Update move info
	SwitchSides();
	state.ply--;
	return;
}