/**********************************************
/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ChessGame.h"
#include "Evaluate.h"

/**************************************************************
* Negamax readable
* http://chessprogramming.wikispaces.com/Negamax
int negaMax( int depth ) {
    if ( depth == 0 ) return evaluate();
    int max = -oo;
    for ( all moves)  {
        score = -negaMax( depth - 1 );
        if( score > max )
            max = score;
    }
    return max;
}
*/
int ChessGame::NegaMax( int depth ) 
{
	if ( depth == 0 ) 
		return Evaluate();
		//return QuietNegaMax(depth - 1);

	int score, max;
	if ( searchdata.maxdepth < ply)
		searchdata.maxdepth = ply + 1;

	max = -INFINITY;

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
				score = -NegaMax(  depth - 1);
				if ( score > max )
				{
					max = score;
					chessresult[ply-1].best = movebeingevaluated;
					chessresult[ply-1].value = score;
				}
			}
			UnmakeMove(movebeingevaluated);
		}
	}
	return max;
} 

int ChessGame::QuietNegaMax( int depth ) 
{
	int legalmoves = 0;
	int movestomate = 0;
	int score, max;
	if ( searchdata.maxdepth < ply)
		searchdata.maxdepth = ply + 1;
	max = -INFINITY;

	ChessMove movebeingevaluated;
	mstack[ply].DumpStack();
	GenerateMoves();

	while ( ! mstack[ply].empty() )
	{
		movebeingevaluated =  mstack[ply].pop();

		if ( MakeMove( movebeingevaluated ) )
		{
			searchdata.nodes++;
			if ( isCapture(movebeingevaluated) && isPositionValid())
			{
				searchdata.legalnodes++;
				searchdata.quietnodes++;
				score = -NegaMax(  depth - 1);

				if ( score >= max )
				{
					max = score;
					chessresult[ply-1].best = movebeingevaluated;
					chessresult[ply-1].value = score;
				}
			}
			UnmakeMove(movebeingevaluated);
		}
	}
	return max;
} 

