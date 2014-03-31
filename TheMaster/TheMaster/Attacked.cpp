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
	Color ctm = state.ctm;
	Color opp = ColorNotOnMove(); // is opponent on check and its our turn (! invalid !)

	Square kingsq = state.king[opp];

	/**********************************************/
	// Did the opponent just left his king in check?
	for ( int i = 0; i < maxpieces[ctm]; i++)
	{
		if ( pieces[i][ctm].piece)
		if ( isAttackedbyPiece(pieces[i][ctm].square, kingsq, ctm, pieces[i][ctm].piece ))
			return false;
	}

	return true;

}

bool ChessGame::isPositionValidOld(void)
{

	Color ctm = state.ctm;
	Color opp = ColorNotOnMove(); // is opponent on check and its our turn (! invalid !)

	Square kingsq = state.king[opp];
	Square sq;
	Piece PiecesAbleToAttack;
	Piece attacker;
	Square Attackersq;

	/***********************************************/
	
	for ( int i = 0; i < maxpieces[ctm]; i++)
	{
		attacker = pieces[i][ctm].piece;
		Attackersq = pieces[i][ctm].square;

		PiecesAbleToAttack = PiecesThatCanAttack(Attackersq, kingsq);

		if ( attacker & PAWN )
		{
			if ( kingsq ==Attackersq + pawndirection[ctm] + WEST )
				return false;
			if ( kingsq ==Attackersq + pawndirection[ctm] + EAST )
				return false;
		}
		if ( attacker & QUEEN )
		{
			for ( int c = 0; c < 8; c++)
			{
				for ( sq = Attackersq + queenvectors[c]; isSquare(sq) && isEmpty(sq); sq += queenvectors[c]);
				if ( kingsq == sq )
					return false;
			}
		}
		if ( attacker & ROOK )
		{
			for ( int c = 0; c < 4; c++)
			{
				for ( sq = Attackersq + rookvectors[c]; isSquare(sq) && isEmpty(sq); sq += rookvectors[c]);
				if ( kingsq == sq )
					return false;
			}
		}
		if ( attacker & BISHOP )
		{
			for ( int c = 0; c < 4; c++)
			{
				for ( sq = Attackersq + bishopvectors[c]; isSquare(sq) && isEmpty(sq); sq += bishopvectors[c]);
				if ( kingsq == sq )
					return false;
			}
		}
		if ( attacker & KNIGHT )
		{
			for ( int c = 0; c < 8; c++)
			{
				if ( kingsq == (Attackersq + knightvectors[c]) )
					return false;
			}
		}
		if ( attacker & KING )
		{
			for ( int c = 0; c < 8; c++)
			{
				if ( kingsq == ( Attackersq + kingvectors[c]) )
					return false;
			}
		}
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
