/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ChessGame.h"
//Fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
void ChessGame::Fen(string fen)
{
	vector<string> tokens;
	Tokenize(fen, tokens, " " );
	int index = 0;
	char col = 0;
	char row = 0;

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
		case '/': row++; col=0; break;
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

	if (tokens[1] == "w") {
		state[ply].ctm = WHITE;
		state[ply].opp = BLACK;
	} else {
		state[ply].ctm = BLACK;
		state[ply].opp = WHITE;
	}

	index = 0;
	do {
		switch( tokens[2][index] ) {
		case 'K': state[ply].castling[WHITE] |= SHORT; break;
		case 'Q': state[ply].castling[WHITE] |= LONG; break;
		case 'k': state[ply].castling[BLACK] |= SHORT; break;
		case 'q': state[ply].castling[BLACK] |= LONG; break;
		}
		index++;
	} while (index < tokens[2].length()  );

	//en passant quare
	if ( tokens[3] == "-" )
		state[ply].eppossible = false;
	else
	{
		state[ply].eppossible = true;
		state[ply].epsquare[0] = MakeSquare(tokens[4]);
	}

	// 50 move rule counter
	if ( tokens[4] == "-" )
		state[ply].fiftymoverule = 0;
	else
	{
		state[ply].fiftymoverule = MakeInt(tokens[5]);
	}
	//move number
	state[ply].move = MakeInt(tokens[5]);
}