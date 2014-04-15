/********************************************
*
*http://web.archive.org/web/20071214140839/http://www.seanet.com/~brucemo/topics/0x88.htm
*/

#include "ChessGame.h"


/*********************************************
* Did last move left me in check?
*/

bool ChessGame::isPositionValid(void)
{
	return !isAttacked(state[ply].king[opp], ctm);
}

/***********************************************************
* Does not check for interposing pieces
*/
Piece ChessGame::PiecesThatCanAttack(Square s1, Square s2)
{

	ASSERT ( isSquare(s1) && "PiecesThatCanAttack: s1 not a Square" );
	ASSERT ( isSquare(s2) && "PiecesThatCanAttack: s2 not a Square");
	int diff = s2 - s1;
	return Attacks0x88[diff + ATTACKTABLEINDEXOFFSET];
}
/***********************************************************
*
*/
bool ChessGame::isAttackedbyPiece ( Square from, Square to, Color side, Piece p )
{

	ASSERT( isSquare(from) && "isAttackedbyPiece: " );
	ASSERT( isSquare(to)  && "isAttackedbyPiece: ");
	ASSERT ( !isEmpty( from )  && "isAttackedbyPiece: ");
	ASSERT( p  && "isAttackedbyPiece: ");

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
bool ChessGame::isAttacked(Square target, Color co)
{
	//PrintBoard();
	Square sq;
	int c;
	//check for pawns, kings and knights
	//Pawns
	if ( co == WHITE )
	{
		if ( isSquare( target + SOUTHWEST) && getPiece( target + SOUTHWEST) == PAWN && isColor(target + SOUTHWEST, co))
			return true;
		if ( isSquare( target + SOUTHEAST) && getPiece( target + SOUTHEAST) == PAWN && isColor(target + SOUTHEAST, co))
			return true;
	}
	else
	{
		if ( isSquare( target + NORTHWEST) && getPiece( target + NORTHWEST) == PAWN && isColor(target + NORTHWEST, co))
			return true;
		if ( isSquare( target + NORTHEAST) && getPiece( target + NORTHEAST) == PAWN && isColor(target + NORTHEAST, co))
			return true;
	}
	//King
	for ( c = 0; c < 8; c++)
	{
		sq = target + kingvectors[c];
		if ( isSquare(sq) && getPiece(sq) == KING && isColor(sq, co))
			return true;
	}
	//Knight
	for ( c = 0; c < 8; c++)
	{
		sq = target + knightvectors[c];
		if ( isSquare(sq) && getPiece(sq) == KNIGHT && isColor(sq, co))
			return true;
	}
	// check for sliding pieces.
	for ( c = 0; c < 8; c++){

		for ( sq = target + queenvectors[c]; isSquare(sq) && isEmpty(sq) ; sq += queenvectors[c]);
		{
			if ( isSquare(sq) && isColor(sq, co) ) // we have a hit!
			{
				if ( getPiece(sq) == QUEEN)
					return true;
				if ( c % 2 == 0 && getPiece(sq) == ROOK)
					return  true;
				if ( c % 2 == 1 && getPiece(sq) == BISHOP)
					return true ;
			}
		}
	}
	return false;
}