/*******************************************************************
* GenerateIntMoves ()
* Generates every move possible from this position taking into account the 
* movement of the pieces.
* 
*/

#include "ChessGame.h"
#include <vector>


/********************************************
* Generates LEGAL moves for side to move
*/
void ChessGame::GenerateMoves( void )
{
	Color ctm = state.ctm;
	Square curr;
	Square sq;
	for ( short i = 0; i < maxpieces[ctm]; i++)
	{
		if ( ! pieces[i][ctm].piece)
			continue;
		curr = pieces[i][ctm].square;
		if ( pieces[i][ctm].piece & KNIGHT)
		{
			for ( int c = 0; c < 8; c++)
			{
				sq = curr + knightvectors[c];
				if ( isSquare(sq))
				{
					if (isEmpty(sq))
						mstack[state.ply].push(
						CM(curr,
						sq,
						MT_NORMAL,
						0));
					if (isOpponent(sq))
						mstack[state.ply].push(
						CM(curr,
						sq,
						MT_CAPTURE,
						getPiece(sq)));
				}
			}
		}

		if ( pieces[i][ctm].piece & KING)
		{
			for ( int c = 0; c < 8; c++)
			{
				sq = curr + kingvectors[c];
				if ( isSquare(sq))
				{
					if ( isEmpty(sq))
						mstack[state.ply].push(
						CM(curr,
						sq,
						MT_NORMAL,
						0));
					if ( isOpponent(sq))
						mstack[state.ply].push(
						CM(curr,
						sq,
						MT_CAPTURE,
						getPiece(sq)));
				}
			}
		}
		if ( pieces[i][ctm].piece & BISHOP)
		{
			for ( int c = 0; c < 4; c++)
			{
				for ( sq = curr + bishopvectors[c]; isSquare(sq) && isEmpty(sq); sq += bishopvectors[c])
					mstack[state.ply].push(
					CM(curr,
					sq,
					MT_NORMAL,
					0));

				if ( isSquare(sq) && isOpponent(sq) )
					mstack[state.ply].push(
					CM(curr,
					sq,
					MT_CAPTURE,
					getPiece(sq)));
			}
		}
		if ( pieces[i][ctm].piece & QUEEN)
		{
			for ( int c = 0; c < 8; c++)
			{
				for ( sq = curr + queenvectors[c]; isSquare(sq) && isEmpty(sq); sq += queenvectors[c])
					mstack[state.ply].push(
					CM(curr,
					sq,
					MT_NORMAL,
					0));

				if ( isSquare(sq) && isOpponent(sq) )
					mstack[state.ply].push(
					CM(curr,
					sq,
					MT_CAPTURE,
					getPiece(sq)));
			}
		}
		if ( pieces[i][ctm].piece & ROOK)
		{
			for ( int c = 0; c < 4; c++)
			{
				for ( sq = curr + rookvectors[c]; isSquare(sq) && isEmpty(sq); sq += rookvectors[c])
					mstack[state.ply].push(
					CM(curr,
					sq,
					MT_NORMAL,
					0));

				if ( isSquare(sq) && isOpponent(sq) )
					mstack[state.ply].push(
					CM(curr,
					sq,
					MT_CAPTURE,
					getPiece(sq)));
			}
		}
		if ( pieces[i][ctm].piece & PAWN)
		{
			sq = curr + pawndirection[ctm];
			//second/seventh rank special jump
			if ( getRank(pieces[i][ctm].square) == pawnsecondrank[ctm] )
				if ( isSquare(sq) && isSquare(curr +  (pawndirection[ctm] * 2)) && 
					isEmpty(sq) && isEmpty(curr +  (pawndirection[ctm] * 2)) )
					mstack[state.ply].push(
					CM(curr,
					curr +  (pawndirection[ctm] * 2),
					MT_ENPASSANTPOSSIBLE,
					sq));
			//fifth and fourth rank special check for ep capture.
			if ( getRank(pieces[i][ctm].square) == pawn_EP_rank[ctm] )
			{
				if ( sq + EAST == state.epsquare[state.ply - 1] ) 
					mstack[state.ply].push(
					CM(curr,
					sq + EAST,
					MT_ENPASSANT,
					0));
				if ( sq + WEST == state.epsquare[state.ply - 1] ) 
					mstack[state.ply].push(
					CM(curr,
					sq + WEST,
					MT_ENPASSANT,
					0));
			}
			//
			if ( isSquare(sq) && isEmpty(sq))
				mstack[state.ply].push(
				CM(curr,
				sq,
				MT_NORMAL,
				0));
			if ( isSquare(sq + EAST) && isOpponent(sq + EAST))
				mstack[state.ply].push(
				CM(curr,
				sq + EAST,
				MT_CAPTURE,
				getPiece(sq + EAST)));
			if ( isSquare(sq + WEST) && isOpponent(sq + WEST))
				mstack[state.ply].push(
				CM(curr,
				sq + WEST,
				MT_CAPTURE,
				getPiece(sq + WEST)));
		}
	}
}

