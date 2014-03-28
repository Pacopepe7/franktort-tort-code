/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ChessGame.h"

void ChessGame::Fen(string fen)
{
	vector<string> tokens;
	Tokenize(fen, tokens, " " );
	int index = 0;
	char col = 0;
	char row = 7;

	do {
		switch(tokens[0][index] ) {
		case 'K': Set(KING, WHITE, row , col);	col++; break;
		case 'Q': Set(QUEEN, WHITE, row , col);	col++; break;
		case 'R': Set(ROOK, WHITE, row , col);	col++; break;
		case 'B': Set(BISHOP, WHITE, row , col);	col++; break;
		case 'N': Set(KNIGHT, WHITE, row , col);	col++; break;
		case 'P': Set(PAWN, WHITE, row , col);	col++; break;
		case 'k': Set(KING, BLACK, row , col);	col++; break;
		case 'q': Set(QUEEN, BLACK, row , col);	col++; break;
		case 'r': Set(ROOK, BLACK, row , col);	col++; break;
		case 'b': Set(BISHOP, BLACK, row , col);	col++; break;
		case 'n': Set(KNIGHT, BLACK, row , col);	col++; break;
		case 'p': Set(PAWN, BLACK, row , col);	col++; break;
		case '/': row--; col=0; break;
		case '1': col+=1; break;
		case '2': col+=2; break;
		case '3': col+=3; break;
		case '4': col+=4; break;
		case '5': col+=5; break;
		case '6': col+=6; break;
		case '7': col+=7; break;
		case '8': col+=8; break;
		};
		index++;
	} while ( index < tokens[0].length() );

	if (tokens[1] =="w") {
		m_boardState.m_bWhitetomove = TRUE;
	} else {
		m_boardState.m_bWhitetomove = FALSE;
	}

	index = 0;
	do {
		switch( tokens[2][index] ) {
		case 'K': m_boardState.castling.whiteshort = true; break;
		case 'Q': m_boardState.castling.whitelong = true; break;
		case 'k': m_boardState.castling.blackshort = true; break;
		case 'q': m_boardState.castling.blacklong = true; break;
		}
		index++;
	} while (index < tokens[2].length()  );

	//en passant quare
	if ( tokens[3] == "-" )
		state.eppossible = false;
	else
	{
		state.eppossible = true;
		state.epsquare = MakeSquare(tokens[4]);
	}

	// 50 move rule counter
	if ( tokens[4] == "-" )
		state.fiftymoverule = 0;
	else
	{
		state.fiftymoverule = MakeInt(tokens[5]);
	}
	//move number
	state.move = MakeInt(tokens[5]);
}