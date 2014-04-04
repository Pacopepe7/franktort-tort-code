/********************************************
*
*http://web.archive.org/web/20071214140839/http://www.seanet.com/~brucemo/topics/0x88.htm
*/

#include "ChessGame.h"


/*********************************************
* Did last move left opponent on check?
*/

bool ChessGame::isPositionValid(void)
{
	state.ctm;
	Square kingsq = state.king[state.opp];

	/**********************************************
	* Did the opponent just left his king in check?
	*/
	for ( int i = 0; i < maxpieces[state.ctm]; i++)
	{
		if ( pieces[i][state.ctm].piece)
			if ( isAttackedbyPiece(pieces[i][state.ctm].square, kingsq, state.ctm, pieces[i][state.ctm].piece ))
				return false;
	}

	return true;

}

/***********************************************************
* Does not check for interposing pieces
*/
Piece ChessGame::PiecesThatCanAttack(Square s1, Square s2)
{

	ASSERT ( isSquare(s1) );
	ASSERT ( isSquare(s2));
	int diff = s2 - s1;
	return Attacks0x88[diff + ATTACKTABLEINDEXOFFSET];
}
/***********************************************************
*
*/
bool ChessGame::isAttackedbyPiece ( Square from, Square to, Color side, Piece p )
{

	ASSERT( isSquare(from) );
	ASSERT( isSquare(to) );
	ASSERT ( !isEmpty( from ) );
	ASSERT( p );

	//if ( from == G5 && to == F7)
	//	PrintBoard();
	Piece PiecesAbleToAttack = PiecesThatCanAttack(from, to);
	if ( ! PiecesAbleToAttack )
		return false;
	int c;
	Square sq;

	if ( !(p & PiecesAbleToAttack))
		return false;

	if ( p & ( KING | KNIGHT ))
		return true;
	if ( p & PAWN)
	{
		if ( side == WHITE )
		{
			if ((to - from == NORTHWEST) | (to - from == NORTHEAST))
				return true;
		}
		else
		{
			if ((to - from == SOUTHWEST) | (to - from == SOUTHEAST))
				return true;
		}
	}

	//if there is an interposing piece (of any color), then return false
	for ( c = 0; c < 8; c++){
		//PrintBoard();
		for ( sq = from + queenvectors[c]; isSquare(sq) && isEmpty(sq) && !(sq == to) ; sq += queenvectors[c]);
		{
			if ( sq == to) // we have a hit!
			{
				if ( p == QUEEN)
					return true;
				if ( c % 2 == 0)
					return p == ROOK;
				return p == BISHOP;
			}
		}
	}
	return false;
} 
/**************************************************************
*
*/
bool ChessGame::isAttacked(Square sq, Color c)
{
	ASSERT (isSquare(sq));
	for ( int i = 0; i < maxpieces[c]; i++)
	{
		if ( pieces[i][c].piece)
			if ( isAttackedbyPiece(pieces[i][c].square, sq, c, pieces[i][c].piece ))
				return true;
	}


	return false;
}