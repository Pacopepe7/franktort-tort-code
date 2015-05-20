#include "ChessPosition.h"
#include "utils.h"

string MakeMoveString(ChessMove cm)
{
	ASSERT(isSquare(FromSquare(cm)));
	ASSERT(isSquare(ToSquare(cm)));
	//ASSERT(FromSquare(cm) != ToSquare(cm));
	string prom = "";
	if (Promotion(cm)){
		if (Promotion(cm) == (QUEEN>> 3)) prom = "q";
		if (Promotion(cm) == (ROOK >> 3)) prom = "r";
		if (Promotion(cm) == (BISHOP >> 3)) prom = "b";
		if (Promotion(cm) == (KNIGHT >> 3)) prom = "n";

	}
	string move = notation[FromSquare(cm)];
	move = move + notation[ToSquare(cm)];

	return move + prom;
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
		cout << MakeMoveString(cm) << endl;
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
	//cout << "Making " << MakeMoveString(cm) << endl;
	//Save pos for later undo
	board->unmake[board->historyply].move = cm;
	board->unmake[board->historyply].castlingprivileges = board->castlingprivileges;
	board->unmake[board->historyply].enpassantsquare = board->enpassantsquare;
	board->unmake[board->historyply].fiftymoverule = board->fiftymoverule;
	board->unmake[board->historyply].positionkey = board->positionkey;
	board->unmake[board->historyply].psqt[WHITE] = board->PSQT[WHITE];
	board->unmake[board->historyply].psqt[BLACK] = board->PSQT[BLACK];

	if (EPCapture(cm)){
		Clear(board, ToSquare(cm) - pawndirection[SideToMove()]);
	}
	else 
	if (Capture(cm)){
		ASSERT(CountBits(Capture(cm)) == 1);
		Clear(board, ToSquare(cm));
		}

	if (Castle(cm))
	{
		if (ToSquare(cm) == G1)		{
			Clear(board, H1);
			SetPiece(board, (ROOK) | SideToMove(), F1);
		}
		if (ToSquare(cm) == C1)		{
			Clear(board, A1);
			SetPiece(board, (ROOK) | SideToMove(), D1);
		}
		if (ToSquare(cm) == G8)		{
			Clear(board, H8);
			SetPiece(board, (ROOK) | SideToMove(), F8);
		}
		if (ToSquare(cm) == C8)		{
			Clear(board, A8);
			SetPiece(board, (ROOK) | SideToMove(), D8);
		}

	}
	if (Promotion(cm))
	{
		ASSERT(CountBits(Promotion(cm)) == 1);
		ASSERT(Promotion(cm) & ((QUEEN | BISHOP | ROOK | KNIGHT) >> 3));
		Clear(board, FromSquare(cm));
		SetPiece(board, (Promotion(cm) << 3) | SideToMove(), ToSquare(cm));
		/*PrintBoard(board);
		getchar();*/
	}
	else
		MovePiece(board, FromSquare(cm), ToSquare(cm));

	if (EPPossible(cm)){
		board->enpassantsquare = ToSquare(cm) - pawndirection[SideToMove()];
		HASH_EP(board->enpassantsquare, SideToMove());
	}
	else
		board->enpassantsquare = INVALID;

	board->castlingprivileges = board->castlingprivileges & castling[ToSquare(cm)];
	board->castlingprivileges = board->castlingprivileges & castling[FromSquare(cm)];
	HASH_CASTLE();

	board->ply++;
	board->historyply++;
	board->sideToMove = Opponent();
	ASSERT(isBoardOK(board));
	//if (ColorOnMove() == WHITE)
	HASH_SIDE();
	HASH_MOVENUM();
}