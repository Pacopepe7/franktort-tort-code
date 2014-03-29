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
		if ( attacker & PAWN )
		{
		}
		if ( attacker & QUEEN )
		{
			if ( pieces[i][ctm].piece & QUEEN)
			{
				for ( int c = 0; c < 8; c++)
				{
					for ( sq = Attackersq + queenvectors[c]; isSquare(sq) && isEmpty(sq); sq += queenvectors[c])
						if ( isSquare(sq) && isOpponent(sq) )
							return true;
				}
			}
		}


	}

	return true;
}
bool ChessGame::Attacks(Square s1, Square s2)
{
	int diff = s2 - s1;
	if ( diff % 17 == 0 ) // King, Queen, Bishop (diagonal)
	{


	}
	return true;
}
bool ChessGame::isAttacked ( Square sq, Color side )
{


	// skip to square x, check if a piece from "side" is attacking this square
	//checking for pawns, pawns are the only piece we care about the color, because they move 
	// differently depending on what color they are
	//int opponent = (side == WHITE) ? BLACK : WHITE;
	//int vector, dest;
	//int total = 0;
	///************************************************************
	//* the piece is a Bishop, Queen or Rook, they all move in the same direction as long as they don't go 
	//* outside the board or find a piece of the same color. 
	//*/
	///*for( vector = 0; vector < POSSIBLEMOVESQUEEN ; vector++)
	//{
	//	for(dest = x + queenvectors[vector]; isEmpty(dest ) ; dest += queenvectors[vector]);
	//	if ( isQueen(dest) && isColor(dest, side))
	//		return true;
	//}
	//for( vector = 0; vector < POSSIBLEMOVESROOK ; vector++)
	//{
	//	for(dest = x + rookvectors[vector]; isEmpty( dest ) ; dest +=rookvectors[vector]);
	//	if ( isRook(dest) && isColor(dest,side))
	//		return true;
	//}
	//for( vector = 0; vector < POSSIBLEMOVESBISHOP ; vector++)
	//{
	//	for(dest = x + bishopvectors[vector]; isEmpty(dest ) ; dest += bishopvectors[vector]);
	//	if ( isBishop(dest) && isColor(dest,side))
	//		return true;
	//}*/
	//for( vector = 0; vector < POSSIBLEMOVESQUEEN ; vector++)
	//{
	//	for(dest = x + queenvectors[vector]; isEmpty(dest ) ; dest += queenvectors[vector]);
	//	{
	//	if ( isQueen(dest) && isColor(dest, side))
	//		return true;
	//	if ( vector < 4 && isRook(dest) && isColor(dest, side))
	//		return true;
	//	if ( vector > 3 && isBishop(dest) && isColor(dest, side))
	//		return true;
	//	}
	//}
	//if ( side == WHITE ) 
	//{
	//	if ( isPawn(x + SOUTHEAST) && isColor(x + SOUTHEAST, WHITE)) 
	//		return true;
	//	if ( isPawn(x + SOUTHWEST) && isColor(x + SOUTHWEST, WHITE)) 
	//		return true;
	//}
	//else
	//{
	//	if ( isPawn(x + NORTHEAST) && isColor(x + NORTHEAST, BLACK)) 
	//		return true;
	//	if ( isPawn(x + NORTHWEST) && isColor(x + NORTHWEST, BLACK)) 
	//		return true;
	//}
	//for( vector = 0; vector < POSSIBLEMOVESKING ; vector++)
	//{
	//	if( isKing(x +  kingvectors[vector])  && 
	//		isColor(x + kingvectors[vector],side))
	//		return true;
	//}
	//for( vector = 0; vector < POSSIBLEMOVESKNIGHT ; vector++)
	//{
	//	if( isKnight(x +  knightvectors[vector]) && isColor(x +  knightvectors[vector], side))
	//		return true;
	//}


	return false;
} // end IsAttacked
