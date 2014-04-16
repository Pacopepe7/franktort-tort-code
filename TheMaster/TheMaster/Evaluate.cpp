/**********************************************
/*
  TheMaster, a UCI chess playing engine 
  Copyright (C)2014 Francisco Tort

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ChessGame.h"
#include "Scores.h"

/*********************************************************************************************
* evaluate()
* This is the function that lets the chess engine know how good the position is for the side to move
*/

/********************************************************/


int ChessGame::Evaluate(void)
{
	int result = 0;
	searchdata.evaluates++;
	Square sq;
	

	/*************************************
	* Fast evaluate
	*/
	result = materialCount[ctm] - materialCount[opp];
	return ( result );
}
