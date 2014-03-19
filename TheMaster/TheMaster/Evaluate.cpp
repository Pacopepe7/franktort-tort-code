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

int ChessBoard::Evaluate(  )
{
	int value = 0, x;
	Piece p;
	int tomove = m_boardState.m_bWhitetomove? BLACK:WHITE;
	int opponent = m_boardState.m_bWhitetomove? WHITE:BLACK;

	int targetkingposition;

	if (m_boardState.m_bWhitetomove ) 
		targetkingposition = m_boardState.m_sBlackkingposition;
	else
		targetkingposition = m_boardState.m_sWhitekingposition;
	



	for (int i = 0; i < 64; i++)
	{
		x = At(insideboadonly[i]);
		p = x;

		if ( x & tomove )
		{
			if ( p & QUEEN /*isQueen(x)*/)
			{
				value += QUEEN_WEIGHT;
			}
			if ( p & ROOK/*isRook(x)*/)
				value += ROOK_WEIGHT;
			if ( p & BISHOP/*isBishop(x)*/)
				value += BISHOP_WEIGHT;
			if ( p & KNIGHT/*isKnight(x)*/)
				value += KNIGHT_WEIGHT;
			if ( p & PAWN/*isPawn(x)*/)
				value += PAWN_WEIGHT;
		}
		if ( x & opponent )
		{
			if ( p & QUEEN/*isQueen(x)*/)
				value -= QUEEN_WEIGHT;
			if ( p & ROOK/*isRook(x)*/)
				value -= ROOK_WEIGHT;
			if ( p & BISHOP/*isBishop(x)*/)
				value -= BISHOP_WEIGHT;
			if ( p & KNIGHT/*isKnight(x)*/)
				value -= KNIGHT_WEIGHT;
			if ( p & PAWN/*isPawn(x)*/)
				value -= PAWN_WEIGHT;
		}
		
	}
	

	return (value );
}
