
/*******************************************************************
* MakeIntMove (unsigned int)
* Makes the selected move on the board, returns true if this move can actually be made
* false otherwise.
* 
*/
#include "ChessGame.h"
#include <iostream>
using namespace std;

bool ChessGame::MakeMove(ChessMove cm)
{
	//assumes the move has been validated! (to do...)
	Square from = getFromSquare(cm);
	Square to = getToSquare(cm);
	Square epsq =  getDataSquare(cm);
	MoveType mt = getMoveType(cm);
	//cout << "From: " << (int)from << ", To: " << (int)to << endl;
	//Piece q = getPromotingPiece(cm);
#ifdef _DEBUG
	if ( ! isSquare(from)) 
		return false;
	if ( ! isSquare(to))
		return false;
#endif
	//Cannot capture the king
	if ( getPiece(to) & KING)
		return false;
	//Ep moves
	if ( epsq == to)
	{


		;
	}
	// no capture
	if ( mt == MT_NORMAL) 
	{
		MovePiece(from, to);
		
	}
	//Capture
	if (mt == MT_CAPTURE )
	{
		CapturePiece(from, to);
	}


	/************************************************/
	//Update move info

	SwitchSides();
	state.ply++;
	return true;
}