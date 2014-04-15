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
	static int  kingvectors[8]		;
	static int  knightvectors[8]	;
	static int  bishopvectors[8]	;
	static int  rookvectors[8]		;
	static int  queenvectors[8]		;

	static int PSQT_WP[64];
	static int PSQT_BP[64];

	static int PSQT_N[64];
	static int PSQT_B[64];
	static int PSQT_R[64];
	static int PSQT_Q[64];
	static int PSQT_K[64];
	static int Ox88to64[128];
	static int blackOx88to64[128];
	static string  notation[MAXBOARDARRAY];	
	Piece Attacks0x88[ATTACKTABLEMAX];
	Pieceinfo_t * Ox88Board[MAXBOARDARRAY];
	short pawndirection[COLORS];
	short pawnsecondrank[COLORS];
	short pawn_EP_rank[COLORS];
	short pawn_promotion_rank[COLORS];
	
	bool debug;
	int depth;
	int maxdepth;
	SearchMethod searchmethod;
	Searchdata searchdata;

	Cstack <ChessMove> mstack[MAXMOVES];

	Pieceinfo_t pieces[MAXPIECES][COLORS];
	short maxpieces[2];

	short ply;
	Color ctm, opp;
	boardstate_t state[300];

public:
	/**************************************
	* Constructor */
	ChessGame ( ); 
	/**************************************
	* Game Functions
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
	void SwitchSides(int dir)		{ 
		opp = ctm;
		ctm = (ctm == WHITE)? BLACK:WHITE;
		ply += dir;
		ASSERT((ply > -1) );
	};
	Color ColorOnMove(void)		{ return ctm;};
	Color ColorNotOnMove(void)	{ return opp;};

	void Set(Piece p, Color c, Square s);
	void Set(Piece p, Color c, short r, short f);
	void MovePiece( Square s1, Square s2);
	void CapturePiece( Square s1, Square s2);
	void Clear(Square s);

	/****************************************
	* Check legality of move/position
	*/
	bool isPositionValid(void);
	Piece PiecesThatCanAttack(/* From */ Square s1,/* to */ Square s2); 
	bool isAttackedbyPiece ( Square from, Square to, Color side, Piece p );
	/****************************************
	* ChessMove helper Funcs
	*/
	bool isSquare(Square sq)						{ return ( (sq & 0x88))? 0:1; } ;
	bool isEmpty(Square sq)							{ return ( Ox88Board[sq] == NULL);};
	bool isAttacked(Square, Color c);
	bool IsInCheck( )								{ return isAttacked(state[ply].king[ctm], opp);};
	bool isOpponent(Square sq)						{ return (  (isEmpty(sq) )? 0 : (Ox88Board[sq]->color == opp));};
	bool isOurs ( Square sq)						{ return (  (isEmpty(sq) )? 0 : (Ox88Board[sq]->color == ctm));};

	Rank getRank(Square s)							{ return ( s >> 4) ; } ;
	File getFile(Square s)							{ return ( s & 7) ; } ;
	int  get64Index(Square s)						{ 
		if ( s > 128)
			PrintBoard();
		ASSERT((s > -1) && "get64Index: Square is less than -1");
		ASSERT((s < 128) &&  "get64Index: Square is !< 128");
		return ( Ox88to64[s]);
	};

	bool sameFile( Square sq1, Square sq2)			{ return ( getFile(sq1) == getFile(sq2))? 0:1; } ;
	bool sameRank( Square sq1, Square sq2)			{ return ( getRank(sq1) == getRank(sq2))? 0:1; } ;
	bool isGoodCapture(ChessMove cm)				{ if ( isCapture(cm) && getPiece(getFromSquare(cm)) == PAWN) return true; return false;};
														/*if (  getPiece(getFromSquare(cm)) < getCapture(cm)) return true;
														return false;};*/
	Piece getPiece(Square sq)						{ return (  (Ox88Board[sq] == NULL)?EMPTY : Ox88Board[sq]->piece );};
	ChessMove CM( Square from, Square to, MoveType mt, Square data)
	{ return ( ( from ) | ( to << 8) | ( mt << 16) | (data << 24) ) ; }
	void PrintMove(ChessMove cm);
	string not(Square sq);
	string MakeAlgebraicMove( ChessMove cm);
	Square MakeSquare(short r, short c)				{ return 16 * r + c;};
	Square MakeSquare(string s)						{ 
		string sq;
		short r = s[0] - 65;
		short c = s[1] - 48;
		return MakeSquare(r, c);
	};
	void PrintPV(void){
		for ( int c = 0; c < ply; c++)
			cout << " " << MakeAlgebraicMove(chessresult[c ].best) << " ";
	}
	/****************************************
	* Testing funcs
	****************************************/
	void PrintBoard(void);
	void PrintDebugMove(ChessMove cm);
	__int64 perft(int depth);

}; // end class "ChessGame"
