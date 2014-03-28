/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ChessGame.h"
#include <iostream>

/**************************************************************
* PrintBoard ()
*/

void ChessGame::PrintBoard ( void ) 
{
	bool newrow = false;
	for ( int i = 0; i < 128; i++)
	{
		if ( ! isSquare(i) )
		{
			newrow = true;
			continue;
		}
		if ( newrow )
		{
			newrow = false; 
			cout << endl;
		}
		if ( Ox88Board[i].piece == EMPTY)
			cout << " ";
		switch ( Ox88Board[i].piece)
		{
		case PAWN:
			if (  Ox88Board[i].color == WHITE ) //White is 0
				cout << "P";
			if (  Ox88Board[i].color == BLACK )
				cout << "p";
			break;
		case KNIGHT:
			if (  ! Ox88Board[i].color ) //WHite is 0
				cout << "N";
			else
				cout << "n";
			break;
		case BISHOP:
			if (  ! Ox88Board[i].color ) //WHite is 0
				cout << "B";
			else
				cout << "b";
			break;
		case ROOK:
			if (  ! Ox88Board[i].color ) //WHite is 0
				cout << "R";
			else
				cout << "r";
			break;
		case QUEEN:
			if (  ! Ox88Board[i].color ) //WHite is 0
				cout << "Q";
			else
				cout << "q";
			break;		
		case KING:
			if (  ! Ox88Board[i].color ) //WHite is 0
				cout << "K";
			else
				cout << "k";
			break;
	
		}


	}
	cout << endl;

}

