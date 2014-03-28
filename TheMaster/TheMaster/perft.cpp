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
	ChessMove movebeingevaluated;
	if ( depth == -1)
	{
		legalmoves = 0;
		return 0;
	}
	if ( depth == 0 ) 
		return 1;
	 mstack[state.ply].DumpStack();
	
	GenerateMoves();
	if ( depth == 1)
		return mstack[state.ply].size();
	while ( ! mstack[state.ply].empty()) 
	{
		movebeingevaluated = mstack[state.ply].pop();
		MakeMove( movebeingevaluated );
		
		moves = perft(  depth - 1);
		legalmoves += moves;
		UnmakeMove(movebeingevaluated);
	}
	return legalmoves;
} 