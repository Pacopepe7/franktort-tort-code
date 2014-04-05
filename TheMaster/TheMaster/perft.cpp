/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ChessGame.h"
#include <iostream>

using namespace std;


__int64 ChessGame::perft( int depth)
{
	__int64 legalmoves = 0;
	int moves;
	int currDepthMoves = 0;
	ChessMove movebeingevaluated;
	if ( depth == -1)
	{
		legalmoves = 0;
		return 0;
	}
	if ( depth == 0 ) 
		return 1;
	mstack[ply].DumpStack();

	GenerateMoves();

	while ( ! mstack[ply].empty()) 
	{
		movebeingevaluated = mstack[ply].pop();

		if ( MakeMove( movebeingevaluated )  )
		{
			if ( isPositionValid() ) 
			{
				//if ( getMoveType(state[ply].m_LastMove) == MT_CAPTURE){
					//PrintBoard();
					//PrintMove(movebeingevaluated);
				moves = perft(  depth - 1);
				currDepthMoves ++;
				legalmoves += moves;
			}
			UnmakeMove(movebeingevaluated);
		}
	}
	if ( ! currDepthMoves )
	{
		//there are no valid moves, mate?
		//PrintBoard();
	}
	return legalmoves;
} 