/**********************************************
/*
  TheMaster, a UCI chess playing engine 
  Copyright (C)2014 Francisco Tort

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ChessGame.h"

/*********************************************************************************************
* evaluate()
* This is the function that lets the chess engine know how good the position is for the side to move
*/

int ChessBoard::Evaluate(  )
{
	int materialtomove = 0;
	int materialtarget = 0;
	int attackvaluetomove = 0;
	int attackvaluetarget = 0;
	int legalmoves = 0;
	int target = (sidetomove == WHITE) ? BLACK : WHITE;
	int targetkingposition;
	if (sidetomove == WHITE ) 
		targetkingposition = blackkingposition;
	else
		targetkingposition = whitekingposition;
	ChessMove cm;
	ChessBoard evalnode = *this;

	// make a draw check
	//if ( tm.drawcheck( evalnode ) ) 
	//	return 0;

	// check if there are valid moves on this position,
	//if not and in check, it's mate!
	// if not and not in check, its stalemate


	for (int x = 0; x < 144; x++)
	{
		if ( getColorAt(x) == sidetomove )
			materialtomove += currentposition[x].value;
		if ( getColorAt(x) == target )
			materialtarget += currentposition[x].value;
	}
	//
	for (int x = 0; x < 144; x++)
	{
		if ( !(currentposition[x] == OUT))
		{
			attackvaluetomove += IsAttacked( x, sidetomove );
			attackvaluetarget += IsAttacked( x, target );
		}
	}
	//return ( ( materialtomove + attackvaluetomove ) - (materialtarget + attackvaluetarget) );
	return ( ( materialtomove ) - (materialtarget) );
}
