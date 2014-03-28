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
	ChessMove movebeingevaluated;
	if ( depth == -1)
	{
		legalmoves = 0;
		return 0;
	}
	if ( depth == 0 ) 
		return 1;
	while ( ! mstack.empty() )
		mstack.pop();
	
	GenerateMoves();

	while ( ! mstack.empty()) 
	{
		movebeingevaluated = mstack.pop();
		MakeMove( movebeingevaluated );
		//cout << (int)getFromSquare(movebeingevaluated) << endl;
		PrintBoard();
		legalmoves += perft(  depth - 1);
		//cout << (int)getFromSquare(movebeingevaluated) << endl;
		UnmakeMove(movebeingevaluated);
	}
	return legalmoves;
} 