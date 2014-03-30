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
	Square sq;
	Piece PiecesAbleToAttack;
	Piece attacker;
	Square Attackersq;
	 

	for ( int i = 0; i < maxpieces[ctm]; i++)
	{
		attacker = pieces[i][ctm].piece;
		Attackersq = pieces[i][ctm].square;

		PiecesAbleToAttack = Attacks(Attackersq, kingsq);

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
Piece ChessGame::Attacks(Square s1, Square s2)
{
	int diff = s2 - s1;
	//if ( diff % 17 == 0 ) // King, Queen, Bishop (diagonal)
	{


	}
	return PAWN;
}
bool ChessGame::isAttacked ( Square sq, Color side )
{


	return false;
} // end IsAttacked
