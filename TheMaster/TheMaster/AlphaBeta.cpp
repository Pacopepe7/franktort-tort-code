/**********************************************
/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

/**************************************************************
* Alpha Beta
* 
*/
int ChessGame::AlphaBeta( int depth , int alpha, int beta) 
{

	if ( depth == 0 ) 
		return Evaluate(  );
	int legalmoves = 0;
	int movestomate = 0;
	int score, max;
	
	max = -INFINITY;

	ChessMove movebeingevaluated;
	mstack[state.ply].DumpStack();
	GenerateMoves();

	while ( ! mstack[state.ply].empty() )
	{
		movebeingevaluated =  mstack[state.ply].pop();

		if ( MakeMove( movebeingevaluated ) )
		{
			if ( isPositionValid())
			{
				if ( isCapture(movebeingevaluated))
				{
					
						score = -AlphaBeta(  depth, -beta, -alpha );
				}
				else
					score = -AlphaBeta(  depth - 1, -beta, -alpha);
				if ( score >= beta )
					reutrn beta;
				if ( score > alpha )
				{
					alpha = score;
					chessresult[state.ply-1].best = movebeingevaluated;
					chessresult[state.ply-1].value = score;
				}
			}
			UnmakeMove(movebeingevaluated);
		}
	}
	return alpha;
} 

