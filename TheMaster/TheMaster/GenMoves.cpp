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
	mstack[ply].DumpStack();
	
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
						mstack[ply].push(
						CM(curr,
						sq,
						MT_NORMAL,
						0));
					if (isOpponent(sq))
						mstack[ply].push(
						CM(curr,
						sq,
						MT_CAPTURE,
						getPiece(sq)));
				}
			}
		}

		if ( pieces[i][ctm].piece & KING)
		{
			//Castling Moves
			if ( ctm == WHITE)
			{
			if ( state[ply].castling[ctm] & SHORT )
			{
				if ( !isAttacked(E1, opp) &&  !isAttacked(F1, opp) &&  !isAttacked(G1, opp) &&
					  isEmpty(F1) && isEmpty(G1))
					  mstack[ply].push(CM(E1,	G1, MT_CASTLE,0));
			}
			if ( state[ply].castling[ctm] & LONG)
			{
				if ( !isAttacked(E1, opp) &&  !isAttacked(D1, opp) &&  !isAttacked(C1, opp) &&
					  isEmpty(D1) && isEmpty(C1) && isEmpty(B1))
					  mstack[ply].push(CM(E1,	C1, MT_CASTLE,0));
			}
			}
			else
			{
			if ( state[ply].castling[ctm] & SHORT)
			{
				if ( !isAttacked(E8, opp) &&  !isAttacked(F8, opp) &&  !isAttacked(G8, opp) &&
					  isEmpty(F8) && isEmpty(G8))
					  mstack[ply].push(CM(E8,	G8, MT_CASTLE,0));
			}
			if ( state[ply].castling[ctm] & LONG)
			{
				if ( !isAttacked(E8, opp) &&  !isAttacked(D8, opp) &&  !isAttacked(C8, opp) &&
					  isEmpty(D8) && isEmpty(C8) && isEmpty(B8))
					  mstack[ply].push(CM(E8,	C8, MT_CASTLE,0));
			}
			}
			for ( int c = 0; c < 8; c++)
			{
				sq = curr + kingvectors[c];
				if ( isSquare(sq))
				{
					if ( isEmpty(sq))
						mstack[ply].push(
						CM(curr,
						sq,
						MT_NORMAL,
						0));
					if ( isOpponent(sq))
						mstack[ply].push(
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
					mstack[ply].push(
					CM(curr,
					sq,
					MT_NORMAL,
					0));

				if ( isSquare(sq) && isOpponent(sq) )
					mstack[ply].push(
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
					mstack[ply].push(
					CM(curr,
					sq,
					MT_NORMAL,
					0));

				if ( isSquare(sq) && isOpponent(sq) )
					mstack[ply].push(
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
					mstack[ply].push(
					CM(curr,
					sq,
					MT_NORMAL,
					0));

				if ( isSquare(sq) && isOpponent(sq) )
					mstack[ply].push(
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
					mstack[ply].push(
					CM(curr,
					curr +  (pawndirection[ctm] * 2),
					MT_ENPASSANTPOSSIBLE,
					sq));
			//fifth and fourth rank special check for ep capture.
			if ( getRank(pieces[i][ctm].square) == pawn_EP_rank[ctm] )
			{
				if ( sq + EAST == state[ply].epsquare ) 
					mstack[ply].push(
					CM(curr,
					sq + EAST,
					MT_ENPASSANT,
					0));
				if ( sq + WEST == state[ply].epsquare ) 
					mstack[ply].push(
					CM(curr,
					sq + WEST,
					MT_ENPASSANT,
					0));
			}
			//
			if ( isSquare(sq) && isEmpty(sq))
				mstack[ply].push(
				CM(curr,
				sq,
				MT_NORMAL,
				0));
			if ( isSquare(sq + EAST) && isOpponent(sq + EAST))
				mstack[ply].push(
				CM(curr,
				sq + EAST,
				MT_CAPTURE,
				getPiece(sq + EAST)));
			if ( isSquare(sq + WEST) && isOpponent(sq + WEST))
				mstack[ply].push(
				CM(curr,
				sq + WEST,
				MT_CAPTURE,
				getPiece(sq + WEST)));
		}
	}
}

