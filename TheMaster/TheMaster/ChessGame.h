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

	
	/*******************************************************
	* 
	*******************************************************/


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
	int AlphaBeta(int depth, int alpha, int beta);
	int QuietAlphaBeta(int depth, int alpha, int beta);
	SearchResult chessresult[MAXMOVES]; // public
	/*****************************************
	* Move Functions
	*/
	void GenerateMoves(void);
	bool MakeMove(ChessMove cm);
	bool MakeMoveFromString( string cm);
	void UnmakeMove( ChessMove cm);

	
	void Command(string c);
	/********************************************
	* Game Functions
	********************************************/
	void SwitchSides(int dir)		{ 
		opp = ctm;
		ctm = (ctm == WHITE)? BLACK:WHITE;
		ply += dir;
		ASSERT((ply > -1) );
	};
	void Set(Piece p, Color c, Square s);
	void Set(Piece p, Color c, short r, short f);
	void CapturePiece( Square s1, Square s2);
	void Clear(Square s);
	void MovePiece( Square s1, Square s2);


	/*********************************************
	* Color related Functions
	*********************************************/
	Color ColorOnMove(void)		{ return ctm;};
	Color ColorNotOnMove(void)	{ return opp;};

	

	/****************************************
	* Check legality of move/position
	*/
	bool isPositionValid(ChessMove cm);
	Piece PiecesThatCanAttack(/* From */ Square s1,/* to */ Square s2); 
	bool isAttackedbyPiece ( Square from, Square to, Color side, Piece p );
	/****************************************
	* ChessMove helper Funcs
	*/
	bool isSquare(Square sq)						{ return ( (sq & 0x88))? false: true; } ;
	bool isEmpty(Square sq)							{ return ( Ox88Board[sq] == NULL);};
	bool isColor(Square sq, Color c)				{ return ( (Ox88Board[sq]->color == c));}
	Color getColor(Square sq)						{ return ( (Ox88Board[sq] == NULL )? NOCOLOR :(Ox88Board[sq]->color ));}
	Piece getPiece(Square sq)						{ return ( (Ox88Board[sq] == NULL) ? EMPTY : Ox88Board[sq]->piece );};
	bool isPieceColor(Square sq, Piece p, Color c)	{ return ( !isSquare(sq)  ? (false) :
													(          (isEmpty(sq) ? (false): 
																((Ox88Board[sq]->piece & p) && (Ox88Board[sq]->color == c )))));};
	bool isAttacked(Square, Color c);
	bool IsInCheck( )								{ return isAttacked(state[ply].king[ctm], opp);};
	bool isOpponent(Square sq)						{ return (  (isEmpty(sq) )? 0 : (Ox88Board[sq]->color == opp));};
	bool isOurs ( Square sq)						{ return (  (isEmpty(sq) )? 0 : (Ox88Board[sq]->color == ctm));};

	Rank getRank(Square s)							{ return ( s >> 4) ; } ;
	File getFile(Square s)							{ return ( s & 7) ; } ;
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

	bool sameFile( Square sq1, Square sq2)			{ return ( getFile(sq1) == getFile(sq2))? 0:1; } ;
	bool sameRank( Square sq1, Square sq2)			{ return ( getRank(sq1) == getRank(sq2))? 0:1; } ;
	bool isGoodCapture(ChessMove cm);			
	bool PawnsAttackingLargePieces(void);
	ChessMove CM( Square from, Square to, MoveType mt, Square data)
	{ return ( ( from ) | ( to << 8) | ( mt << 16) | (data << 24) ) ; }
	void PrintMove(ChessMove cm);
	void PrintMovePlain(ChessMove cm);
	string not(Square sq);
	string MakeAlgebraicMove( ChessMove cm);
	Square MakeSquare(short r, short c)				{ return 16 * r + c;};
	Square MakeSquare(string s)						{ 
		string sq;
		short r = s[0] - 65;
		short c = s[1] - 48;
		return MakeSquare(r, c);
	};
	void PrintPV(int length){
		for ( int c = 0; c < length; c++)
			cout << " " << MakeAlgebraicMove(chessresult[c ].best) << " ";
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
