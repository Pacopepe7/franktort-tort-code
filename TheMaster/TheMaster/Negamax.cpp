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
* 
*/
int ChessGame::NegaMax( int depth ) 
{

	if ( depth == 0 ) 
		return Evaluate(  );
	int legalmoves = 0;
	int movestomate = 0;
	int score, max;
	if ( searchdata.maxdepth < state.ply)
		searchdata.maxdepth = state.ply + 1;
	max = -INFINITY;

	ChessMove movebeingevaluated;
	mstack[state.ply].DumpStack();
	GenerateMoves();

	while ( ! mstack[state.ply].empty() )
	{
		movebeingevaluated =  mstack[state.ply].pop();

		if ( MakeMove( movebeingevaluated ) )
		{
			searchdata.nodes++;
			if ( isPositionValid())
			{
				searchdata.legalnodes++;
				/*if ( isCapture(movebeingevaluated))
				{
						score = -NegaMax(  depth );
				}
				else*/
					score = -NegaMax(  depth - 1);
				if ( score >= max )
				{
					max = score;
					chessresult[state.ply-1].best = movebeingevaluated;
					chessresult[state.ply-1].value = score;
				}
			}
			UnmakeMove(movebeingevaluated);
		}
	}
	return max;
} 

