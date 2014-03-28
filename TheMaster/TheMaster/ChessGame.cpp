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
	pawndirection[WHITE] = NORTH;
	pawndirection[BLACK] = SOUTH;
	pawnsecondrank[WHITE] = RANK2;
	pawnsecondrank[BLACK] = RANK7;

	for (int i = 0; i < 64; i++)
	{
		Ox88Board[i].color = NOCOLOR;
		Ox88Board[i].index = 0;
		Ox88Board[i].piece = EMPTY;
		Ox88Board[i].square = 0;
	}
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
	pieces[pieceindex][c].color = c;
	
	Ox88Board[s].color = c;
	Ox88Board[s].piece = p;
	Ox88Board[s].square = s;
	Ox88Board[s].index = pieceindex;
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
	short index;
	Color c;
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

bool ChessGame::ValidateMove( string move)
{
	return true;
}



void ChessGame::MakeMove( string cm)
{


}
void ChessGame::MakeMove( Square from, Square to)
{


}


