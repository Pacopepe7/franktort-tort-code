/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "ChessBoard.h"
#include "utils.h"

ChessBoard::ChessBoard(void)
{
	for (int i = 0; i < 128; i++)
	{
		Ox88Board[i].color = NOCOLOR;
		Ox88Board[i].piece = EMPTY;
		Ox88Board[i].square = INVALIDSQUARE;
	}

}
string ChessBoard::getNotation( short r, short c) 
{
	char a = (char) (r+65);
	char b = (char) (c + 48);
	string str = "A1";
	str[0] = a;
	str[1] = b;
	return str;
}
void ChessBoard::Set(Piece p, Color c, Square s)
{
	Ox88Board[getIndex(s)].piece = p;
	Ox88Board[getIndex(s)].color = c;
}
void ChessBoard::Clear( Square s)
{
	Ox88Board[getIndex(s)].piece = EMPTY;
	Ox88Board[getIndex(s)].color = NOCOLOR;
}
int ChessBoard::getIndex(Square s)							
{ 
	return s + (s & ~7); 
} ;





