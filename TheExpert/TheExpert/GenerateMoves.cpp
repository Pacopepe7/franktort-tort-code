#include "ChessPosition.h"
#include <iostream>
using namespace std;


void AddQuietMove(ChessPosition * board, ChessMove cm, MOVELIST * list)
{

	//cout << "Adding move " << MakeMoveString(cm) << endl;
	//cout << "adding to list..." << endl;
	list->move[list->index] = cm;
	list->index++;
	//cout << "done adding to list..." << endl;
}

void AddCapture(ChessPosition * board, ChessMove cm, MOVELIST * list)
{
	ASSERT(Capture(cm));
	//cout << "Adding capt " << MakeMoveString(cm) << endl;
	list->move[list->index] = cm;

	list->index++;
}
void GenerateMoves(ChessPosition * board, MOVELIST * list)
{
	list->index = -1;
	
	Color color = board->sideToMove;
	Piece p;
	Location sq;

	short i, c;

	for (i = 0; i < MAXPIECES; i++)
	{
		const Location curr = board->pieces[i][color].lLocation;
		if (curr == INVALID)
			continue;
		p = (board->pieces[i][color].pPiece & (PIECE));
		//cout << "Piece is: " << p << endl;
		switch (p)
		{
		case QUEEN:
			for (c = 0; c < MAXQUEENVECTORS; c++)
			{
				for (sq = curr + queenvectors[c]; isSquare(sq) && isEmpty(sq) ; sq += queenvectors[c])
				{
					if (!isSquare(sq))
						break;
					ASSERT(isSquare(sq));
					if (isEmpty(sq))
						AddQuietMove(board, CM(curr, sq, EMPTY, EMPTY, EMPTY), list);
					else if (isOpponent(sq))
					{
						AddCapture(board, CM(curr, sq, (getPiece(sq) >> 2), EMPTY, EMPTY), list);
						break;
					}
				}
				
			
			}
			break;
		case BISHOP:
			for (c = 0; c < MAXBISHOPVECTORS; c++)
			{
				for (sq = curr + bishopvectors[c]; isSquare(sq) && isEmpty(sq); sq += bishopvectors[c])
				{
					if (!isSquare(sq))
						break;
					
					if (isEmpty(sq))
						AddQuietMove(board, CM(curr, sq, EMPTY, EMPTY, EMPTY), list);
					else
					if (isOpponent(sq)){
						AddCapture(board, CM(curr, sq, (getPiece(sq)>>2), EMPTY, EMPTY), list);
						break;
					}
				}
			}
			break;
		case ROOK:
			for (c = 0; c < MAXROOKVECTORS; c++)
			{
				for (sq = curr + rookvectors[c]; isSquare(sq) && isEmpty(sq) ; sq += rookvectors[c])
				{
					if (!isSquare(sq))
						break;

					if (isEmpty(sq))
						AddQuietMove(board, CM(curr, sq, EMPTY, EMPTY, EMPTY), list);
					else
					if (isOpponent(sq))
					{
						AddCapture(board, CM(curr, sq, (getPiece(sq) >> 2), EMPTY, EMPTY), list);
						break;
					}
				}

			}
			break;
		case KNIGHT:
			for (c = 0; c < MAXKNIGHTVECTORS; c++)
			{
				
					sq = curr + knightvectors[c];
					
					if (isSquare(sq))
					{
						if (isEmpty(sq))
							AddQuietMove(board, CM(curr, sq, EMPTY, EMPTY, EMPTY), list);
						else if (isOpponent(sq))
							{
								AddCapture(board, CM(curr, sq, (getPiece(sq) >> 2), EMPTY, EMPTY), list);
								//ASSERT(!((getPiece(sq) >> 3) == PAWN));
							}
						//AddCapture(board, CM(curr, sq, (getPiece(sq) >> 3), EMPTY, EMPTY), list);
					}
			}
			break;
		case KING:
			////Castling Moves
			//if (sideToMove == WHITE)
			//{
			//	if (castling[sideToMove] & SHORT)
			//	{
			//		if (isEmpty(F1) && isEmpty(G1) && !isAttacked(E1, opp) && !isAttacked(F1, opp) && !isAttacked(G1, opp))
			//			mstack[ply].push(ChessMove(E1, G1, MT_CASTLE, 0));
			//	}
			//	if (castling[sideToMove] & LONG)
			//	{
			//		if (isEmpty(D1) && isEmpty(C1) && isEmpty(B1) && !isAttacked(E1, opp) && !isAttacked(D1, opp) && !isAttacked(C1, opp))
			//			mstack[ply].push(ChessMove(E1, C1, MT_CASTLE, 0));
			//	}
			//}
			//else
			//{
			//	if (castling[sideToMove] & SHORT)
			//	{
			//		if (isEmpty(F8) && isEmpty(G8) && !isAttacked(E8, opp) && !isAttacked(F8, opp) && !isAttacked(G8, opp))
			//			mstack[ply].push(ChessMove(E8, G8, MT_CASTLE, 0));
			//	}
			//	if (castling[sideToMove] & LONG)
			//	{
			//		if (isEmpty(D8) && isEmpty(C8) && isEmpty(B8) && !isAttacked(E8, opp) && !isAttacked(D8, opp) && !isAttacked(C8, opp))
			//			mstack[ply].push(ChessMove(E8, C8, MT_CASTLE, 0));
			//	}
			//}
			for (c = 0; c < 8; c++)
			{
				sq = curr + kingvectors[c];
				if (isSquare(sq))
				{
					if (isEmpty(sq))
						AddQuietMove(board, CM(curr, sq, EMPTY, EMPTY, EMPTY), list);
					else if (isOpponent(sq))
						AddCapture(board, CM(curr, sq, (getPiece(sq) >> 2), EMPTY, EMPTY), list);
				}
			}
			break;
		case PAWN:
			int pawndirection;
			int seventhrank;
			int secondrank;
			int pawn_promotion_rank;
			if (board->sideToMove == WHITE)
			{
				pawndirection = SOUTH;
				seventhrank = 0;
				secondrank = 6; // 0-7
				pawn_promotion_rank = 0;
			}
			else
			{
				pawndirection = NORTH;
				seventhrank = 0;
				secondrank = 1; // 0 - 7
				pawn_promotion_rank = 0;
			}


			sq = curr + pawndirection;

			////second/seventh rank special jump
			if (getRank(board->pieces[i][board->sideToMove].lLocation) == secondrank)
				if (isEmpty(sq) && isEmpty(curr + (pawndirection * 2)))
					AddQuietMove(board, CM(curr, curr + (pawndirection * 2), EMPTY, EMPTY, MT_ENPASSANTPOSSIBLE), list);
			//fifth and fourth rank special check for ep capture.
			//if (getRank(pieces[i][ctm].square) == pawn_EP_rank[ctm])
			//{
			//	if (sq + EAST == state[ply].epsquare)
			//		mstack[ply].push(
			//		ChessMove(curr,
			//		sq + EAST,
			//		MT_ENPASSANT,
			//		0));
			//	if (sq + WEST == state[ply].epsquare)
			//		mstack[ply].push(
			//		ChessMove(curr,
			//		sq + WEST,
			//		MT_ENPASSANT,
			//		0));
			//}

			// Check promotions first
			/*if (getRank64(pieces[i][sideToMove].getLocation()) == pawn_promotion_rank))
			{*/
				//if (isSquare(sq) && isEmpty(sq)){
				//	mstack[ply].push(ChessMove(curr, sq, MT_PROMOTION, QUEEN));
				//	mstack[ply].push(ChessMove(curr, sq, MT_PROMOTION, ROOK));
				//	mstack[ply].push(ChessMove(curr, sq, MT_PROMOTION, BISHOP));
				//	mstack[ply].push(ChessMove(curr, sq, MT_PROMOTION, KNIGHT));
				//}
				//if (isSquare(sq + EAST) && isOpponent(sq + EAST)){
				//	mstack[ply].push(ChessMove(curr, sq + EAST, MT_CAPTURE | MT_PROMOTION, SetCapturePromotion(getPiece(sq + EAST), QUEEN)));
				//	mstack[ply].push(ChessMove(curr, sq + EAST, MT_CAPTURE | MT_PROMOTION, SetCapturePromotion(getPiece(sq + EAST), ROOK)));
				//	mstack[ply].push(ChessMove(curr, sq + EAST, MT_CAPTURE | MT_PROMOTION, SetCapturePromotion(getPiece(sq + EAST), BISHOP)));
				//	mstack[ply].push(ChessMove(curr, sq + EAST, MT_CAPTURE | MT_PROMOTION, SetCapturePromotion(getPiece(sq + EAST), KNIGHT)));
				//}
				//if (isSquare(sq + WEST) && isOpponent(sq + WEST)){
				//	mstack[ply].push(ChessMove(curr, sq + WEST, MT_CAPTURE | MT_PROMOTION, SetCapturePromotion(getPiece(sq + WEST), QUEEN)));
				//	mstack[ply].push(ChessMove(curr, sq + WEST, MT_CAPTURE | MT_PROMOTION, SetCapturePromotion(getPiece(sq + WEST), ROOK)));
				//	mstack[ply].push(ChessMove(curr, sq + WEST, MT_CAPTURE | MT_PROMOTION, SetCapturePromotion(getPiece(sq + WEST), BISHOP)));
				//	mstack[ply].push(ChessMove(curr, sq + WEST, MT_CAPTURE | MT_PROMOTION, SetCapturePromotion(getPiece(sq + WEST), KNIGHT)));
				//}
			//}
			//else// Regular pawn moves
			//{
			if (isEmpty(curr + (pawndirection)))
					AddQuietMove(board, CM(curr, curr + (pawndirection ), EMPTY, EMPTY, EMPTY), list);
				//if (isSquare64(sq + EAST64) && Opponent() == getColor64(sq))
				//	mstack[ply].push(
				//	ChessMove(curr,
				//	sq + EAST,
				//	MT_CAPTURE,
				//	getPiece(sq + EAST)));
				//if (isSquare(sq + WEST) && isOpponent(sq + WEST))
				//	mstack[ply].push(
				//	ChessMove(curr,
				//	sq + WEST,
				//	MT_CAPTURE,
				//	getPiece(sq + WEST)));
				//}
				//break;
			//}
		}
	}
}