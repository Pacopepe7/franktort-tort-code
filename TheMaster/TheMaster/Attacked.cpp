/********************************************
*
*
*/

#include "ChessBoard.h"


int ChessBoard::IsAttacked ( int x, int side )
{
	
	// skip to square x, check if a piece from "side" is attacking this square
	//checking for pawns, pawns are the only piece we care about the color, because they move 
	// differently depending on what color they are
	int otherside = (side == WHITE) ? BLACK : WHITE;
	int vector, dest;
	int total = 0;
	if ( side == WHITE ) 
	{
		if ( isPawn(x + SOUTHEAST) && isColor(x + SOUTHEAST, WHITE)) 
			total ++;
		if ( isPawn(x + SOUTHWEST) && isColor(x + SOUTHWEST, WHITE)) 
			total ++;
	}
	else
	{
		if ( isPawn(x + NORTHEAST) && isColor(x + NORTHEAST, BLACK)) 
			total ++;
		if ( isPawn(x + NORTHWEST) && isColor(x + NORTHWEST, BLACK)) 
			total ++;
	}
	for( vector = 0; vector < possibleMoves(KING) ; vector++)
	{
		if( isKing(x +  kingvectors[vector])  && 
			isColor(x + kingvectors[vector],side))
			total++;
	}
	for( vector = 0; vector < possibleMoves(KNIGHT) ; vector++)
	{
		if( isKnight(x +  knightvectors[vector]) && isColor(x +  knightvectors[vector], side))
			total++;
	}
	/************************************************************
		* the piece is a Bishop, Queen or Rook, they all move in the same direction as long as they don't go 
		* outside the board or find a piece of the same color. 
		*/
		for( vector = 0; vector < possibleMoves(QUEEN) ; vector++)
		{
			for(dest = x + queenvectors[vector]; isEmpty(dest ) ; dest += queenvectors[vector]);
			if ( isQueen(dest) && isColor(dest, side))
				total ++;
		}
		/////////////////////////////////////
		for( vector = 0; vector < possibleMoves(ROOK) ; vector++)
		{
			for(dest = x + rookvectors[vector]; isEmpty( dest ) ; dest +=rookvectors[vector]);
			if ( isRook(dest) && isColor(dest,side))
				total ++;
		}
		for( vector = 0; vector < possibleMoves(BISHOP) ; vector++)
		{
			for(dest = x + bishopvectors[vector]; isEmpty(dest ) ; dest += bishopvectors[vector]);
			if ( isBishop(dest) && isColor(dest,side))
				total ++;
		}
		
		return total;
} // end IsAttacked
