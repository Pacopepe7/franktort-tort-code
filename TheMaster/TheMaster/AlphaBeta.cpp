/**********************************************
/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

*/
/*int alphaBeta( int alpha, int beta, int depthleft ) {
if( depthleft == 0 ) return quiesce( alpha, beta );
for ( all moves)  {
score = -alphaBeta( -beta, -alpha, depthleft - 1 );
if( score >= beta )
return beta;   //  fail hard beta-cutoff
if( score > alpha )
alpha = score; // alpha acts like max in MiniMax
}
return alpha;
}
http://chessprogramming.wikispaces.com/Alpha-Beta
*/
#include "ChessGame.h"
#include "Evaluate.h"
#include <iostream>

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

	if ( depth < 1 && !IsInCheck() ) 
		return QuietAlphaBeta( depth - 1, alpha, beta );



	int legalmoves = 0;
	int movestomate = 0;
	int score;

	if ( searchdata.maxdepth < ply + 1)
		searchdata.maxdepth = ply + 1;


	ChessMove movebeingevaluated;

	mstack[ply].DumpStack();
	GenerateMoves();

	/*if ( mstack[ply].size() < 20 )
	depth ++;*/

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
				
				if ( isCapture(movebeingevaluated)  )
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

