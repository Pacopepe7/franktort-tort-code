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
#include "Scores.h"
#include <iostream>

using namespace std;


int  ChessGame::kingvectors[8]		= { NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST };
int  ChessGame::knightvectors[8]	= {
	NORTH + NORTHWEST, NORTH + NORTHEAST, EAST + NORTHEAST, EAST + SOUTHEAST, 
	SOUTH + SOUTHEAST, SOUTH + SOUTHWEST,  WEST + SOUTHWEST, WEST + NORTHWEST,  };
int  ChessGame::bishopvectors[8]	= { NORTHEAST, SOUTHEAST,  SOUTHWEST, NORTHWEST, 0, 0, 0, 0};
int  ChessGame::rookvectors[8]		= { NORTH, SOUTH, EAST, WEST , 0, 0, 0, 0};
int  ChessGame::queenvectors[8]		= { NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST };
int ChessGame::Ox88to64[128] = {
	//63, 62, 61, 60, 59, 58, 57, 56, 0,0,0,0,0,0,0,0,//0-15
	//55, 54, 53, 52, 51, 50, 49, 48, 0,0,0,0,0,0,0,0,//16-
	//47, 46, 45, 44, 43, 42, 41, 40, 0,0,0,0,0,0,0,0,//32
	//39, 38, 37, 36, 35, 34, 33, 32, 0,0,0,0,0,0,0,0,//48
	//31, 30, 29, 28, 27, 26, 25, 24, 0,0,0,0,0,0,0,0,//64
	//23, 22, 21, 20, 19, 18, 17, 16, 0,0,0,0,0,0,0,0,//80
	//15, 14, 13, 12, 11, 10,  9,  8, 0,0,0,0,0,0,0,0,//96
	// 7,  6,  5,  4,  3,  2,  1,  0, 0,0,0,0,0,0,0,0};//112

	0, 1, 2, 3, 4, 5, 6, 7,				0,0,0,0,0,0,0,0,
	8, 9, 10, 11, 12, 13, 14, 15,		0,0,0,0,0,0,0,0,
	16, 17, 18, 19, 20, 21, 22, 23,		0,0,0,0,0,0,0,0,
	24, 25, 26, 27, 28, 29, 30, 31,		0,0,0,0,0,0,0,0,
	32, 33, 34, 35, 36, 37, 38, 39,		0,0,0,0,0,0,0,0,
	40, 41, 42, 43, 44, 45, 46, 47,		0,0,0,0,0,0,0,0,
	48, 49, 50, 51, 52, 53, 54, 55,		0,0,0,0,0,0,0,0,
	56, 57, 58, 59, 60, 61, 62,	63,		0,0,0,0,0,0,0,0};

int ChessGame::blackOx88to64[128] = {
	56, 57, 58, 59, 60, 61, 62,	63,		0,0,0,0,0,0,0,0,
	48, 49, 50, 51, 52, 53, 54, 55,		0,0,0,0,0,0,0,0,
	40, 41, 42, 43, 44, 45, 46, 47,		0,0,0,0,0,0,0,0,
	32, 33, 34, 35, 36, 37, 38, 39,		0,0,0,0,0,0,0,0,
	24, 25, 26, 27, 28, 29, 30, 31,		0,0,0,0,0,0,0,0,
	16, 17, 18, 19, 20, 21, 22, 23,		0,0,0,0,0,0,0,0,
	8, 9, 10, 11, 12, 13, 14, 15,		0,0,0,0,0,0,0,0,
	0, 1, 2, 3, 4, 5, 6, 7,				0,0,0,0,0,0,0,0};

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
	if( debug )
		cout << "Initializing ChessGame\n";
	Init();
	InitAttackTables();
	Fen(STARTPOS);
}
/**
* Init ()
* Sets the state of the internal chess engine to the starting position and resets all the flags
*/
void ChessGame::Init ( void ) 
{
	if( debug )
		cout << "Initializing ChessGame\n";
	maxpieces[WHITE] = maxpieces[BLACK] = materialCount[WHITE] = materialCount[BLACK] = 0;

	pawndirection[WHITE] = NORTH;
	pawndirection[BLACK] = SOUTH;

	pawnsecondrank[WHITE] = 6;
	pawnsecondrank[BLACK] = 1;

	pawn_EP_rank[WHITE] = 3;
	pawn_EP_rank[BLACK] = 4;

	pawn_promotion_rank[WHITE] = 1;
	pawn_promotion_rank[BLACK] = 6;

	ply = 0;
	
	ctm = WHITE;
	opp = BLACK;

	state[ply].king[WHITE] = state[ply].king[BLACK] = 0;
	state[ply].castling[WHITE] = state[ply].castling[BLACK] = NONE;

	searchmethod = ALPHABETA;

#ifdef _DEBUG
	debug = true;
	maxdepth = 4;
#else
	debug = false;
	maxdepth = 5; // 7 works best (6 has bad odd-even effect)
#endif
	for (int i = 0; i < 128; i++)
		Ox88Board[i] = NULL;
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
		state[ply].king[c] = s;
	//Update counter
	if ( ! found)
	maxpieces[c]++;
	//Update material counter
	if ( p & PAWN) materialCount[c] += PAWN_WEIGHT;
	if ( p & KNIGHT) materialCount[c] += KNIGHT_WEIGHT;
	if ( p & BISHOP) materialCount[c] += BISHOP_WEIGHT;
	if ( p & ROOK) materialCount[c] += ROOK_WEIGHT;
	if ( p & QUEEN) materialCount[c] += QUEEN_WEIGHT;
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

	ASSERT( isSquare(s) && "Not a Square");
	ASSERT( !isEmpty(s) && "Clear is not empty");
	//Update material counter
	Piece p = getPiece(s);
	Color c = getColor(s);
	if ( p & PAWN)	materialCount[c] -= PAWN_WEIGHT;
	if ( p & KNIGHT)materialCount[c] -= KNIGHT_WEIGHT;
	if ( p & BISHOP)materialCount[c] -= BISHOP_WEIGHT;
	if ( p & ROOK)	materialCount[c] -= ROOK_WEIGHT;
	if ( p & QUEEN)	materialCount[c] -= QUEEN_WEIGHT;

	/***************************/
	Ox88Board[s]->color = COLORS;
	Ox88Board[s]->index = 0;
	Ox88Board[s]->piece = EMPTY;
	Ox88Board[s]->square = 0;
	Ox88Board[s] = NULL;
	
}

bool ChessGame::MakeMoveFromString( string cm)
{
	//cout << "move to make = " << cm << endl;
	mstack[ply].DumpStack();
	GenerateMoves();
		ChessMove _cm;
	for ( int c = 0; c < mstack[ply].size(); c++)
	{
		_cm =  mstack[ply].inspect(c);
		string move = MakeAlgebraicMove(_cm);
		
		if (cm == move )
		{
			//cout << " Found match!" << cm << " == " << move << endl;
			MakeMove(_cm);//validate missing...
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
	Square data = getDataSquare(cm);
	MoveType mt = getMoveType(cm);

	ASSERT ( isSquare(from));
	ASSERT ( isSquare(to));

	chessmove = not(from);
	chessmove += not(to);
	//todo, promotion
	if (  mt == ( MT_PROMOTION | MT_CAPTURE))
	{
		if ( getPromotion(data)  == KNIGHT)
			chessmove += "n";
		if ( getPromotion(data)  == BISHOP)
			chessmove += "b";
		if ( getPromotion(data)  == ROOK)
			chessmove += "r";
		if ( getPromotion(data)  == QUEEN)
			chessmove += "q";
	}
	if ( isPromotion(cm))
	{
		if ( getPromotion(data)  == KNIGHT)
			chessmove += "n";
		if ( getDataSquare(cm)  == BISHOP)
			chessmove += "b";
		if ( getDataSquare(cm)  == ROOK)
			chessmove += "r";
		if ( getDataSquare(cm)  == QUEEN)
			chessmove += "q";
	}
	return chessmove;
}



