
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
	//PrintMove(cm);

	ASSERT ( isSquare(from) && "MakeMove");
	ASSERT ( isSquare(to) && "MakeMove");
	ASSERT ( ! isEmpty(from ) && "MakeMove");

	//Cannot capture the king
	if ( getPiece(to) & KING)
		return false;


	//set state corresponding to next ply
	memcpy(&state[ply + 1], &state[ply], sizeof(boardstate_t));
	state[ply + 1].m_LastMove = cm;

	//Ep possible
	if ( mt & MT_ENPASSANTPOSSIBLE ) 
	{
		state[ply + 1].epsquare = data;
		MovePiece(from, to);
	}
	else
		state[ply + 1].epsquare = INVALID;
	if ( from == A1 || to == A1)
		state[ply + 1].castling[WHITE] = state[ply + 1].castling[WHITE] & SHORT;
	if ( from == H1 || to == H1)
		state[ply + 1].castling[WHITE] = state[ply + 1].castling[WHITE] & LONG;
	if ( from == A8 || to == A8)
		state[ply + 1].castling[BLACK] = state[ply + 1].castling[BLACK] &  SHORT;
	if ( from == H8 || to == H8)
		state[ply + 1].castling[BLACK] = state[ply + 1].castling[BLACK] &  LONG;
	//Castle
	if ( mt & MT_CASTLE )
	{
		if ( to == G1){
			Clear(H1);
			MovePiece(E1, G1);
			Set(ROOK, WHITE, F1);
			state[ply + 1].castling[WHITE] = NONE;
		}
		if ( to == C1){
			Clear(A1);
			MovePiece(E1, C1);
			Set(ROOK, WHITE, D1);
			state[ply + 1].castling[WHITE] = NONE;
		}
		if ( to == G8){
			Clear(H8);
			MovePiece(E8, G8);
			Set(ROOK, BLACK, F8);
			state[ply + 1].castling[BLACK] = NONE;
		}
		if ( to == C8){
			Clear(A8);
			MovePiece(E8, C8);
			Set(ROOK, BLACK, D8);
			state[ply + 1].castling[BLACK] = NONE;
		}
	}
	// EP
	if ( mt & MT_ENPASSANT )
	{
		Clear(state[ply].epsquare - pawndirection[ctm] );
		MovePiece(from, to);
	}
	// no capture
	if ( mt == MT_NORMAL) 
		MovePiece(from, to);

	//Capture
	if (mt == MT_CAPTURE )
		CapturePiece(from, to );
	//Protion
	if (mt == MT_PROMOTION )
	{
		Clear(from);
		Set(data, ctm, to);
	}
	if (mt == (MT_PROMOTION | MT_CAPTURE) )
	{
		Clear(to);
		Clear(from);
		Set(getPromotion(data), ctm, to);
		
	}

	/*************************************/
	//update king position
	if ( getPiece(to) & KING){
		state[ply + 1].king[ctm] = to;
		state[ply + 1].castling[ctm] = NONE;}
	/************************************************/
	//Update move info
	SwitchSides(FORWARD);	
	//PrintBoard();
	//PrintMove(cm);
	return true;
}