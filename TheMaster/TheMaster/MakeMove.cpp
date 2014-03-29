
/*******************************************************************
* MakeIntMove (unsigned int)
* Makes the selected move on the board, returns true if this move can actually be made
* false otherwise.
* 
*/
#include "ChessGame.h"
#include <iostream>
using namespace std;

/**************************************************
* if return is false, no need to UnmakeMove
*
*/
bool ChessGame::MakeMove(ChessMove cm)
{
	//Does NOT assume the move has been validated! (to do...)
	Square from = getFromSquare(cm);
	Square to = getToSquare(cm);
	Square data =  getDataSquare(cm);
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
	//Ep possible
	if ( mt == MT_ENPASSANTPOSSIBLE ) 
	{
		state.epsquare[state.ply] = data;
		MovePiece(from, to);
	}
	else
		state.epsquare[state.ply] = 0;
	// EP
	if ( mt == MT_ENPASSANT )
	{
		//PrintBoard();
		Clear(state.epsquare[state.ply - 1] - pawndirection[state.ctm] );
		MovePiece(from, to);
		//PrintBoard();
	}
	// no capture
	if ( mt == MT_NORMAL) 
		MovePiece(from, to);

	//Capture
	if (mt == MT_CAPTURE )
		CapturePiece(from, to);

	/************************************************/
	//Update move info

	SwitchSides();
	state.ply++;
	return true;
}