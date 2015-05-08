
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

	MovePiece(board, ToSquare(cm), FromSquare(cm));
	if (Capture(cm)){
		SetPiece(board, (Capture(cm) << 2) | ColorOnMove(), ToSquare(cm));
		//PrintBoard(board);
	}
	board->ply--;
	board->historyply--;
	board->sideToMove = Opponent();
	ASSERT(isBoardOK(board));
}
