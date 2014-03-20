/**********************************************
/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Definitions.h"

#include "fixedLengthStack.h"


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
	int m_BestValueSoFar;
	ChessMove m_LastMove;
	bool m_bWhitetomove;
	short m_sWhitekingposition;
	short m_sBlackkingposition;
	short ply;
};


using namespace std;
/************************************************/
class ChessBoard 
{
public:
	// Static members, only one copy per class (vs one for instance)
	static char *notation[144];
	static Piece startingposition[144];
	static short inttoboard[64];
	static short boardtoint[144];
	static short insideboadonly[64];
	static int kingvectors[8];
	static int knightvectors[8];
	static int bishopvectors[8];
	static int rookvectors[8];
	static int queenvectors[8];

	boardstate_t m_boardState;
	Cstack <ChessMove> m_movestack;

	Piece currentposition[144];
	//static ChessBoard * position[30];



	

	Piece getColor(Piece x)				{ return (At(x) & COLOR_MASK); } ;
	Piece At(int x)						{ return ( currentposition[ x ]);};
	bool isPawn(Piece x)				{ return (At(x) & PAWN)> 0; } ;
	bool isKnight(Piece x)				{ return (At(x) & KNIGHT) > 0; } ;
	bool isBishop(Piece x)				{ return (At(x) & BISHOP) > 0; } ;
	bool isRook(Piece x)				{ return (At(x) & ROOK) > 0; } ;
	bool isQueen(Piece x)				{ return (At(x) & QUEEN)> 0; } ;
	bool isKing(Piece x)				{ return (At(x) & KING)> 0; } ;
	bool isWhite(Piece x)				{ return (At(x) & WHITE)==WHITE; } ;
	bool isBlack(Piece x)				{ return (At(x) & BLACK)==BLACK;};
	bool isEmpty(Piece x)				{ return (At(x)   == EMPTY);};
	int Rank ( int x)					{ return (x / 12); } ;
	int Col(int x)						{ return (x % 12); } ;

	//bool isEmpty(Piece x)				{ return (At(x) & EMPTY) > 0; } ;
	bool isOut(int x)					{ return (At(x) & OUT) > 1; } ;


	bool isEPPossible(ChessMove cm)		{ return (cm & MT_ENPASSANTPOSSIBLE) > 0;};
	bool isEP(ChessMove cm)				{ return (cm & MT_ENPASSANT) > 0; } ;
	bool isCaslte(ChessMove cm)			{ return (cm & MT_CASTLE) >0; } ;
	bool isCapture(ChessMove cm)		{ return (cm & MT_CAPTURE) > 0;};
	bool isPromotion(ChessMove cm)		{ return (cm & MT_PROMOTION)>0; } ;
	unsigned int TO(ChessMove cm)		{ return inttoboard[( (cm & TO_MASK) >> 6 ) ];};
	unsigned int FROM(ChessMove cm)		{ return inttoboard[( cm & FROM_MASK)];};
	string MakeString(ChessMove cm);


	ChessMove CHESSMOVE(int from, int to, int flags)	{ return ((boardtoint[from])|(boardtoint[to] << 6) | flags); } ;
	Piece getPieceAt( int x )			{ return currentposition[x] & PIECE_MASK; } ;
	Piece getColorAt( int x )			{ return currentposition[x] & COLOR_MASK; } ;

	int possibleMoves(Piece);
	bool isColor( int me,  int color)	{ return  ((At(me) & COLOR_MASK) == color); } ;

public:
	//Functions
	ChessBoard(void);
	ChessBoard(string fen);
	//ChessBoard(string moves);

	void Init ( void );
	bool MakeMove ( ChessMove cm );
	void GenerateMoves ( void );

	bool isAttacked ( int sq, int side );

	int Evaluate( );
	int getIndex(char row, char column);
	//Helpers
	string getNotation(int x)			{ return notation[x];};
	string PrintBoard(void);

};