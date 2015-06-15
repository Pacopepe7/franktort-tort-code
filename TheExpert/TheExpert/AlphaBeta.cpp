
#include <boost/timer/timer.hpp>
#include <boost/chrono/include.hpp>

#include "ChessPosition.h"
#include "ChessMove.h"
#include "Eval.h"
#include <iostream>

#include "stdlib.h"
#include "stdio.h"
#include "windows.h"

using namespace std;

#define WINDOWSIZE		100
#define WINDOWSTEP		20
#define WINDOWMIN		20
#define MISSEDWINDOW	INF
#define MAXGAMEMOVES	256
#define TOTALCHECKEXTENSIONS	10

using namespace boost;

typedef boost::timer::auto_cpu_timer btimer;
typedef boost::chrono::duration<double> sec;

#define MAXABDEPTH		20



static void CheckUp(S_SEARCHINFO *info) {
	// .. check if time up, or interrupt from GUI
	if (info->timeset == TRUE && GetTickCount() > info->stoptime) {
		info->stopped = TRUE;
	}
}
static int IsRepetition(ChessPosition *pos) {

	int index = 0;

	for (index = pos->historyply - pos->fiftymoverule; index < pos->historyply - 1; ++index) {
		ASSERT(index >= 0 && index < MAXGAMEMOVES);
		ASSERT(index > -1);
		ASSERT(index < MAXGAMEMOVES);
		if (pos->positionkey == pos->unmake[index].positionkey) {
			return true;
		}
	}
	return false;
}
static void ClearForSearch(S_SEARCHINFO *info) {

	//int index = 0;
	//int index2 = 0;

	//for (index = 0; index < 13; ++index) {
	//	for (index2 = 0; index2 < BRD_SQ_NUM; ++index2) {
	//		//pos->searchHistory[index][index2] = 0;
	//	}
	//}

	//for (index = 0; index < 2; ++index) {
	//	for (index2 = 0; index2 < MAXDEPTH; ++index2) {
	//		pos->searchKillers[index][index2] = 0;
	//	}
	//}

	//pos->HashTable->overWrite = 0;
	//pos->HashTable->hit = 0;
	//pos->HashTable->cut = 0;
	//pos->ply = 0;
	info->totalcheckextensions = 0;
	info->seldepth = 0;
	info->onlymoveplyone = FALSE;
	//info->pv = false;
	//info->lastmoveforced = false;
	//info->lastmovecheck = false;
	info->stopped = 0;
	info->nodes = 0;
	info->fh = 0;
	info->fhf = 0;
}

void AlphaBetaDriver(ChessPosition * board, S_SEARCHINFO * info)
{
	int value;
	int alpha = -INF;
	int beta = INF;
	int window = WINDOWSIZE;
	int maxdepth = 8;
	int depth = 1;
	int starttime;
	int mseconds;

	LINE pv;
	sec 	seconds;
	boost::timer::cpu_timer timer;
	do {
		ClearForSearch(info);
		starttime = GetTickCount();
		cout << "info alpha " << alpha << " beta " << beta << " window " << window << endl;
		value = AlphaBeta(board, alpha, beta, depth, &pv, info, false);

		cout << "info nodes " << info->nodes;
		mseconds = GetTickCount() - starttime;
		cout << " time " << mseconds;

		std::cout.precision(3);
		if ((mseconds ))
			cout << " nps " << ((info->nodes / mseconds) * 1000 ) ;
		else
			cout << " nps " << (info->nodes);
		std::cout.unsetf(std::ios::floatfield);

		cout << " score cp " << value;
		cout << " pv ";
		for (int c = 0; c < pv.cmove; c++)
			cout << MakeMoveString(pv.argmove[c]) << " ";
		cout << " depth " << depth << " seldepth " << info->seldepth;
		cout << endl;
		///PrintZTStats();
		if ((value == MATE) || (value == -MATE))
			break;
		if (info->stopped == TRUE) 
			break;
		if (depth == 1 && info->onlymoveplyone == TRUE)
			break;
		if ((value <= alpha) || (value >= beta))
		{
			if ((value >= beta))
				beta = INF;
			if (value <= alpha)
				alpha = -INF;
			window = WINDOWSIZE;
		}
		else
		{
			depth ++;
			if (window > WINDOWMIN)
				window -= WINDOWSTEP;
			alpha = value - window;
			beta = value + window;
		}
			
	} while (depth <= info->depth);

	cout << "bestmove " << MakeMoveString(pv.argmove[0]) << endl;
	PrintBoard(board);
	return;

}
/**************************************************************
* Alpha Beta
*
*/
int AlphaBeta(ChessPosition * board, int alpha, int beta, int depth, LINE * pline, S_SEARCHINFO * info, bool DoNullMove)
{
	
	int score;
	int hashf = hashfALPHA;
	bool extended = false;
	int legalmoves = 0;
	int movestomate = 0;
	bool extension = false;

	if (depth <= 0)
	{
		pline->cmove = 0;
		score = QuietAlphaBeta(board, alpha, beta, info);
		//RecordHash(board->positionkey, depth, score, hashfEXACT);
		return score;
	}

	//if ((score = ProbeHash(board->positionkey, depth, alpha, beta)) != -1)
	//	return score;

	LINE line;
	ChessMove move;
	MOVELIST list;
	line.cmove = 0;
	bool incheck;
	/***************************************************
	* Extensions
	***************************************************/
	incheck = IsInCheck();
	ASSERT(info->totalcheckextensions <= TOTALCHECKEXTENSIONS);
	if (incheck && (info->totalcheckextensions < TOTALCHECKEXTENSIONS)){
		
		depth ++;
		info->totalcheckextensions ++;
		//info->lastmovecheck = true;
	}
	

	if ((info->nodes & 2048) == 0) {
		CheckUp(info);
	}
	if (IsRepetition(board) ) 
		return 0;
	if (( board->fiftymoverule >= 100) && board->ply ) {
		return 0;
	}

	/*if (DoNullMove && !incheck && board->historyply && depth >= 4 ){
		MakeNullMove(board);
		score = -AlphaBeta(board, -beta, -beta + 1, depth - 3, &line, info, false);
		UnMakeNullMove(board);
		if (score >= beta && abs(score) < MATE)
			return beta;
	}*/
	//info->lastmoveforced = false;

	GenerateMoves(board, &list);
	info->pv = OrderPV(&list, &line, depth);

	if (info->seldepth < board->ply + 1)
		info->seldepth ++;

	while (MovesStillLeft(list))	{
		ASSERT(list.index != -1);
		move = RemoveMoveFromList(&list);
		ASSERT(move);
		if (info->stopped == TRUE) {
			return alpha;
		}
		MakeMove(board, move, true);
		if (isValid())	{
			
			score = -AlphaBeta(board, -beta, -alpha, depth - 1, &line, info);
			
			//info->pv = false;
			legalmoves++;
			info->nodes++;			
		
			if (score >= beta)				{
				//RecordHash(board->positionkey, depth, beta, hashfBETA);
				UnMakeMove(board, move, false);
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
		UnMakeMove(board, move, false);
	}

	if (!legalmoves)
	{
		if (IsInCheck())
			return -MATE;
		else
			return 0;
	}
	if ( legalmoves == 1)
		info->onlymoveplyone = TRUE;
	//RecordHash(board->positionkey,  depth,  alpha, hashf);
	return alpha;
}


int QuietAlphaBeta(ChessPosition * board, int alpha, int beta, S_SEARCHINFO * info)
{
	int score;
	int hashf = hashfALPHA;
	ASSERT(info != NULL);
	//if ((score = ProbeHash(board->positionkey, 0, alpha, beta)) != -1)
	//	return score;

	if (IsRepetition(board) || board->fiftymoverule >= 100) {
		//RecordHash(board->positionkey, 0, 0, hashfEXACT);
		return 0;
	}

	score = Eval(board);

	if (score >= beta)
	{
		//RecordHash(board->positionkey, 0, beta, hashfEXACT);
		return beta;
	}
	if (score > alpha)
		alpha = score;

	int legalmoves = 0;
	int movestomate = 0;
	int captures = 0;
	
	ChessMove move;
	MOVELIST list;
	//SearchResult firstValidMove;
	//if (IsInCheck())
	//	GenerateMoves(board, &list, true);
	//else

	if (info->seldepth < board->ply + 1)
		info->seldepth++;

	GenerateMoves(board, &list, false);

	while (MovesStillLeft(list))
	{
		ASSERT(list.index != -1);
		move = RemoveMoveFromList(&list);
		ASSERT(move);
		MakeMove(board, move, true);
		if (isValid()){
			score = -QuietAlphaBeta(board, -beta, -alpha, info);
			legalmoves++;
			info->nodes++;
			if (score >= beta){
				UnMakeMove(board, move, false);
				//RecordHash(board->positionkey, 0, beta, hashfBETA);
				return score;
			}
			if (score > alpha){
				//hashf = hashfEXACT;
				alpha = score;
			}
		}
		UnMakeMove(board, move, false);
	}
	//if (!legalmoves)	
	//	alpha = Eval(board);
	//RecordHash(board->positionkey, 0, alpha, hashf);
	return alpha;
}

