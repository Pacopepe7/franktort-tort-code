/**********************************************
/*
  TheMaster, a UCI chess playing engine 
  Copyright (C)2014 Francisco Tort

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Definitions.h"
#include "ChessPiece.h"
#include "ChessMove.h"
#include <vector>
#include <stack>
#pragma once

struct castling { bool whiteshort;
					bool whitelong;
					bool blackshort;
					bool blacklong;};

class ChessBoard 
{
public:
	static ChessMove nullmove;
	static char *notation[144];
	static ChessPiece startingposition[144];
	static unsigned int inttoboard[64];
	static unsigned int boardtoint[144];
	ChessPiece currentposition[144];
	ChessMove BestSoFar;
	unsigned int BestIntSoFar;
	int bestValueSoFar;
	
	unsigned int LastMoveInt;

	unsigned int chessmoves_arr[256];
	int chessmoveindex;

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

	castling Castlingpriviledges;
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
	bool MakeIntMove ( unsigned int cm );
	void GenerateMoves ( void );
	void GenerateIntMoves ( void );
	int IsAttacked ( int sq, int side );
	string getDescription( int x );
	int Evaluate( );
	int getPieceAt( int x );
	int getColorAt( int x );
	int getIndex(string x);
	string PrintBoard(void);
	
	unsigned int CMPOP(void);
	void CMPUSH(unsigned int);
	bool CMEMPTY (void);
};