/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Color.h"
#include "Piece.h"
#include "ChessMove.h"
#include "Square.h"

//#undef NDEBUG
#ifdef _DEBUG
#define ASSERT assert
#else
#define ASSERT /********/
#endif

#include "Definitions.h"
#include <string>
#include <iostream>
#include "utils.h"
#include <assert.h>
#include "fixedLengthStack.h"
#include <boost/timer/timer.hpp>
#include <boost/chrono/include.hpp>

using namespace boost;

typedef boost::chrono::duration<double> sec;

struct SearchResult
{
	ChessMove best;
	int value;
	bool onlymove;

};
enum SearchMethod { NEGAMAX, ALPHABETA, MTDF, CUSTOM};
struct Searchdata
{

	long long nodes;
	long long legalnodes;
	long long evaluates;
	long long regularnodes;
	long long quietnodes;
	int maxdepth;
};
/***********************************************
*
* Thanks http://chessprogramming.wikispaces.com/Bruce+Moreland
***********************************************/
typedef struct LINE {
    int cmove;              // Number of moves in the line.
    ChessMove argmove[50];  // The line.
}   LINE;
/************************************************/
struct Pieceinfo_t
{
	Piece piece;
	Color color;
	Square square;
	short index;
};

/************************************************/
struct boardstate_t {
	int castling[2];
	ChessMove m_LastMove;
	ChessMove currentMove;
	Square king[2];
	short move;
	Square epsquare;
	short fiftymoverule;
};

/************************************************
* OTHER TYPES
*/
typedef unsigned __int32	Mask;
typedef __int8				Direction;
typedef __int8				Rank;
typedef __int8				File;


/***********************************************
* Definitions
***********************************************/
#define FORWARD						 1
#define BACK						(-1)

#define TRUE	 1
#define FALSE	 0
#define INVALIDSQUARE				 64		

/************************************************
* MASKS
*/
#define MAXBOARDARRAY	128
#define INVALID			(-1)
#define MAXMOVES		250
#define ATTACKTABLEINDEXOFFSET	260
#define ATTACKTABLEMAX			(ATTACKTABLEINDEXOFFSET * 2)

/***********************************************/
#define NONE					0
#define SHORT					1
#define LONG					2
#define BOTH					3
/************************************************
* Macros
************************************************/
#define KingPos(side)			( state[ply].king[side])
#define isSquare(sq)			( (sq & 0x88)? false: true )
#define isEmpty(sq)				( Ox88Board[sq] == NULL) 
#define isColor( sq, c)			( Ox88Board[sq]->color == c)

#define isOpponent(sq)			( ( (isEmpty(sq) )? 0 : (Ox88Board[sq]->color == opp)))
#define isOurs(sq)				( ( (isEmpty(sq) )? 0 : (Ox88Board[sq]->color == ctm)))

#define IsInCheck( )			( isAttacked(KingPos(ctm), opp))

#define sameFile( sq1, sq2)		( ( getFile(sq1) == getFile(sq2))? 0:1 )
#define sameRank( sq1, sq2)		( ( getRank(sq1) == getRank(sq2))? 0:1 )
#define getRank(sq)				( ( sq >> 4) )
#define getFile(sq)				( ( sq & 7) )

#define MakeSquare(r, c)		( 16 * r + c)

/*********************************************
* Color related Macros
*********************************************/
#define ColorOnMove()			( ctm )
#define ColorNotOnMove()		( opp )
/*************************************************
* Getters
**************************************************/
#define getColor(sq)			( ( (Ox88Board[sq] == NULL )? NOCOLOR :(Ox88Board[sq]->color )))
#define getPiece(sq)			( ( (Ox88Board[sq] == NULL) ? EMPTY : Ox88Board[sq]->piece ))


#define STARTPOS "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"


class ChessGame 
{
public:
	/****************************************************
	* Move Gen and Attack helper offssets
	*****************************************************/
	static int  kingvectors[8]		;
	static int  knightvectors[8]	;
	static int  bishopvectors[8]	;
	static int  rookvectors[8]		;
	static int  queenvectors[8]		;

	short pawndirection[COLORS];
	short pawnsecondrank[COLORS];
	short pawnthirdrank[COLORS];
	short pawn_EP_rank[COLORS];
	short pawn_promotion_rank[COLORS];
	/*****************************************************
	* Piece Square Tables
	*****************************************************/
	static int PSQT_P[64];
	static int PSQT_N[64];
	static int PSQT_B[64];
	static int PSQT_R[64];
	static int PSQT_Q[64];
	static int PSQT_K[64];
	static int PSQT_KEG[64];
	/******************************************************
	* Has board info
	******************************************************/
	Pieceinfo_t * Ox88Board[MAXBOARDARRAY];
	Cstack <ChessMove> mstack[MAXMOVES];
	short ply;
	short depthply;
	Color ctm, opp;
	boardstate_t state[MAXMOVES];
	Pieceinfo_t pieces[MAXPIECES][COLORS];
	int materialCount[COLORS];
	int psqtCount[COLORS];
	short maxpieces[COLORS];
	int numKnights[COLORS];
	int numBishops[COLORS];
	int numRooks[COLORS];
	int numPawns[COLORS];
	/******************************************************
	* Helper for board info 
	*******************************************************/
	static int Ox88to64[128];
	static int blackOx88to64[128]; 
	static string  notation[MAXBOARDARRAY];	
	Piece Attacks0x88[ATTACKTABLEMAX];

	bool debug;
	int depth;
	int maxdepth;
	SearchMethod searchmethod;
	Searchdata searchdata;
	LINE pv;


public:
	/**************************************
	* Constructor */
	ChessGame ( ); 
	/**************************************
	* Initializers Functions
	*/
	void Init(void);
	void InitAttackTables(void);
	void Fen(string fen);

	/***************************************
	* Main Search Functions
	*/
	int Evaluate(void);
	int NegaMax(int depth);
	int QuietNegaMax(int depth);
	int AlphaBetaDriver();
	int AlphaBeta(int depth, int alpha, int beta, LINE *);
	int QuietAlphaBeta(int depth, int alpha, int beta);
	SearchResult chessresult[MAXMOVES]; // public

	/*****************************************
	* Move Functions
	******************************************/
	void GenerateMoves(void);
	void GenCaptures(void);
	void SortMoves(void);
	bool MakeMove(ChessMove cm);
	bool MakeMoveFromString( string cm);
	void UnmakeMove( ChessMove cm);
	ChessMove RetrieveOrderedMove(void);
	
	void Command(string c);
	/********************************************
	* Game Functions
	********************************************/
	void SwitchSides(int dir)		{ 
		opp = ctm;
		ctm = (ctm == WHITE)? BLACK:WHITE;
		ply += dir;
		depthply += dir;
		ASSERT((ply > -1) );
	};
	void Set(Piece p, Color c, Square s);
	void Set(Piece p, Color c, short r, short f);
	void CapturePiece( Square s1, Square s2);
	void Clear(Square s);
	void MovePiece( Square s1, Square s2);




	

	/******************************************
	* Check legality of move/position
	******************************************/
	bool isPositionValid(ChessMove cm);
	Piece PiecesThatCanAttack(/* From */ Square s1,/* to */ Square s2); 
	bool isAttackedbyPiece ( Square from, Square to, Color side, Piece p );
	/******************************************
	* ChessMove helper Funcs
	*****************************************/
	bool isPieceColor(Square sq, Piece p, Color c)	{ return ( !isSquare(sq)  ? (false) :
													(          (isEmpty(sq) ? (false): 
																((Ox88Board[sq]->piece & p) && (Ox88Board[sq]->color == c )))));};
	bool isAttacked(Square, Color c);

	int  getOx88to64Index(Color c, Square s)						{ 
		if ( s > 128)
			PrintBoard();
		ASSERT((s > -1) && "get64Index: Square is less than -1");
		ASSERT((s < 128) &&  "get64Index: Square is !< 128");
		if ( c ) // c = 1 == BLACK
			return ( 63 - Ox88to64[s]);
		else
			return ( Ox88to64[s]);
	};

	/*****************************************************************
	* Extensions
	*****************************************************************/
	bool isGoodCapture(ChessMove cm);
	bool PawnsAttackingLargePieces(ChessMove cm);


	ChessMove CM( Square from, Square to, MoveType mt, Square data)
	{ return ( ( from ) | ( to << 8) | ( mt << 16) | (data << 24) ) ; }
	void PrintMove(ChessMove cm);
	void PrintMovePlain(ChessMove cm);
	string not(Square sq);
	string MakeAlgebraicMove( ChessMove cm);
	Square MakeSquareFromString(string s)						{ 
		string sq;
		short r = s[0] - 65;
		short c = s[1] - 48;
		return MakeSquare(r, c);
	};
	void PrintPV(int length){
		for ( int c = ply; c < length; c++)
			cout << " " << MakeAlgebraicMove(chessresult[c].best);
	}
	void PrintLine(void){
		for ( int c = 1; c < ply; c++)
			cout << " " << MakeAlgebraicMove(state[c].m_LastMove);
	}
	
	/****************************************
	* Testing funcs
	****************************************/
	void ClearSearchData(void);
	void PrintSearchData( sec);

	void PrintBoard(void);
	void PrintDebugMove(ChessMove cm);
	__int64 perft(int depth);

}; // end class "ChessGame"
