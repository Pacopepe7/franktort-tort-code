/**********************************************
/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort}
http://chessprogramming.wikispaces.com/Alpha-Beta
*/
#include "ChessGame.h"
#include "Evaluate.h"
#include <iostream>

/**************************************************************
* Alpha Beta
* 
*/
int ChessGame::AlphaBetaDriver()
{
	int value, alpha, beta;
	sec seconds;
	bool timeleft = true;
	depth = -1;
	alpha = -INFINITY;
	beta = INFINITY;
	int window = 100;
	do {
		depth += 2;
		ClearSearchData();
		boost::timer::cpu_timer timer;
		cout << "info alpha " << alpha << " beta " << beta << " window " << window << endl;
		value = AlphaBeta( depth, alpha, beta);
		seconds = boost::chrono::nanoseconds(timer.elapsed().user);
		PrintSearchData(seconds);		ClearSearchData();

		if ( abs(value) == MATE)
			break;

		if ((value <= alpha) || (value >= beta)) {
			if ( (value <= alpha) )
				alpha = -INFINITY;
			if (  (value >= beta))
				beta = INFINITY;
			cout << "info Researching!" << endl;
			depth -= 2;
		}else{
			alpha = value - window;
			beta = value + window;
		}
		/*if ( depth == 5 && seconds.count() > 0.4)
			timeleft = false;
		if ( depth == 7 && seconds.count() > 0.30)
			timeleft = false;
		if ( seconds.count() > 2)
			timeleft = false;*/
	}while (seconds.count() < 2);
	
	return value;

}
/**************************************************************
* Alpha Beta
* 
*/
int ChessGame::AlphaBeta( int depth , int alpha, int beta) 
{
	if ( state[ply].fiftymoverule >= 50 )
		return 0;
	/* if ( 3 move repetition)
	return 0; */

	if ( IsInCheck() )
		depth ++;

	if ( depth == 0) 
		return QuietAlphaBeta( depth - 1, alpha, beta );



	int legalmoves = 0;
	int movestomate = 0;
	int score;

	if ( searchdata.maxdepth < ply + 1)
		searchdata.maxdepth = ply + 1;

	ChessMove movebeingevaluated;

	mstack[ply].DumpStack();
	GenerateMoves();



	while ( ! mstack[ply].empty() )	{
		movebeingevaluated =  mstack[ply].pop();
		if ( MakeMove( movebeingevaluated ) ){
			
			if ( isPositionValid(movebeingevaluated))	{
				searchdata.nodes++;
				legalmoves++;
				searchdata.legalnodes++;
				searchdata.regularnodes++;

				score = -AlphaBeta(  depth - 1, -beta, -alpha);

				if ( score >= beta )				{
					UnmakeMove(movebeingevaluated);
					return beta;				
				}
				if ( score > alpha )				{
					alpha = score;
					chessresult[ply-1].best = movebeingevaluated;
					chessresult[ply-1].value = score;				
				}
			}
			UnmakeMove(movebeingevaluated);
		}
	}
	//PrintBoard();
	if (! legalmoves )	{
		ASSERT(ctm != opp);
		//if in check, return mate, else (stalemate) return 0;
		if ( IsInCheck())
			alpha = -MATE;
		else
			alpha = 0;
	}
	/*if ( legalmoves == 1 )
		depth ++;*/
	return alpha;
} 

int ChessGame::QuietAlphaBeta( int depth , int alpha, int beta) 
{
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

	/*if ( ply  % 30 == 0) 
	{
		cout << "info ply = " << ply << endl;
		PrintBoard();
		for (int c = 1; c < ply; c++)
			PrintMovePlain(state[c].m_LastMove);
	}*/
	ChessMove movebeingevaluated;
	mstack[ply].DumpStack();
	GenerateMoves();

	while ( ! mstack[ply].empty() )
	{
		movebeingevaluated =  mstack[ply].pop();
		if ( MakeMove( movebeingevaluated ) )
		{
			if ( isPositionValid(movebeingevaluated))
			{
				legalmoves++;
				searchdata.legalnodes++;
				
				if ( isGoodCapture(movebeingevaluated)  )
				{
					searchdata.quietnodes++;
					searchdata.nodes++;
					captures ++;
					score = -QuietAlphaBeta(  depth - 1, -beta, -alpha);

					if ( score >= beta )
					{
						UnmakeMove(movebeingevaluated);
						return beta;
					}
					if ( score > alpha )
					{
						alpha = score;
						chessresult[ply-1].best = movebeingevaluated;
						chessresult[ply-1].value = score;
					}
				}
			}
			UnmakeMove(movebeingevaluated);
		}
	}
	//PrintBoard();
	if (! legalmoves )	{
		ASSERT(ctm != opp);
		//if in check, return mate, else (stalemate) return 0;
		if ( IsInCheck())
			alpha = -MATE;
		else
			alpha = 0;
	}

	return alpha;
} 

