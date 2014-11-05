/********************************************
*
*http://web.archive.org/web/20071214140839/http://www.seanet.com/~brucemo/topics/0x88.htm
*/

#include "ChessGame.h"


/*********************************************
* Did last move left me in check?
*/

bool ChessGame::isPositionValid(ChessMove cm)
{
	//{ return isAttacked(state[ply].king[ctm], opp);};
	return !isAttacked(KingPos(opp), ctm);
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
	static Square sq;
	static int c;
	//check for pawns, kings and knights
	//Pawns
	if ( co == WHITE )
	{
		if ( isPieceColor( target + SOUTHWEST, PAWN, co))
			return true;
		if ( isPieceColor( target + SOUTHEAST, PAWN, co))
			return true;
	}
	else
	{
		if ( isPieceColor( target + NORTHWEST, PAWN, co))
			return true;
		if ( isPieceColor( target + NORTHEAST, PAWN, co))
			return true;
	}
	//King
	for ( c = 0; c < 8; c++)
	{
		if (isPieceColor( target + kingvectors[c], KING, co))
			return true;
	}
	//Knight
	for ( c = 0; c < 8; c++)
	{
		if ( isPieceColor( target + knightvectors[c], KNIGHT , co))
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

bool ChessGame::PawnsAttackingLargePieces(ChessMove cm)
{
	Square pawnsq = getToSquare(cm);
	Square sq;
	Piece p = getPiece(pawnsq);
	if ( p != PAWN)
		return false;
	Rank r = getRank(pawnsq);
	if ( r != pawnsecondrank[ctm] && r !=  pawnthirdrank[ctm] )
		return false;

	sq = pawnsq + pawndirection[opp] + EAST ;
	if ( isSquare(sq) && !isEmpty(sq) && isOurs(sq))
	{
		if (  getPiece(sq) & ( ROOK | QUEEN | BISHOP | KNIGHT ) )
			return true;
	}
	sq = pawnsq + pawndirection[opp] + WEST ;
	if ( isSquare(sq) && !isEmpty(sq) && isOurs(sq))
	{
		if ( getPiece(sq) & ( ROOK | QUEEN | BISHOP | KNIGHT ) )
			return true;
	}
	return false;
}