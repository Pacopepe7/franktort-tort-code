/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
/**********************************************
* ChessGame.cpp
* Class implementing a chess playing engine.
* Francisco Tort
* Dec 30, 2009
*
*/
#include "ChessGame.h"


int  ChessGame::kingvectors[8]		= { NORTH, SOUTH, EAST, WEST, NORTHEAST, NORTHWEST, SOUTHWEST, SOUTHEAST };
int  ChessGame::knightvectors[8]	= {
	NORTH + NORTHWEST, NORTH + NORTHEAST, SOUTH + SOUTHWEST, SOUTH + SOUTHEAST, 
	WEST + NORTHWEST, EAST + NORTHEAST, WEST + SOUTHWEST, EAST + SOUTHEAST
};
int  ChessGame::bishopvectors[8]	= { NORTHWEST,  NORTHEAST, SOUTHWEST, SOUTHEAST, 0, 0, 0, 0};
int  ChessGame::rookvectors[8]		= { NORTH, SOUTH, EAST, WEST , 0, 0, 0, 0};
int  ChessGame::queenvectors[8]		= { NORTH, SOUTH, EAST, WEST, NORTHEAST, NORTHWEST, SOUTHWEST, SOUTHEAST };

/**
* Chess Gane Constructor
*/
ChessGame::ChessGame ( ) 
{
	Init();
}
/**
* Init ()
* Sets the state of the internal chess engine to the starting position and resets all the flags
*/
void ChessGame::Init ( void ) 
{

	maxpieces[WHITE] = 0;
	maxpieces[BLACK] = 0;
	Fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}
/***************************************************
* Analogy: Imagine you are taking pieces out of a box and "set"ing them
* on a chess board.
*/
void ChessGame::Set(Piece p, Color c, Square s)
{
#ifdef _DEBUG
	if ( ! isSquare(s)) 
		return;
#endif
	short pieceindex = maxpieces[c];
	pieces[pieceindex][c].piece  = p;
	pieces[pieceindex][c].square = s;
	maxpieces[c]++;
	Ox88Board[s].color = c;
	Ox88Board[s].piece = p;
	Ox88Board[s].square = s;
}
/***********************************************************
*
*/
void ChessGame::MovePiece(Square from, Square to)
{
#ifdef _DEBUG
	if ( ! isSquare(from)) 
		return;
	if ( ! isSquare(to)) 
		return;
	if ( isEmpty(from))
		return;
	if ( ! isEmpty(to))
		return;
#endif
	static short index;
	static Color c;
	c = Ox88Board[from].color;
	index = Ox88Board[from].index;
	/*************************************/
	Ox88Board[to].piece = Ox88Board[from].piece;
	Ox88Board[to].color = c;
	Ox88Board[to].index = Ox88Board[from].index;
	Ox88Board[to].square = Ox88Board[from].square;

	pieces[index][c].square = to;
}
/***********************************************************
*
*/
void ChessGame::CapturePiece(Square from, Square to)
{

}
/***********************************************************
*
*/
void ChessGame::Set(Piece p, Color c, short r, short f)
{
	Set(p, c, MakeSquare(r, f));
}
/***********************************************************
* Removes Piece at Square and removes its piece data from array
*/
void ChessGame::Clear( Square s)
{
#ifdef _DEBUG
	if ( ! isSquare(s)) 
		return;
	if ( isEmpty(s))
		return;
#endif
	static short index;
	static Color c;
	c = Ox88Board[s].color;
	index = Ox88Board[s].index;
	/***************************/
	pieces[index][c].color = NOCOLOR;
	pieces[index][c].index = 0;
	pieces[index][c].piece = EMPTY;
	pieces[index][c].square = 0;

	Ox88Board[s].color = NOCOLOR;
	Ox88Board[s].index = 0;
	Ox88Board[s].piece = EMPTY;
	Ox88Board[s].square = 0;
}
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
bool ChessGame::ValidateMove( string move)
{
	return true;
}
void ChessGame::MakeMove(ChessMove cm)
{
	//assumes the move has been validated! (to do...)
	static int our, theirs; // reusable counters
	static Square from = getFromSquare(cm);
	static Square to = getToSquare(cm);
	static Square epsq =  getEPSquare(cm);
	static MoveType mt = getMoveType(cm);
	//static Piece q = getPromotingPiece(cm);
#ifdef _DEBUG
	if ( ! isSquare(from)) 
		return;
	if ( ! isSquare(to))
		return;
#endif
	//Ep moves
	if ( epsq == to)
	{


		return;
	}
	// no capture
	if ( isEmpty(to)) 
	{
		MovePiece(from, to);
		return;
	}
	//Capture
	{

		return;
	}

}

void ChessGame::UnmakeMove( ChessMove cm)
{
	static Square from = getFromSquare(cm);
	static Square to = getToSquare(cm);
	static Square epsq =  getEPSquare(cm);
	static MoveType mt = getMoveType(cm);

	MovePiece(to, from); // going backwards...

}
void ChessGame::MakeMove( string cm)
{


}
void ChessGame::MakeMove( Square from, Square to)
{


}
/********************************************
* Generates LEGAL moves for side to move
*/
void ChessGame::GenerateMoves( void )
{
	Color ctm = m_boardState.m_bWhitetomove? WHITE:BLACK;
	for ( short i = 0; i < maxpieces[ctm]; i++)
	{
		if ( pieces[i][ctm].piece == PAWN)
		{

		}



	}

}
__int64 ChessGame::perft( int depth)
{
	__int64 legalmoves = 0;
	ChessMove movebeingevaluated;
	if ( depth == -1)
	{
		legalmoves = 0;
		return 0;
	}
	if ( depth == 0 ) 
		return 1;
	while ( ! m_movestack.empty() )
		m_movestack.pop();
	
	GenerateMoves();

	while ( ! m_movestack.empty()) 
	{
		movebeingevaluated = m_movestack.pop();
		MakeMove( movebeingevaluated );
		legalmoves += perft(  depth - 1);
		UnmakeMove(movebeingevaluated);
	}
	return legalmoves;
} 

/**************************************************************
* PrintBoard ()
*/

void ChessGame::PrintBoard ( void ) 
{

}

