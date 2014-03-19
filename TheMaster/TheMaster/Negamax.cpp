/**********************************************
/*
  TheMaster, a UCI chess playing engine 
  Copyright (C)2014 Francisco Tort

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ChessGame.h"
#include "ChessBoard.h"

/**************************************************************
* Negamax readable
* 
*/
int ChessGame::NegaMax( ChessBoard & currentBoard, int currentsearchdepth ) 
{
	if ( currentsearchdepth < 0 ) 
		return currentBoard.Evaluate(  );

	int legalmoves = 0;
	int movestomate = 0;
	int value;
	unsigned int movebeingevaluated;
	ChessBoard temp = currentBoard;
	ChessBoard moveGenBoard = currentBoard;

	moveGenBoard.GenerateMoves();
	

	while ( ! moveGenBoard.m_movestack.empty() )
	{
		movebeingevaluated =  moveGenBoard.m_movestack.pop();
		
		temp =  ChessBoard(currentBoard);
		if ( temp.MakeMove( movebeingevaluated ) )
		{
			legalmoves++;
			if ( temp.isCapture(temp.m_boardState.m_LastMove)  )
				value = -NegaMax( temp, currentsearchdepth);
			else
				value = -NegaMax( temp, currentsearchdepth - 1);
				
			if ( value >= currentBoard.m_boardState.m_BestValueSoFar )
			{
				currentBoard.m_boardState.m_BestValueSoFar = value;
				currentBoard.m_boardState.m_BestSoFar = movebeingevaluated;
			}
		}
	}
	return temp.m_boardState.m_BestValueSoFar;
} 

