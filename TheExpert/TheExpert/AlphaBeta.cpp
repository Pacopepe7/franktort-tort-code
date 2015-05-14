
#include <boost/timer/timer.hpp>
#include <boost/chrono/include.hpp>

#include "ChessPosition.h"
#include "ChessMove.h"
#include "Eval.h"
#include <iostream>
using namespace std;



using namespace boost;

typedef boost::timer::auto_cpu_timer btimer;
typedef boost::chrono::duration<double> sec;

#define MAXABDEPTH		20

void AlphaBetaDriver(ChessPosition * board)
{
	int value;
	int alpha = -INF;
	int beta = INF;
	int window = 150;
	int maxdepth = 8;
	int depth = 1;
	
	int nodes = 0;
	LINE pv;
	sec 	seconds;
	boost::timer::cpu_timer timer;
	do {
		nodes = 0;

		//cout << "info alpha " << alpha << " beta " << beta << " window " << window;
		value = AlphaBeta(board, alpha, beta, depth, &pv, &nodes);
		cout << "info nodes " << nodes;
		seconds = boost::chrono::nanoseconds(timer.elapsed().user);
		cout << " time " << seconds.count();

		std::cout.precision(3);
		if (seconds.count())
			cout << " nps " << (int)(nodes / seconds.count());
		else
			cout << " nps " << (nodes);
		std::cout.unsetf(std::ios::floatfield);

		cout << " score cp " << value;
		cout << " depth " << depth << " pv ";
		for (int c = 0; c < pv.cmove; c++)
			cout << MakeMoveString(pv.argmove[c]) << " ";
		cout << endl;
		if ((value == MATE) || (value == -MATE))
			break;

		if ((value <= alpha) || (value >= beta))
		{
			if (value <= alpha)
				alpha = -INF;
			if ((value >= beta))
				beta = INF;
		}
		else
		{
			depth ++;
			alpha = value - window;
			beta = value + window;
		}
			

	} while (/*(depth != maxdepth) &&*/  (seconds.count() < 5));
	cout << "bestmove " << MakeMoveString(pv.argmove[0]) << endl;
	return;

}
/**************************************************************
* Alpha Beta
*
*/
int AlphaBeta(ChessPosition * board, int alpha, int beta, int depth, LINE * pline, int *nodes)
{
	int score;
	int hashf = hashfALPHA;
	bool extended = false;
	int legalmoves = 0;
	int movestomate = 0;


	if ((score = ProbeHash(board->positionkey, MAXABDEPTH - depth, alpha, beta)) != -1)
		return score;
	LINE line;
	ChessMove move;
	MOVELIST list;
	line.cmove = 0;
	/***************************************************
	* Extensions
	***************************************************/
	if (IsInCheck())
		depth++;

	if (depth == 0)
	{
		
		pline->cmove = 0;
		score = QuietAlphaBeta(board, alpha, beta);
		//score = Eval(board);
		RecordHash(board->positionkey, MAXABDEPTH - depth, score, hashfEXACT);
		return score;
	}
	if (board->fiftymoverule >= 50)
		return 0;
	GenerateMoves(board, &list);
	OrderPV(&list, &line, depth);

	while (MovesStillLeft(list))	{
		ASSERT(list.index != -1);
		move = RemoveMoveFromList(&list);
		ASSERT(move);
		MakeMove(board, move);
		if (isValid())	{
			score = -AlphaBeta(board, -beta, -alpha, depth - 1, &line, nodes);
			legalmoves++;
			(*nodes)++;
			if (score >= beta)				{
				RecordHash(board->positionkey, MAXABDEPTH - depth, beta, hashfBETA);
				UnMakeMove(board, move);
				return beta;
			}
			if (score > alpha)		
			{
				hashf = hashfEXACT;
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
			return -MATE;
		else
			return 0;
	}
	RecordHash(board->positionkey, MAXABDEPTH - depth,  alpha, hashf);
	return alpha;
}





int QuietAlphaBeta(ChessPosition * board, int alpha, int beta)
{
	if (board->fiftymoverule >= 50)
		return 0;
	int score = Eval(board);

	if (score >= beta)
		return beta;
	if (score > alpha)
		alpha = score;

	int legalmoves = 0;
	int movestomate = 0;
	int captures = 0;
	
	ChessMove move;
	MOVELIST list;
	//SearchResult firstValidMove;
	GenerateMoves(board, &list, false);
		
	while (MovesStillLeft(list))
	{
		ASSERT(list.index != -1);
		move = RemoveMoveFromList(&list);
		ASSERT(move);
		MakeMove(board, move);
		if (isValid()){
			score = -QuietAlphaBeta(board, -beta, -alpha);
			legalmoves++;

			if (score >= beta){
				UnMakeMove(board, move);
				return beta;
			}
			if (score > alpha){
				alpha = score;
			}
		}
		UnMakeMove(board, move);
	}
	//PrintBoard();
	if (!legalmoves)	
	{		
		if (IsInCheck())
			return -MATE;
		else
			return 0;
	}

	return alpha;
}

