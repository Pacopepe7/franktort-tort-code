#include "ChessPosition.h"
#include "ChessMove.h"

#include <iostream>
using namespace std;

U64 perft(ChessPosition * board, int depth)
{
	ASSERT(board);
	ASSERT(isBoardOK(board));
	bool foundontt = false;


	if (depth == 0)
		return 1;

	U64 legalmoves = 0;
	U64 moves;

	int currDepthMoves = 0;
	int captures = 0;
	int testcount = 0;
	ChessMove move;

	MOVELIST list;
	list.index = -1;

	GenerateMoves(board, &list);
	ASSERT(MovesStillLeft(list));
	while (MovesStillLeft(list))
	{
		move = GetMoveFrom(list);
		
		MakeMove(board, move, false);
		if (isValid())
		{
			moves = perft(board, (int)depth - 1);
			currDepthMoves++;
			legalmoves += moves;
		}
		UnMakeMove(board, move, false);
	}
	//RecordHashperft(board->positionkey, board->historyply, legalmoves);
	return legalmoves;
}