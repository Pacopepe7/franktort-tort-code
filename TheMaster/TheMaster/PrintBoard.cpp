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
	cout << "----------------------" << endl;
	if ( ctm ) cout << "   BLACK to move   " << endl;
	else cout << "   WHITE to move   " << endl;
	cout << "White king at : " << not(state[ply].king[WHITE]) << endl;
	cout << "Black king at : " << not(state[ply].king[BLACK]) << endl;

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
		if ( Ox88Board[i] == NULL)
		{
			cout << " ";
			continue;
		}
		switch ( Ox88Board[i]->piece)
		{
		case PAWN:
			if (  Ox88Board[i]->color == WHITE ) //White is 0
				cout << "P";
			if (  Ox88Board[i]->color == BLACK )
				cout << "p";
			break;
		case KNIGHT:
			if (  ! Ox88Board[i]->color ) //WHite is 0
				cout << "N";
			else
				cout << "n";
			break;
		case BISHOP:
			if (  ! Ox88Board[i]->color ) //WHite is 0
				cout << "B";
			else
				cout << "b";
			break;
		case ROOK:
			if (  ! Ox88Board[i]->color ) //WHite is 0
				cout << "R";
			else
				cout << "r";
			break;
		case QUEEN:
			if (  ! Ox88Board[i]->color ) //WHite is 0
				cout << "Q";
			else
				cout << "q";
			break;		
		case KING:
			if (  ! Ox88Board[i]->color ) //WHite is 0
				cout << "K";
			else
				cout << "k";
			break;
		}
	}
	cout << endl;

	//print, to move pieces...
	/*for ( int c = 0; c < maxpieces[ state.ctm]; c++)
		cout << "c: " << c << ", P: " << (int)pieces[c][state.ctm].piece << " I: " <<  (int)pieces[c][state.ctm].square << endl;
	for ( int c = 0; c < maxpieces[ ColorNotOnMove()]; c++)
		cout << "c: " << c << ", P: " << (int)pieces[c][ColorNotOnMove()].piece << " I: " <<  (int)pieces[c][ColorNotOnMove()].square << endl;
	Square from = getFromSquare(state.m_LastMove);
	Square to = getToSquare(state.m_LastMove);
	Square data =  getDataSquare(state.m_LastMove);
	MoveType mt = getMoveType(state.m_LastMove);
	cout << (int) state.m_LastMove << "f: " << (int)from << " t: " << (int)to << " data: " << (int)data << " MT: " << (int) mt << endl;*/

}
void  ChessGame::PrintDebugMove(ChessMove cm)
{
	Square from = getFromSquare(cm);
	Square to = getToSquare(cm);
	Square data =  getDataSquare(cm);
	MoveType mt = getMoveType(cm);
	cout << "DEBUG:" << (int) cm << "f: " << (int)from << " t: " << (int)to << " data: " << (int)data << " MT: " << (int) mt << endl;
}
