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
#include <iostream>

using namespace std;


int  ChessGame::kingvectors[8]		= { NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST };
int  ChessGame::knightvectors[8]	= {
	NORTH + NORTHWEST, NORTH + NORTHEAST, EAST + NORTHEAST, EAST + SOUTHEAST, 
	SOUTH + SOUTHEAST, SOUTH + SOUTHWEST,  WEST + SOUTHWEST, WEST + NORTHWEST,  };
int  ChessGame::bishopvectors[8]	= { NORTHEAST, SOUTHEAST,  SOUTHWEST, NORTHWEST, 0, 0, 0, 0};
int  ChessGame::rookvectors[8]		= { NORTH, SOUTH, EAST, WEST , 0, 0, 0, 0};
int  ChessGame::queenvectors[8]		= { NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST };

string ChessGame::notation[128]		= {
	"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "X",  "X", "X", "X", "X", "X", "X", "X",
	"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "X",  "X", "X", "X", "X", "X", "X", "X",
	"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", "X",  "X", "X", "X", "X", "X", "X", "X",
	"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "X",  "X", "X", "X", "X", "X", "X", "X",
	"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "X",  "X", "X", "X", "X", "X", "X", "X",
	"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "X",  "X", "X", "X", "X", "X", "X", "X",
	"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "X",  "X", "X", "X", "X", "X", "X", "X",
	"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "X",  "X", "X", "X", "X", "X", "X", "X"};
	
/**
* Chess Gane Constructor
*/
ChessGame::ChessGame ( ) 
{
	Init();
	InitAttackTables();

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

	pawnsecondrank[WHITE] = 6;
	pawnsecondrank[BLACK] = 1;

	pawn_EP_rank[WHITE] = 3;
	pawn_EP_rank[BLACK] = 4;

	state.ply = 0;
	state.ctm = WHITE;
	state.king[WHITE] = 0;
	state.king[BLACK] = 0;

	for (int i = 0; i < 128; i++)
		Ox88Board[i] = NULL;

	Fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}
/***************************************************
* Analogy: Imagine you are taking pieces out of a box and "set"ing them
* on a chess board.
*/
void ChessGame::Set(Piece p, Color c, Square s)
{
	ASSERT ( isSquare(s)) ;
	
	short pieceindex;
	bool found = false;
	
	for (  pieceindex = 0; pieceindex < MAXPIECES && pieceindex < maxpieces[c]; pieceindex++)
		if ( pieces[pieceindex][c].piece == EMPTY )
		{
			found = true;
			break;
		}
	Ox88Board[s] = &pieces[pieceindex][c];
	Ox88Board[s]->piece  = p;
	Ox88Board[s]->square = s;
	Ox88Board[s]->color = c;
	Ox88Board[s]->index = pieceindex;
	
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
	ASSERT ( isSquare(from)) ;
	ASSERT ( isSquare(to)) ;
	ASSERT ( !isEmpty(from));
	ASSERT ( isEmpty(to));
		
	Color c = Ox88Board[from]->color;
	int index = Ox88Board[from]->index;

	/*************************************/
	//update king position
	if ( Ox88Board[from]->piece & KING)
		state.king[c] = to;
	
	Ox88Board[from]->square = to;
	/*************************************/
		
	Ox88Board[to] = Ox88Board[from];
	Ox88Board[from] = NULL;
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

	ASSERT( isSquare(s));
	ASSERT( !isEmpty(s));
	
	/***************************/
	Ox88Board[s]->color = NOCOLOR;
	Ox88Board[s]->index = 0;
	Ox88Board[s]->piece = EMPTY;
	Ox88Board[s]->square = 0;
	Ox88Board[s] = NULL;
	
}





bool ChessGame::MakeMoveFromString( string cm)
{
	cout << "move = " << cm << endl;
	mstack[state.ply].DumpStack();
	GenerateMoves();
	cout << "Moves stack size = " << mstack[state.ply].size() << endl;
	int moves = mstack[state.ply].size();
	for ( int c = 0; c < moves; c++)
	{
		string movetemp;
		movetemp = MakeAlgebraicMove(mstack[state.ply].pop());
		cout << movetemp << endl;
	}
	GenerateMoves();
	moves = mstack[state.ply].size();
	cout << "Moves stack size = " << mstack[state.ply].size() << endl;
	ChessMove _cm;
	for ( int c = 0; c < moves; c++)
	{
		_cm =  mstack[state.ply].pop();
		string move = MakeAlgebraicMove(_cm);
		if (cm == move )
		{
			MakeMove(_cm);
			return true;
		}
	}
	return false;
}

string ChessGame::MakeAlgebraicMove( ChessMove cm)
{
	string chessmove = "";

	Square from = getFromSquare(cm);
	Square to = getToSquare(cm);
	ASSERT ( isSquare(from));
	ASSERT ( isSquare(to));

	chessmove = not(from);
	chessmove += not(to);
	//todo, promotion

	return chessmove;
}


