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
	if ( depth < 0 ) 
		return Evaluate(  );

	int legalmoves = 0;
	int movestomate = 0;
	int value, best = -INFINITY;

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
				value = -NegaMax(  depth - 1);
			}
			UnmakeMove(movebeingevaluated);
			
				
			if ( value >= best )
			{
				best = value;
			}
		}
	}
	return best;
} 

