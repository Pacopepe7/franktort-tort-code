
#include "chess.h"
#include "ChessPosition.h"
#include "utils.h"

/* To and From squares are reversed */
void UnMakeMove(ChessPosition * board, ChessMove cm)
{
	//ChessMove lastcm = board->unmake[board->historyply - 1].move;
	ASSERT(isSquare(FromSquare(cm)));
	ASSERT(isSquare(ToSquare(cm)));
	ASSERT(isBoardOK(board));
	ASSERT(board->historyply > 0);
	//cout << "UnMaking " << MakeMoveString(cm) << endl;
	//cout << "Old key: "; printf("Key:%llX\n", board->positionkey);	
	
	if (Promotion(cm))
	{
		Clear(board, ToSquare(cm));
		SetPiece(board, PAWN | ColorNotOnMove(), FromSquare(cm));
	}
	else
	MovePiece(board, ToSquare(cm), FromSquare(cm));

	//Unmaking EP move
	if (EPCapture(cm))
	{
		SetPiece(board, (PAWN) | SideToMove(), ToSquare(cm) + pawndirection[SideToMove()]);
	}
	else 
	if (Capture(cm)){	
		ASSERT(CountBits(Capture(cm)) == 1);
		SetPiece(board, (Capture(cm) << 2) | SideToMove(), ToSquare(cm));
	}

	if (Castle(cm))
	{
		if (ToSquare(cm) == G1)		{
			Clear(board, F1);
			SetPiece(board, (ROOK) | ColorNotOnMove(), H1);
		}
		if (ToSquare(cm) == C1)		{
			Clear(board, D1);
			SetPiece(board, (ROOK) | ColorNotOnMove(), A1);
		}
		if (ToSquare(cm) == G8)		{
			Clear(board, F8);
			SetPiece(board, (ROOK) | ColorNotOnMove(), H8);
		}
		if (ToSquare(cm) == C8)		{
			Clear(board, D8);
			SetPiece(board, (ROOK) | ColorNotOnMove(), A8);
		}
	}


	board->ply--;
	board->historyply--;



	//Restore position flags
	board->castlingprivileges = board->unmake[board->historyply].castlingprivileges;
	board->enpassantsquare = board->unmake[board->historyply].enpassantsquare;
	board->fiftymoverule = board->unmake[board->historyply].fiftymoverule;
	board->positionkey = board->unmake[board->historyply].positionkey;
	//cout << "New key: "; printf("Key:%llX\n", board->positionkey); 

	board->sideToMove = Opponent();
	ASSERT(isBoardOK(board));
}
