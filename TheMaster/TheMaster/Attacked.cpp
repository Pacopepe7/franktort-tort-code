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
	
	Square oppking = state[ply].king[opp];
	Square sq; int c;
	//check for pawns, kings and knights
	//Pawns
	if ( ctm == WHITE )
	{
		if ( isSquare( oppking + SOUTHWEST) && getPiece( oppking + SOUTHWEST) == PAWN && isOurs(oppking + SOUTHWEST))
			return false;
		if ( isSquare( oppking + SOUTHEAST) && getPiece( oppking + SOUTHEAST) == PAWN && isOurs(oppking + SOUTHEAST))
			return false;
	}
	else
	{
		if ( isSquare( oppking + NORTHWEST) && getPiece( oppking + NORTHWEST) == PAWN && isOurs(oppking + NORTHWEST))
			return false;
		if ( isSquare( oppking + NORTHEAST) && getPiece( oppking + NORTHEAST) == PAWN && isOurs(oppking + NORTHEAST))
			return false;
	}
	//King
	for ( c = 0; c < 8; c++)
	{
		sq = oppking + kingvectors[c];
		if ( isSquare(sq) && getPiece(sq) == KING && isOurs(sq))
			return false;
	}
	//Knight
	for ( c = 0; c < 8; c++)
	{
		sq = oppking + knightvectors[c];
		if ( isSquare(sq) && getPiece(sq) == KNIGHT && isOurs(sq))
			return false;
	}
	// check for sliding pieces.
	for ( c = 0; c < 8; c++){

		for ( sq = oppking + queenvectors[c]; isSquare(sq) && isEmpty(sq) ; sq += queenvectors[c]);
		{
			if ( isSquare(sq) && isOurs(sq) ) // we have a hit!
			{
				if ( getPiece(sq) == QUEEN)
					return false;
				if ( c % 2 == 0 && getPiece(sq) == ROOK)
					return  false;
				if ( c % 2 == 1 && getPiece(sq) == BISHOP)
					return false ;
			}
		}
	}

	/**********************************************
	* Did the opponent just left his king in check?
	* I made the last move so its my king!!
	*/
	//for ( int i = 0; i < maxpieces[ctm]; i++)
	//{
	//	if ( pieces[i][ctm].piece)
	//		if ( isAttackedbyPiece(pieces[i][ctm].square, state[ply].king[opp], ctm, pieces[i][ctm].piece ))
	//			return false;
	//}
		
	return true;

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
bool ChessGame::isAttacked(Square sq, Color c)
{
	ASSERT (isSquare(sq) && "isAttacked: ");
	for ( int i = 0; i < maxpieces[c]; i++)
	{
		if ( pieces[i][c].piece)
			if ( isAttackedbyPiece(pieces[i][c].square, sq, c, pieces[i][c].piece ))
				return true;
	}


	return false;
}