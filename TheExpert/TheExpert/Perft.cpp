#include "ChessPosition.h"
#include "ChessMove.h"

#include <iostream>
using namespace std;

U64 perft(ChessPosition * board, int depth)
{
	//cout << "Entering perft" << endl;
	ASSERT(board);
	ASSERT(isBoardOK(board));


	if (depth == 0)
		return 1;
	if (depth == -1)
		return 0;

	U64 legalmoves = 0;
	U64 moves;

	int currDepthMoves = 0;
	int testcount = 0;
	ChessMove move;

	MOVELIST list;
	list.index = -1;
	//PrintBoard(board);
	GenerateMoves(board, &list);
	ASSERT(MovesStillLeft(list));
	while (MovesStillLeft(list))
	{
		move = GetMoveFrom(list);
		//cout << "Making move: " << MakeMoveString(move) << endl;
		MakeMove(board, move);
		{
			
			//PrintBoard(board);
			//if (isPositionValid(movebeingevaluated))
			{
				moves = perft(board, (int)depth - 1);
				currDepthMoves++;
				legalmoves += moves;
			}
			//cout << "UnMaking move: " << MakeMoveString(move) << endl;
			UnMakeMove(board, move);
			//PrintBoard(board);
		}
	}
	return legalmoves;
}