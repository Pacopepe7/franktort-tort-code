/**********************************************
* ChessBoard.h
* Class header for a chess board.
* Francisco Tort
* Dec 30, 2009
* ChessBoard holds all the information needed to represent a chess position
* including which side to move, castling options etc...
* 
*/
#include "Definitions.h"
#include "ChessPiece.h"
#include "ChessMove.h"
#include <vector>
#include <stack>

class ChessBoard 
{
public:
	static ChessMove nullmove;
	static char *notation[144];
	static ChessPiece startingposition[144];
	ChessPiece currentposition[144];
	ChessMove BestSoFar;
	ChessMove LastMove;
	stack <ChessMove> chessmoves;

	static int out[8] ;
	static int empty[8]; 
	static int whitepawn [8];
	static int knight [8];
	static int bishop [8];
	static int rook [8];
	static int queen [8];
	static int king [8];
	static int blackpawn [8];


	static ChessPiece OUT;
	static ChessPiece EMPTY;
	static ChessPiece WP;
	static ChessPiece WN;
	static ChessPiece WB;
	static ChessPiece WR;
	static ChessPiece WQ;
	static ChessPiece WK;
	static ChessPiece BP;
	static ChessPiece BN;
	static ChessPiece BB;
	static ChessPiece BR;
	static ChessPiece BQ;
	static ChessPiece BK;

	bool whitecancastlekingside;
	bool whitecancastlequeenside;
	bool blackcancastlekingside;
	bool blackcancastlequeenside;
	int sidetomove;
	int whitekingposition;
	int blackkingposition;
	int ply;

	//Functions
	ChessBoard(void);
	ChessBoard(string fen);
	ChessBoard operator= ( ChessBoard copy );
	void Init ( void );
	bool MakeMove ( ChessMove cm );
	void GenerateMoves ( void );
	int IsAttacked ( int sq, int side );
	string getDescription( int x );
	int Evaluate( );
	int getPieceAt( int x );
	int getColorAt( int x );
	int getIndex(string x);
	string PrintBoard(void);
};