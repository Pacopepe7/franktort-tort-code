#include "ChessPosition.h"

string MakeMoveString(ChessMove cm)
{
	ASSERT(isSquare(FromSquare(cm)));
	ASSERT(isSquare(ToSquare(cm)));
	//ASSERT(FromSquare(cm) != ToSquare(cm));

	string move = notation[FromSquare(cm)];
	move = move + notation[ToSquare(cm)];
	return move;
}
ChessMove MakeMoveFromString(ChessPosition * board, string move)
{
	MOVELIST list;
	ChessMove cm;
	string chessmove;

	GenerateMoves(board, &list);
	ASSERT(MovesStillLeft(list));
	while (MovesStillLeft(list))
	{
		cm = GetMoveFrom(list);
		chessmove = MakeMoveString(cm);
		if (move == chessmove)
			return cm;
	}
	return false;
}

void MakeMove(ChessPosition * board, ChessMove cm)
{
	ASSERT(isSquare(FromSquare(cm)));
	ASSERT(isSquare(ToSquare(cm)));
	ASSERT(isBoardOK(board));

	//Save pos for later undo
	//board->unmake[board->historyply].move = cm;
	//board->unmake[board->historyply].castlingprivileges = board->castlingprivileges;
	//board->unmake[board->historyply].enpassantsquare = board->enpassantsquare;
	//board->unmake[board->historyply].fiftymoverule = board->fiftymoverule;
	//board->unmake[board->historyply].positionkey = board->positionkey;


	if (Capture(cm)){
		Clear(board, ToSquare(cm));
		//PrintBoard(board);
		
		//board->fiftymoverule = 0;
		}
		
	MovePiece(board, FromSquare(cm), ToSquare(cm));


	board->ply++;
	board->historyply++;
	board->sideToMove = Opponent();

}