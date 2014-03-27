/********************************************
*
*
*/

#include "ChessBoard.h"


bool ChessBoard::isAttacked ( int x, int side )
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
