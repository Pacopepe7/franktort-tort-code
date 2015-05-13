/**********************************************
/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort}
http://chessprogramming.wikispaces.com/Alpha-Beta
*/
#include "ChessGame.h"
#include "Evaluate.h"
#include <iostream>

#include "zobrist.h"


#define MAXEXTENSONSBYCHECK	3
#define MAXDEPTH			15
/**************************************************************
* Alpha Beta
* 
*/
int ChessGame::AlphaBetaDriver()
{
	int value, alpha, beta;

	sec seconds;
	pv.cmove = 0;
	depthply = 0;
	bool timeleft = true;
	bool researching = false;
	bool targetdepthreached = false;
	depth = 1;
	int depthdelta = 1;
	alpha = -INFINITY;
	beta = INFINITY;
	int window = 25;
	
	do {
		ClearSearchData();
		boost::timer::cpu_timer timer;
		cout << "info alpha " << alpha << " beta " << beta << " window " << window << endl;
		value = AlphaBeta( depth, alpha, beta, &pv);
		seconds = boost::chrono::nanoseconds(timer.elapsed().user);
		PrintSearchData(seconds);		ClearSearchData();

		if ( abs(value) == MATE)
			break;
		if ( chessresult[ply].onlymove )
			break;

		if ((value <= alpha) || (value >= beta)) {
			if ( (value <= alpha) )
				alpha = -INFINITY;
			if (  (value >= beta))
				beta = INFINITY;
			cout << "info Researching!" << endl;
			researching = true;
		}else{
			depth += depthdelta;
			alpha = value - window;
			beta = value + window;
			researching = false;
		}

		if ( depth > maxdepth && ! researching)
			targetdepthreached = true;
		if ( seconds.count() > 60 && researching)
			timeleft = false;
		if ( seconds.count() > 60 && ! researching)
			timeleft = false;
	}while (!targetdepthreached && timeleft );
	depth -= depthdelta;
	return value;

}
/**************************************************************
* Alpha Beta
* 
*/
int ChessGame::AlphaBeta( int depth , int alpha, int beta, LINE * pline) 
{
	int legalmoves = 0;
	int movestomate = 0;
	int score;
	LINE line;
	ChessMove movebeingevaluated;
	SearchResult firstValidMove;
	line.cmove = 0;

	/* if ( 3 move repetition)
	return 0; */

	/***************************************************
	* Extensions
	***************************************************/
	if (IsInCheck() && searchdata.maxdepth < MAXDEPTH)
		depth ++;

	/**************************************************
	*
	**************************************************/
	if ( depth == 0) 
	{
		pline->cmove = 0;
		return QuietAlphaBeta( depth - 1, alpha, beta );
	}
	if ( state[ply].fiftymoverule >= 50 )
	{
		return 0;
	}
	if ( searchdata.maxdepth < ply + 1)
		searchdata.maxdepth = ply + 1;

	mstack[ply].DumpStack();
	GenerateMoves();
	SortMoves();


	while ( ! mstack[ply].empty() )	{
		movebeingevaluated =  RetrieveOrderedMove();
		if ( MakeMove( movebeingevaluated ) ){

			if ( isPositionValid(movebeingevaluated))	{
				score = -AlphaBeta(  depth - 1, -beta, -alpha, &line);
				searchdata.nodes++;
				searchdata.legalnodes++;
				searchdata.regularnodes++;
				if ( ! legalmoves)
				{
					firstValidMove.best = movebeingevaluated;
					firstValidMove.value = score;
				}
				legalmoves++;
				if ( score >= beta )				{
					UnmakeMove(movebeingevaluated);
					return beta;				
				}
				if ( score > alpha )				{
					alpha = score;
					pline->argmove[0] = movebeingevaluated;
					memcpy(pline->argmove + 1, line.argmove, line.cmove * sizeof(ChessMove));
					pline->cmove = line.cmove + 1;
					chessresult[ply-1].best = movebeingevaluated;
					chessresult[ply-1].value = score;	
					chessresult[ply-1].onlymove = false;

				}
			}
			UnmakeMove(movebeingevaluated);
		}		
	}

//PrintBoard();
if (! legalmoves )	{//if in check, return mate, else (stalemate) return 0;		
	if ( IsInCheck())
		alpha = -MATE;
	else
		alpha = 0;
}
if ( legalmoves == 1 )
{
	chessresult[ply].best = firstValidMove.best;
	chessresult[ply].value = firstValidMove.value;
	chessresult[ply].onlymove = true;
	//depth++;//need to fix 3 move repetition before this..
}
return alpha;
} 

int ChessGame::QuietAlphaBeta( int depth , int alpha, int beta) 
{
	if ( state[ply].fiftymoverule >= 50 )
		return 0;

	int legalmoves = 0;
	int movestomate = 0;
	int captures = 0;
	int score = Evaluate();

	if ( score >= beta )
		return beta;
	if ( alpha < score )
		alpha = score;

	if ( searchdata.maxdepth < ply + 1)
		searchdata.maxdepth = ply + 1;

	ChessMove movebeingevaluated;
	//SearchResult firstValidMove;
	mstack[ply].DumpStack();
	GenCaptures();
	SortMoves();

	while ( ! mstack[ply].empty() )
	{
		movebeingevaluated =  mstack[ply].pop().cm;
		if ( MakeMove( movebeingevaluated ) ){
			if ( isPositionValid(movebeingevaluated)){
				legalmoves++;
				searchdata.legalnodes++;

				if ( isGoodCapture(movebeingevaluated)  ){

					score = -QuietAlphaBeta(  depth - 1, -beta, -alpha);
					searchdata.quietnodes++;
					searchdata.nodes++;
					captures ++;
					if ( score >= beta ){
						UnmakeMove(movebeingevaluated);
						return beta;
					}
					if ( score > alpha ){
						alpha = score;
						chessresult[ply-1].best = movebeingevaluated;
						chessresult[ply-1].value = score;
						chessresult[ply-1].onlymove = false;
					}
				}

			}
			UnmakeMove(movebeingevaluated);
		}
	}
	//PrintBoard();
	if (! legalmoves )	{//if in check, return mate, else (stalemate) return 0;		
		if ( IsInCheck())
			alpha = -MATE;
		else
			alpha = 0;
	}

	return alpha;
} 

