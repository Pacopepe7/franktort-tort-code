/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ChessGame.h"
#include "zobrist.h"
#include <iostream>

using namespace std;


__int64 ChessGame::perft( int depth)
{
	if (depth == 0)
		return 1;
	__int64 legalmoves = 0;
	U64 moves;
	int currDepthMoves = 0;
	int testcount = 0;
	ChessMove movebeingevaluated;
	if ( depth == -1)
	{
		legalmoves = 0;
		return 0;
	}

	mstack[ply].DumpStack();
	/*
	If in check, generate only moves to get out of check.
	*/
	/*if (IsInCheck())
		GenerateOutOfCheckMoves();
	else*/
		GenerateMoves();

	while ( ! mstack[ply].empty()) 
	{
		movebeingevaluated = mstack[ply].pop().cm;

		if ( MakeMove( movebeingevaluated )  )
		{
			if ( isPositionValid(movebeingevaluated) ) 
			{
				//if ( getMoveType(state[ply].m_LastMove) == MT_CAPTURE){
					//PrintBoard();
					//PrintMove(movebeingevaluated);
				moves = perft( (int) depth - 1);
				currDepthMoves ++;
				legalmoves += moves;
				/*testcount += moves  ;
				if (depth == 6){
					PrintMove(movebeingevaluated);
					cout << ": " << testcount << endl;
					testcount = 0;
				}*/
			}

			UnmakeMove(movebeingevaluated);
		}


	}
	if ( ! currDepthMoves )
	{
		//there are no valid moves, mate?
		//PrintBoard();
	}
	//cout << "Perft : " << legalmoves << endl;
	return legalmoves;
} 