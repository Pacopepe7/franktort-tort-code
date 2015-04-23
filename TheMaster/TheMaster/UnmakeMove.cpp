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

	ASSERT ( isSquare(from) && "UnmakeMove");
	ASSERT ( isSquare(to) && "UnmakeMove");

	if ( mt == MT_NORMAL )
		MovePiece(to, from); // going backwards...

	if ( mt == MT_CAPTURE)
	{
		MovePiece(to, from);
		Set(data,ctm,to);
	}
	if ( mt == MT_PROMOTION)
	{
		Clear(to);
		Set(PAWN,opp,from);
	}
	if ( mt == (MT_CAPTURE | MT_PROMOTION))
	{	
		Clear(to);
		Set(getCapture(data), ctm, to);
		Set(PAWN,opp,from);
	}
	if( mt == MT_ENPASSANTPOSSIBLE )
		MovePiece(to, from);

	if( mt == MT_ENPASSANT )
	{
		Set(PAWN, ctm, to + pawndirection[ctm]);
		MovePiece(to, from);
	}
	if( mt == MT_CASTLE)
	{
		if ( to == G1){
			Clear(F1);
			MovePiece(G1, E1);
			Set(ROOK, WHITE, H1);
		}
		if ( to == C1){
			Clear(D1);
			MovePiece(C1, E1);
			Set(ROOK, WHITE, A1);
		}
		if ( to == G8){
			Clear(F8);
			MovePiece(G8, E8);
			Set(ROOK, BLACK, H8);
		}
		if ( to == C8){
			Clear(D8);
			MovePiece(C8, E8);
			Set(ROOK, BLACK, A8);
		}
	}
	/************************************************/
	//Update move info
	SwitchSides(BACK);
	/*************************************/
	return;
}