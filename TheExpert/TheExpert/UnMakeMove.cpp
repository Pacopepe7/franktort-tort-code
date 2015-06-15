
#include "chess.h"
#include "ChessPosition.h"
#include "utils.h"

/* To and From squares are reversed */
void UnMakeMove(ChessPosition * board, ChessMove cm, bool update)
{
	//ChessMove lastcm = board->unmake[board->historyply - 1].move;
	ASSERT(isSquare(FromSquare(cm)));
	ASSERT(isSquare(ToSquare(cm)));
	ASSERT(isBoardOK(board));
	ASSERT(board->historyply > 0);
	ASSERT(board->historyply < MAXMOVES);
	//cout << "UnMaking " << MakeMoveString(cm) << endl;
	//cout << "Old key: "; printf("Key:%llX\n", board->positionkey);	
	
	if (Promotion(cm))
	{
		Clear(board, ToSquare(cm), update);
		SetPiece(board, PAWN | ColorNotOnMove(), FromSquare(cm), update);
	}
	else
	MovePiece(board, ToSquare(cm), FromSquare(cm), update);

	//Unmaking EP move
	if (EPCapture(cm))
	{
		SetPiece(board, (PAWN) | SideToMove(), ToSquare(cm) + pawndirection[SideToMove()], update);
	}
	else 
	if (Capture(cm)){	
		ASSERT(CountBits(Capture(cm)) == 1);
		SetPiece(board, (Capture(cm) << 2) | SideToMove(), ToSquare(cm), update);
	}

	if (Castle(cm))
	{
		if (ToSquare(cm) == G1)		{
			Clear(board, F1, update);
			SetPiece(board, (ROOK) | ColorNotOnMove(), H1, update);
		}
		if (ToSquare(cm) == C1)		{
			Clear(board, D1, update);
			SetPiece(board, (ROOK) | ColorNotOnMove(), A1, update);
		}
		if (ToSquare(cm) == G8)		{
			Clear(board, F8, update);
			SetPiece(board, (ROOK) | ColorNotOnMove(), H8, update);
		}
		if (ToSquare(cm) == C8)		{
			Clear(board, D8, update);
			SetPiece(board, (ROOK) | ColorNotOnMove(), A8, update);
		}
	}


	board->ply--;
	board->historyply--;



	//Restore position flags
	board->castlingprivileges = board->unmake[board->historyply].castlingprivileges;
	board->enpassantsquare = board->unmake[board->historyply].enpassantsquare;
	board->fiftymoverule = board->unmake[board->historyply].fiftymoverule;
	board->positionkey = board->unmake[board->historyply].positionkey;
	board->PSQT[WHITE] = board->unmake[board->historyply].psqt[WHITE];
	board->PSQT[BLACK] = board->unmake[board->historyply].psqt[BLACK];
	//cout << "New key: "; printf("Key:%llX\n", board->positionkey); 

	board->sideToMove = Opponent();
	ASSERT(isBoardOK(board));
}
