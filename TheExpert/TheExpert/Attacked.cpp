#include "ChessPosition.h"
#include <iostream>
using namespace std;

/* is "target" square attacked by "color" on "board" */
bool isAttacked(const ChessPosition * board, const Location target, const Color color)
{
	ASSERT(board);
	ASSERT(isSquare(target));
	ASSERT(isValidColor(color));

	int c;
	Location sq;

	//Sliding Pieces.

	for (c = 0; c < MAXQUEENVECTORS; c++)
	{
		for (sq = target + queenvectors[c]; isSquare(sq) && isEmpty(sq); sq += queenvectors[c]);
		if (isSquare(sq))
			if (isColor(sq, color)){
				if (isPieceAt(sq, QUEEN))
					return true;
				if (isPieceAt(sq, BISHOP) && ((c % 2) == 1))
					return true;
				if (isPieceAt(sq, ROOK) && ((c % 2) == 0))
					return true;


			}
	}

	//KNIGHT:
	for (c = 0; c < MAXKNIGHTVECTORS; c++)
	{
		sq = target + knightvectors[c];
		if (isSquare(sq))
		{
			if (!isEmpty(sq))
				if (isColor(sq, color) && isPieceAt(sq, KNIGHT))
					return true;
		}
	}
	//King
	for (c = 0; c < 8; c++)
	{
		sq = target + kingvectors[c];
		if (isSquare(sq))
		{
			if (!isEmpty(sq))
				if (isColor(sq, color) && isPieceAt(sq, KING))
					return true;
		}
	}
	//PAWNS
	if (isWhite(color)){
		if (isSquare(target + NORTHWEST) && !isEmpty(target + NORTHWEST))
			if (isColor(target + NORTHWEST, color) && isPieceAt(target + NORTHWEST, PAWN))
				return true;
		if (isSquare(target + NORTHEAST) && !isEmpty(target + NORTHEAST))
			if (isColor(target + NORTHEAST, color) && isPieceAt(target + NORTHEAST, PAWN))
				return true;
	}
	else{
		if (isSquare(target + SOUTHWEST) && !isEmpty(target + SOUTHWEST))
			if (isColor(target + SOUTHWEST, color) && isPieceAt(target + SOUTHWEST, PAWN))
				return true;
		if (isSquare(target + SOUTHEAST) && !isEmpty(target + SOUTHEAST))
			if (isColor(target + SOUTHEAST, color) && isPieceAt(target + SOUTHEAST, PAWN))
				return true;
	}
	return false;
}


