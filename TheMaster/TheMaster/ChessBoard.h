/**********************************************
/*
  TheMaster, a UCI chess playing engine 
  Copyright (C)2014 Francisco Tort

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Definitions.h"

#include <vector>
#include <stack>
#include <string>

#pragma once

/************************************************/
struct castling_t { 
	bool whiteshort;
	bool whitelong;
	bool blackshort;
	bool blacklong;
};
/************************************************/
struct boardstate_t {
	castling_t castling;
	ChessMove m_BestSoFar;
	ChessMove m_LastMove;
	bool m_bWhitetomove;
	short m_sWhitekingposition;
	short m_sBlackkingposition;
	short ply;
};

/************************************************/
class Cstack
{
private: 
	ChessMove chessmoves_arr[256];
	short chessmoveindex;
public:
	Cstack() 
	{ 
		chessmoveindex = 0;
	};
	ChessMove pop(void)			
	{ 
		if ( ! empty() )
			return chessmoves_arr[chessmoveindex--]; 
		return (0); 
	} ;
	void push(ChessMove cm)		
	{
		chessmoves_arr[++chessmoveindex] = cm; 
	} ;
	bool empty (void)				
	{ 
		if ( chessmoveindex < 0 )	
			return true;
		return false; 
	}	;
};
using namespace std;
/************************************************/
class ChessBoard 
{
public:
	boardstate_t m_boardState;
	Cstack m_movestack;

	static char *notation[144];
	static Piece startingposition[144];
	static unsigned int inttoboard[64];
	static unsigned int boardtoint[144];
	Piece currentposition[144];


	static int kingvectors[8];
	static int knightvectors[8];
	static int bishopvectors[8];
	static int rookvectors[8];
	static int queenvectors[8];


	inline Piece At(int x)	{ return currentposition[x ];};
	
	Piece getColor(Piece x)			{ return (At(x) & COLOR_MASK); } ;
	bool isPawn(Piece x)				{ return (At(x) & PAWN)> 1; } ;
	bool isKnight(Piece x)			{ return (At(x) & KNIGHT) > 1; } ;
	bool isBishop(Piece x)			{ return (At(x) & BISHOP) > 1; } ;
	bool isRook(Piece x)				{ return (At(x) & ROOK) > 1; } ;
	bool isQueen(Piece x)				{ return (At(x) & QUEEN)> 1; } ;
	bool isKing(Piece x)				{ return (At(x) & KING)> 1; } ;
	bool isWhite(Piece x)				{ return (At(x) & WHITE)==WHITE; } ;
	bool isBlack(Piece x)				{ return (At(x) & BLACK)==BLACK;};
	int Rank ( int x)				{ return (x / 12); } ;
	int Col(int x)					{ return (x % 12); } ;

	bool isEmpty(Piece x)				{ return (At(x) & EMPTY) > 1; } ;
	bool isOut(int x)				{ return (At(x) & OUT) > 1; } ;


	bool isEPPossible(ChessMove cm)	{ return (cm & MT_ENPASSANTPOSSIBLE) > 1;};
	bool isEP(ChessMove cm)			{ return (cm & MT_ENPASSANT) > 1; } ;
	bool isCaslte(ChessMove cm)		{ return (cm & MT_CASTLE) >1; } ;
	bool isPromotion(ChessMove cm)	{ return (cm & MT_PROMOTION)>1; } ;
	unsigned int TO(ChessMove cm)			{ return inttoboard[( (cm & TO_MASK) >> 6 ) ];};
	unsigned int FROM(ChessMove cm)			{ return inttoboard[( cm & FROM_MASK)];};


	ChessMove CHESSMOVE(int from, int to, int flags)	{ return ((boardtoint[from])|(boardtoint[to] << 6) | flags); } ;
	Piece getPieceAt( int x )					{ return currentposition[x] & PIECE_MASK; } ;
	Piece getColorAt( int x )					{ return currentposition[x] & COLOR_MASK; } ;
	
	int possibleMoves(Piece);
	bool isColor( int me,  int color)  { return  ((At(me) & COLOR_MASK) == color); } ;

public:
	//Functions
	ChessBoard(void);
	ChessBoard(string fen);
	//ChessBoard(string moves);

	void Init ( void );
	bool MakeMove ( unsigned int cm );
	void GenerateMoves ( void );

	int IsAttacked ( int sq, int side );
	
	int Evaluate( );
	int getIndex(char row, char column);

	string PrintBoard(void);
	
};