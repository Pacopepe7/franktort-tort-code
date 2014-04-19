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
	
	/*************************************
	* Fast evaluate
	*/
	result = materialCount[ctm] - materialCount[opp];
	result += psqtCount[ctm] - psqtCount[opp];
	/*************************************************************
	* Adjust for endgame king PSQT
	*************************************************************/
	if ( (materialCount[ctm] + materialCount[opp]) < (8500 / 3) )
	{
		
		result -= PSQT_K[getOx88to64Index(ctm, state[ply].king[ctm])];
		result -= PSQT_K[getOx88to64Index(opp, state[ply].king[opp])];
		result += PSQT_KEG[getOx88to64Index(ctm, state[ply].king[ctm])];
		result += PSQT_KEG[getOx88to64Index(opp, state[ply].king[opp])];
	}

	/*********************************************************
	* Piece Pairs Bonuses
	*********************************************************/
	if ( numBishops[ctm] == 2 ) result +=  BISHOPPAIR;
	if ( numBishops[opp] == 2 ) result -=  BISHOPPAIR;

	if ( numKnights[ctm] == 2 ) result +=  KNIGHTPAIR;
	if ( numKnights[opp] == 2 ) result -=  KNIGHTPAIR;

	if ( numRooks[ctm] == 2 ) result +=  ROOKPAIR;
	if ( numRooks[opp] == 2 ) result -=  ROOKPAIR;

	/**********************************************************
	* Return draw score (0) if material is not sufficient
	**********************************************************/
	if ( numPawns[ctm] == 0 && materialCount[ctm] < 400 && result > 0 ) //one minor piece
		return 0;
	if ( numPawns[ctm] == 0 && materialCount[ctm] > 700 && numKnights[ctm] && result > 0) // two bishops can mate, no numknights >0
		return 0;





	return ( result );
}
