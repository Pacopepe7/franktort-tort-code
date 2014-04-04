
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

ASSERT ( isSquare(from));
ASSERT ( isSquare(to));
ASSERT ( ! isEmpty(from));

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
	//Castle
	if ( mt == MT_CASTLE )
	{
		if ( to == G1){
			Clear(H1);
			MovePiece(E1, G1);
			Set(ROOK, WHITE, F1);
			state.castling.whiteshort = false;
		}
		if ( to == C1){
			Clear(A1);
			MovePiece(E1, C1);
			Set(ROOK, WHITE, D1);
			state.castling.whitelong = false;
		}
		if ( to == G8){
			Clear(H8);
			MovePiece(E8, G8);
			Set(ROOK, BLACK, F8);
			state.castling.blackshort = false;
		}
		if ( to == C8){
			Clear(A8);
			MovePiece(E8, C8);
			Set(ROOK, BLACK, D8);
			state.castling.blacklong = false;
		}
	}
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
	state.m_LastMove = cm;
	SwitchSides();
	state.ply++;
	//PrintBoard();
	return true;
}