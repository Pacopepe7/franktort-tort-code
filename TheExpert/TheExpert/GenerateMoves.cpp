#include "ChessPosition.h"
#include <iostream>
using namespace std;


void AddQuietMove(const ChessPosition * board, const ChessMove cm, MOVELIST * list)
{
	ASSERT(isSquare(FromSquare(cm)));
	ASSERT(isSquare(ToSquare(cm)));
	ASSERT(isEmpty(ToSquare(cm)));

	list->move[list->index] = cm;
	list->index++;
}

void AddCapture(const ChessPosition * board, const ChessMove cm, MOVELIST * list)
{
	//To square CAN be empty, enpassant capture...
	if (!isEmpty(ToSquare(cm))){
		if ((getPiece(ToSquare(cm)) & KING))
		{
			PrintBoard(board);
			cout << MakeMoveString(cm) << "   " << endl;
		}
		ASSERT(!(getPiece(ToSquare(cm)) & KING));
		ASSERT(isOpponent(ToSquare(cm)));	
		ASSERT(isPieceAt(ToSquare(cm), PIECE));
	}
	ASSERT(isSquare(FromSquare(cm)));
	ASSERT(isSquare(ToSquare(cm)));
	if (!EPCapture(cm))
	{
		ASSERT(!isEmpty(ToSquare(cm)));
		ASSERT(!(getPiece(ToSquare(cm)) & KING));
		//ASSERT()
		
	}
	if (Promotion(cm)){
		ASSERT(Promotion(cm) & PROMOTIONPIECEMASK);
		ASSERT(Promotion(cm) & ((QUEEN | BISHOP | ROOK | KNIGHT) >> 3));
		ASSERT(CountBits(Promotion(cm)) == 1);
	}
	if (Capture(cm)){
		ASSERT(CountBits(Capture(cm)) == 1);
	}
	list->move[list->index] = cm;
	list->index++;
}
void GenerateMoves(const ChessPosition * board, MOVELIST * list)
{
	list->index = -1;
	
	Color color = board->sideToMove;
	Piece p;
	Location sq;
	Location direction;

	short i, c;

	for (i = 0; i < MAXPIECES; i++)
	{
		const Location curr = board->pieces[i][color].lLocation;
		if (curr == INVALID)
			continue;
		p = board->pieces[i][color].pPiece;

		switch (p)
		{
		case QUEEN:
			
			for (c = 0; c < MAXQUEENVECTORS; c++)
			{
				for (sq = curr + queenvectors[c]; isSquare(sq) && isEmpty(sq); sq += queenvectors[c])
					AddQuietMove(board, CM(curr, sq, EMPTY, EMPTY, EMPTY), list);
					
				if (isSquare(sq) && isOpponent(sq))
					AddCapture(board, CM(curr, sq, getPieceWOColor(sq), EMPTY, EMPTY), list);
			}
			break;
		case BISHOP:

			for (c = 0; c < MAXBISHOPVECTORS; c++)
			{
				for (sq = curr + bishopvectors[c]; isSquare(sq) && isEmpty(sq); sq += bishopvectors[c])
					AddQuietMove(board, CM(curr, sq, EMPTY, EMPTY, EMPTY), list);
				if (isSquare(sq) && isOpponent(sq))
					AddCapture(board, CM(curr, sq, getPieceWOColor(sq), EMPTY, EMPTY), list);
			}
			break;
		case ROOK:
			for (c = 0; c < MAXROOKVECTORS; c++)
			{
				for (sq = curr + rookvectors[c]; isSquare(sq) && isEmpty(sq) ; sq += rookvectors[c])
					AddQuietMove(board, CM(curr, sq, EMPTY, EMPTY, EMPTY), list);
				if (isSquare(sq) && isOpponent(sq))
					AddCapture(board, CM(curr, sq, getPieceWOColor(sq), EMPTY, EMPTY), list);
				
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
						else if (isOpponent(sq)){
								AddCapture(board, CM(curr, sq, getPieceWOColor(sq), EMPTY, EMPTY), list);
							}
					}
			}
			break;
		case KING:
			//Castling Moves
			if (ColorOnMove() == WHITE)
			{
				if (board->castlingprivileges & WHITESHORT)
				{
					if (isEmpty(F1) && isEmpty(G1) &&
						!isAttacked(board, E1, Opponent()) &&
						!isAttacked(board, F1, Opponent()) &&
						!isAttacked(board, G1, Opponent()))
						AddQuietMove(board, CM(E1, G1, EMPTY, EMPTY, MT_CASTLE), list );
				}
				if (board->castlingprivileges & WHITELONG)
				{
					if (isEmpty(D1) && isEmpty(C1) && isEmpty(B1) &&
						!isAttacked(board, E1, Opponent()) &&
						!isAttacked(board, D1, Opponent()) &&
						!isAttacked(board, C1, Opponent()))
						AddQuietMove(board, CM(E1, C1, EMPTY, EMPTY, MT_CASTLE), list);
				}
			}
			else
			{
				if (board->castlingprivileges & BLACKSHORT)
				{
					if (isEmpty(F8) && isEmpty(G8) &&
						!isAttacked(board, E8, Opponent()) &&
						!isAttacked(board, F8, Opponent()) &&
						!isAttacked(board, G8, Opponent()))
						AddQuietMove(board, CM(E8, G8, EMPTY, EMPTY, MT_CASTLE), list);
				}
				if (board->castlingprivileges & BLACKLONG)
				{
					if (isEmpty(D8) && isEmpty(C8) && isEmpty(B8) &&
						!isAttacked(board, E8, Opponent()) &&
						!isAttacked(board, D8, Opponent()) &&
						!isAttacked(board, C8, Opponent()))
						AddQuietMove(board, CM(E8, C8, EMPTY, EMPTY, MT_CASTLE), list);
				}
			}
			for (c = 0; c < 8; c++)
			{
				sq = curr + kingvectors[c];
				if (isSquare(sq))
				{
					if (isEmpty(sq))
						AddQuietMove(board, CM(curr, sq, EMPTY, EMPTY, EMPTY), list);
					else if (isOpponent(sq))
						AddCapture(board, CM(curr, sq, getPieceWOColor(sq), EMPTY, EMPTY), list);
				}
			}
			break;
		case PAWN:
			direction = pawndirection[ColorOnMove()];
			sq = curr + direction;
			////second/seventh rank special jump
			if (getRank(board->pieces[i][ColorOnMove()].lLocation) == secondrank[ColorOnMove()])
				if (isEmpty(sq) && isEmpty(sq + (direction)))
					AddQuietMove(board, CM(curr, sq + (direction), EMPTY, EMPTY, MT_ENPASSANTPOSSIBLE), list);
			// Check promotions
			if (getRank(board->pieces[i][ColorOnMove()].lLocation) == pawn_promotion_rank[ColorOnMove()])
			{

				if (isSquare(sq) && isEmpty(sq)){
					AddQuietMove(board, CM(curr, sq, EMPTY, (QUEEN >> 3), EMPTY), list);
					AddQuietMove(board, CM(curr, sq, EMPTY, (ROOK >> 3), EMPTY), list);
					AddQuietMove(board, CM(curr, sq, EMPTY, (BISHOP >> 3), EMPTY), list);
					AddQuietMove(board, CM(curr, sq, EMPTY, (KNIGHT >> 3), EMPTY), list);
				}
				if (isSquare(sq + EAST) && !isEmpty(sq + EAST) && isOpponent(sq + EAST)){
					AddCapture(board, CM(curr, sq + EAST, getPieceWOColor(sq + EAST), (QUEEN >> 3), EMPTY), list);
					AddCapture(board, CM(curr, sq + EAST, getPieceWOColor(sq + EAST), (ROOK >> 3), EMPTY), list);
					AddCapture(board, CM(curr, sq + EAST, getPieceWOColor(sq + EAST), (BISHOP >> 3), EMPTY), list);
					AddCapture(board, CM(curr, sq + EAST, getPieceWOColor(sq + EAST), (KNIGHT >> 3), EMPTY), list);
				}
				if (isSquare(sq + WEST) && !isEmpty(sq + WEST) && isOpponent(sq + WEST)){
					AddCapture(board, CM(curr, sq + WEST, getPieceWOColor(sq + WEST), (QUEEN >> 3), EMPTY), list);
					AddCapture(board, CM(curr, sq + WEST, getPieceWOColor(sq + WEST), (ROOK >> 3), EMPTY), list);
					AddCapture(board, CM(curr, sq + WEST, getPieceWOColor(sq + WEST), (BISHOP >> 3), EMPTY), list);
					AddCapture(board, CM(curr, sq + WEST, getPieceWOColor(sq + WEST), (KNIGHT >> 3), EMPTY), list);
				}
			}
			else{


				if (isEmpty(sq))
					AddQuietMove(board, CM(curr, sq, EMPTY, EMPTY, EMPTY), list);

				if (isSquare(sq + WEST))
					if (!isEmpty(sq + WEST))
						if (isOpponent(sq + WEST))
							AddCapture(board, CM(curr, sq + WEST, getPieceWOColor(sq + WEST), EMPTY, EMPTY), list);

				if (isSquare(sq + EAST))
					if (!isEmpty(sq + EAST))
						if (isOpponent(sq + EAST))
							AddCapture(board, CM(curr, sq + EAST, getPieceWOColor(sq + EAST), EMPTY, EMPTY), list);
			}
			//fifth and fourth rank special check for ep capture.
			if (board->enpassantsquare != INVALID)
			{
				//cout << "EP square != INVALID" << endl;
				if (getRank(board->pieces[i][ColorOnMove()].lLocation) == ep_rank[ColorOnMove()])
				{
					//cout << "pawn is on ep_rank"  << endl;
					if ((sq + EAST) == board->enpassantsquare)
					{
						//cout << "Adding EP Capture" << endl;
						AddCapture(board, CM(curr, sq + EAST, (PAWN >> 2), EMPTY, MT_EPCAPTURE), list);
					}
					if ((sq + WEST) == board->enpassantsquare)
					{
						//cout << "Adding EP Capture" << endl;
						AddCapture(board, CM(curr, sq + WEST, (PAWN >> 2), EMPTY, MT_EPCAPTURE), list);
					}
				}
			}
		}
	}
}