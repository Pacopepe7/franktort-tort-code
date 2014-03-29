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

int  ChessGame::kingvectors[8]		= { NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST };
int  ChessGame::knightvectors[8]	= {
	NORTH + NORTHWEST, NORTH + NORTHEAST, EAST + NORTHEAST, EAST + SOUTHEAST, 
	SOUTH + SOUTHEAST, SOUTH + SOUTHWEST,  WEST + SOUTHWEST, WEST + NORTHWEST,  };
int  ChessGame::bishopvectors[8]	= { NORTHEAST, SOUTHEAST,  SOUTHWEST, NORTHWEST, 0, 0, 0, 0};
int  ChessGame::rookvectors[8]		= { NORTH, SOUTH, EAST, WEST , 0, 0, 0, 0};
int  ChessGame::queenvectors[8]		= { NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST };

string ChessGame::notation[128]		= {
	"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "X",  "X", "X", "X", "X", "X", "X", "X",
	"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "X",  "X", "X", "X", "X", "X", "X", "X",
	"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "X",  "X", "X", "X", "X", "X", "X", "X",
	"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "X",  "X", "X", "X", "X", "X", "X", "X",
	"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "X",  "X", "X", "X", "X", "X", "X", "X",
	"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", "X",  "X", "X", "X", "X", "X", "X", "X",
	"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "X",  "X", "X", "X", "X", "X", "X", "X",
	"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "X",  "X", "X", "X", "X", "X", "X", "X"};
	
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
	pawndirection[WHITE] = NORTH;
	pawndirection[BLACK] = SOUTH;
	pawnsecondrank[WHITE] = RANK2;
	pawnsecondrank[BLACK] = RANK7;
	state.ply = 0;
	state.king[WHITE] = 0;
	state.king[BLACK] = 0;

	for (int i = 0; i < 128; i++)
	{
		Ox88Board[i].color = NOCOLOR;
		Ox88Board[i].index = 0;
		Ox88Board[i].piece = EMPTY;
		Ox88Board[i].square = 0;
	}
	Fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	InitTables();
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
	short pieceindex;
	bool found = false;
	
	for (  pieceindex = 0; pieceindex < MAXPIECES && pieceindex < maxpieces[c]; pieceindex++)
		if ( pieces[pieceindex][c].piece == EMPTY )
		{
			found = true;
			break;
		}
	pieces[pieceindex][c].piece  = p;
	pieces[pieceindex][c].square = s;
	pieces[pieceindex][c].color = c;
	
	Ox88Board[s].color = c;
	Ox88Board[s].piece = p;
	Ox88Board[s].square = s;
	Ox88Board[s].index = pieceindex;
	//update king position
	if ( p & KING)
		state.king[c] = s;
	if ( ! found)
	maxpieces[c]++;
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
	short index;
	Color c;
	c = Ox88Board[from].color;
	index = Ox88Board[from].index;
	/*************************************/
	Ox88Board[to].piece = Ox88Board[from].piece;
	Ox88Board[to].color = c;
	Ox88Board[to].index = Ox88Board[from].index;
	Ox88Board[to].square = Ox88Board[from].square;
	//update king position
	if ( Ox88Board[to].piece & KING)
		state.king[c] = to;


	pieces[index][c].square = to;
	
	Ox88Board[from].piece = EMPTY;
	Ox88Board[from].color = NOCOLOR;
	Ox88Board[from].index = 0;
	Ox88Board[from].square = 0;
	
	
}
/***********************************************************
*
*/
void ChessGame::CapturePiece(Square from, Square to)
{
	Clear(to);
	MovePiece(from, to);
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
	short index= Ox88Board[s].index;
	Color c = Ox88Board[s].color;
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

bool ChessGame::ValidateMove( string move)
{
	return true;
}



bool ChessGame::MakeMove( string cm)
{

	return true;
}
bool ChessGame::MakeMove( Square from, Square to)
{

	return true;
}


