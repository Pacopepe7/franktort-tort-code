#include "ChessPosition.h"
#include "ChessMove.h"
#include "Eval.h"
#include <iostream>
using namespace std;

void AlphaBetaDriver(ChessPosition * board)
{
	int value;
	int alpha = -INF;
	int beta = INF;
	int window = 100;
	int maxdepth = 8;
	int depth = 1;

	LINE pv;

do {
	cout << "info alpha " << alpha << " beta " << beta << " window " << window << endl;
	value = AlphaBeta(board, alpha, beta, depth, &pv);
	cout << "info pv ";
	for (int c = 0; c < pv.cmove; c++)
		cout << MakeMoveString(pv.argmove[c]) << " ";
	cout << endl;

	if (abs(value) == MATE)
		break;

	if ((value <= alpha) || (value >= beta)) {
		if ((value <= alpha))
			alpha = -INF;
		if ((value >= beta))
			beta = INF;
	}
	else{
		depth++;
		alpha = value - window;
		beta = value + window;
	}

} while (depth != maxdepth);

return ;

}
/**************************************************************
* Alpha Beta
*
*/
int AlphaBeta(ChessPosition * board, int alpha, int beta, int depth, LINE * pline)
{
	int score;
	int hashf = hashfALPHA;
	bool extended = false;
	int legalmoves = 0;
	int movestomate = 0;
	
	LINE line;
	ChessMove move;
	MOVELIST list;
	line.cmove = 0;
	/***************************************************
	* Extensions
	***************************************************/

	if (depth == 0)
	{
		pline->cmove = 0;
		//score = QuietAlphaBeta(depth - 1, alpha, beta);
		score = Eval();
		//RecordHash(tempzobrist, depth, score, hashfEXACT);
		return score;
	}
	if (board->fiftymoverule >= 50)
		return 0;
	GenerateMoves(board, &list);
	while (MovesStillLeft(list))	{
		move = GetMoveFrom(list);
		MakeMove(board, move);
		if (isValid())	{
			score = -AlphaBeta(board, -beta, -alpha, depth - 1, &line);
				legalmoves++;
				if (score >= beta)				{
					//RecordHash(tempzobrist, depth, beta, hashfBETA);
					UnMakeMove(board, move);
					return beta;
				}
				if (score > alpha)				{
					alpha = score;
					pline->argmove[0] = move;
					memcpy(pline->argmove + 1, line.argmove, line.cmove * sizeof(ChessMove));
					pline->cmove = line.cmove + 1;
					
				}
			}
		UnMakeMove(board, move);
		}

	if (!legalmoves)	
	{
		if (IsInCheck())
			alpha = -MATE;
	}
	else
		alpha = 0;
	//RecordHash(tempzobrist, depth, alpha, hashf);
	return alpha;
}





//int QuietAlphaBeta(int depth, int alpha, int beta)
//{
//	if (state[ply].fiftymoverule >= 50)
//		return 0;
//
//	int legalmoves = 0;
//	int movestomate = 0;
//	int captures = 0;
//	int score = Evaluate();
//
//	if (score >= beta)
//		return beta;
//	if (alpha < score)
//		alpha = score;
//
//	if (searchdata.maxdepth < ply + 1)
//		searchdata.maxdepth = ply + 1;
//
//	ChessMove movebeingevaluated;
//	//SearchResult firstValidMove;
//	mstack[ply].DumpStack();
//	GenCaptures();
//	SortMoves();
//
//	while (!mstack[ply].empty())
//	{
//		movebeingevaluated = mstack[ply].pop();
//		if (MakeMove(movebeingevaluated)){
//			if (isPositionValid()){
//				legalmoves++;
//				searchdata.legalnodes++;
//
//				if (isGoodCapture(movebeingevaluated)){
//
//					score = -QuietAlphaBeta(depth - 1, -beta, -alpha);
//					searchdata.quietnodes++;
//					searchdata.nodes++;
//					captures++;
//					if (score >= beta){
//						UnmakeMove(movebeingevaluated);
//						return beta;
//					}
//					if (score > alpha){
//						alpha = score;
//						chessresult[ply - 1].best = movebeingevaluated;
//						chessresult[ply - 1].value = score;
//						chessresult[ply - 1].onlymove = false;
//					}
//				}
//
//			}
//			UnmakeMove(movebeingevaluated);
//		}
//	}
//	//PrintBoard();
//	if (!legalmoves)	{//if in check, return mate, else (stalemate) return 0;		
//		if (IsInCheck())
//			alpha = -MATE;
//		else
//			alpha = 0;
//	}
//
//	return alpha;
//}
//
