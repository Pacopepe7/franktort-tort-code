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

	if ( depth < 1 ) 
		return QuietAlphaBeta( depth - 1, -beta, -alpha );
	int legalmoves = 0;
	int movestomate = 0;
	int score, max;
	if ( searchdata.maxdepth < ply)
		searchdata.maxdepth = ply + 1;

	ChessMove movebeingevaluated;
	mstack[ply].DumpStack();
	GenerateMoves();

	while ( ! mstack[ply].empty() )
	{
		movebeingevaluated =  mstack[ply].pop();
		if ( MakeMove( movebeingevaluated ) )
		{
			searchdata.nodes++;
			if ( isPositionValid())
			{
				searchdata.legalnodes++;
				searchdata.regularnodes++;
				score = -AlphaBeta(  depth - 1, -beta, -alpha);
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
			UnmakeMove(movebeingevaluated);
		}
	}
	return alpha;
} 

int ChessGame::QuietAlphaBeta( int depth , int alpha, int beta) 
{
	int legalmoves = 0;
	int movestomate = 0;
	int score, max;
	if ( searchdata.maxdepth < ply)
		searchdata.maxdepth = ply + 1;

	ChessMove movebeingevaluated;
	mstack[ply].DumpStack();
	GenerateMoves();

	while ( ! mstack[ply].empty() )
	{
		movebeingevaluated =  mstack[ply].pop();
		if ( MakeMove( movebeingevaluated ) )
		{
			searchdata.nodes++;
			if ( isPositionValid())
			{
				searchdata.legalnodes++;
				searchdata.quietnodes++;
				if ( isCapture(movebeingevaluated) )
					score = -AlphaBeta(  depth - 1, -beta, -alpha);
				else
					score = Evaluate();
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
			UnmakeMove(movebeingevaluated);
		}
	}
	return alpha;
} 

