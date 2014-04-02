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
	int ctm = state.ctm;
	int opp = ColorNotOnMove();
	searchdata.evaluates++;
	Square sq, oppsq;
	/*************************************
	* Fast evaluate
	*/
	for ( int c = 0; c < maxpieces[ctm]; c++)
	{
		sq = pieces[c][ctm].square;
		if ( ctm != WHITE )
			sq = blackOx88to64[sq];
		switch (pieces[c][ctm].piece){
		case PAWN:			
			result += PAWN_WEIGHT;	
			result += PSQT_WP[get64Index(sq)];	
			break;
		case KNIGHT:		result += KNIGHT_WEIGHT;result += PSQT_N[get64Index(sq)];	break;
		case BISHOP:		result += BISHOP_WEIGHT;result += PSQT_B[get64Index(sq)];	break;
		case ROOK:			result += ROOK_WEIGHT;  result += PSQT_R[get64Index(sq)];	break;
		case QUEEN:			result += QUEEN_WEIGHT;	result += PSQT_Q[get64Index(sq)];	break;
		}
		oppsq = pieces[c][ctm].square;
		if ( ctm != WHITE )
			sq = blackOx88to64[sq];
		switch (pieces[c][opp].piece){
		case PAWN:			
			result -= PAWN_WEIGHT;	
			result -= PSQT_WP[get64Index(sq)];	
			break;
		case KNIGHT:		result -= KNIGHT_WEIGHT;result -= PSQT_N[get64Index(sq)];	break;
		case BISHOP:		result -= BISHOP_WEIGHT;result -= PSQT_B[get64Index(sq)];	break;
		case ROOK:			result -= ROOK_WEIGHT;  result -= PSQT_R[get64Index(sq)];	break;
		case QUEEN:			result -= QUEEN_WEIGHT;	result -= PSQT_Q[get64Index(sq)];	break;
		}

	}
	return ( result );
}
