/*******************************************************************
* GenerateIntMoves ()
* Generates every move possible from this position taking into account the 
* movement of the pieces.
* 
*/

#include "ChessGame.h"
#include <vector>


/********************************************
* Generates pseudo-legal moves for side to move
*/
void ChessGame::GenCaptures( void )
{
	mstack[ply].DumpStack();

	Square curr, sq;
	short i;

	for (  i = 0; i < maxpieces[ctm]; i++)
	{
		if ( ! pieces[i][ctm].piece)
			continue;
		curr = pieces[i][ctm].square;
		switch ( pieces[i][ctm].piece)
		{
		case QUEEN:
			for ( int c = 0; c < 8; c++)
			{
				for ( sq = curr + queenvectors[c]; isSquare(sq) && isEmpty(sq); sq += queenvectors[c]);
					/*mstack[ply].push(
					CM(curr,
					sq,
					MT_NORMAL,
					0));*/

				if ( isSquare(sq) && isOpponent(sq) )
					mstack[ply].push(
					CM(curr,
					sq,
					MT_CAPTURE,
					getPiece(sq)));
			}
			break;
		case BISHOP:
			for ( int c = 0; c < 4; c++)
			{
				for ( sq = curr + bishopvectors[c]; isSquare(sq) && isEmpty(sq); sq += bishopvectors[c]);
				/*	mstack[ply].push(
					CM(curr,
					sq,
					MT_NORMAL,
					0));*/

				if ( isSquare(sq) && isOpponent(sq) )
					mstack[ply].push(
					CM(curr,
					sq,
					MT_CAPTURE,
					getPiece(sq)));
			}
			break;
		case ROOK:
			for ( int c = 0; c < 4; c++)
			{
				for ( sq = curr + rookvectors[c]; isSquare(sq) && isEmpty(sq); sq += rookvectors[c]);
					/*mstack[ply].push(
					CM(curr,
					sq,
					MT_NORMAL,
					0));*/

				if ( isSquare(sq) && isOpponent(sq) )
					mstack[ply].push(
					CM(curr,
					sq,
					MT_CAPTURE,
					getPiece(sq)));
			}
			break;
		case KNIGHT:
			for ( int c = 0; c < 8; c++)
			{
				sq = curr + knightvectors[c];
				if ( isSquare(sq))
				{
					/*if (isEmpty(sq))
						mstack[ply].push(
						CM(curr,
						sq,
						MT_NORMAL,
						0));*/
					if (isOpponent(sq))
						mstack[ply].push(
						CM(curr,
						sq,
						MT_CAPTURE,
						getPiece(sq)));
				}
			}
			break;
		case KING:
			//Castling Moves
		
			for ( int c = 0; c < 8; c++)
			{
				sq = curr + kingvectors[c];
				if ( isSquare(sq))
				{
			/*		if ( isEmpty(sq))
						mstack[ply].push(
						CM(curr,
						sq,
						MT_NORMAL,
						0));*/
					if ( isOpponent(sq))
						mstack[ply].push(
						CM(curr,
						sq,
						MT_CAPTURE,
						getPiece(sq)));
				}
			}
			break;
		case PAWN:
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
			// Check promotions first
			if ( getRank(pieces[i][ctm].square) == pawn_promotion_rank[ctm])
			{
				if ( isSquare(sq) && isEmpty(sq)){
					mstack[ply].push(CM(curr,sq,MT_PROMOTION,	QUEEN));
					mstack[ply].push(CM(curr,sq,MT_PROMOTION,	ROOK));
					mstack[ply].push(CM(curr,sq,MT_PROMOTION,	BISHOP));
					mstack[ply].push(CM(curr,sq,MT_PROMOTION,	KNIGHT));
				}
				if ( isSquare(sq + EAST) && isOpponent(sq + EAST)){
					mstack[ply].push(CM(curr,sq + EAST,	MT_CAPTURE | MT_PROMOTION,SetCapturePromotion(getPiece(sq + EAST), QUEEN)));
					mstack[ply].push(CM(curr,sq + EAST,	MT_CAPTURE | MT_PROMOTION,SetCapturePromotion(getPiece(sq + EAST), ROOK )));
					mstack[ply].push(CM(curr,sq + EAST,	MT_CAPTURE | MT_PROMOTION,SetCapturePromotion(getPiece(sq + EAST), BISHOP)));
					mstack[ply].push(CM(curr,sq + EAST,	MT_CAPTURE | MT_PROMOTION,SetCapturePromotion(getPiece(sq + EAST), KNIGHT)));
				}
				if ( isSquare(sq + WEST) && isOpponent(sq + WEST)){
					mstack[ply].push(CM(curr,sq + WEST,	MT_CAPTURE | MT_PROMOTION,	SetCapturePromotion(getPiece(sq + WEST), QUEEN)));
					mstack[ply].push(CM(curr,sq + WEST,	MT_CAPTURE | MT_PROMOTION,	SetCapturePromotion(getPiece(sq + WEST), ROOK)));
					mstack[ply].push(CM(curr,sq + WEST,	MT_CAPTURE | MT_PROMOTION,	SetCapturePromotion(getPiece(sq + WEST), BISHOP)));
					mstack[ply].push(CM(curr,sq + WEST,	MT_CAPTURE | MT_PROMOTION,	SetCapturePromotion(getPiece(sq + WEST), KNIGHT)));
				}
			}
			else// Regular pawn moves
			{
				/*if ( isSquare(sq) && isEmpty(sq))
					mstack[ply].push(
					CM(curr,
					sq,
					MT_NORMAL,
					0));*/
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
			break;
		}
	}
}

///****************************************************
//* Sort Moves using everything known
//****************************************************/
//void ChessGame::SortMoves( void )
//{
//	ASSERT(! mstack[ply].empty());
//	if ( ! pv.cmove ) // no info to act upon
//		return;
//	for ( int c = 0; c < mstack[ply].size() ; c++)
//		if ( isCapture(mstack[ply].inspect(c)))
//			mstack[ply].push(mstack[ply].Remove(c));
//
//	
//	ChessMove pvmove;
//	
//	if ( pv.cmove >= depthply )
//	{
//		pvmove = pv.argmove[depthply];
//
//		for ( int c = 0; c < mstack[ply].size(); c++){
//			if ( pvmove == mstack[ply].inspect(c) ){
//				mstack[ply].push(mstack[ply].Remove(c));
//				break;
//			}
//		}
//
//	}
//
//}