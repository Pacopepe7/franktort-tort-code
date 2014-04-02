/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Definitions.h"
#include <string>
#include "utils.h"
#include <assert.h>
#include "fixedLengthStack.h"

struct SearchResult
{
	ChessMove best;
	int value;
};
struct Searchdata
{
	long long nodes;
	long long legalnodes;
	long long evaluates;
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
struct castling_t { 
	bool whiteshort;
	bool whitelong;
	bool blackshort;
	bool blacklong;
};
/************************************************/
struct boardstate_t {
	castling_t castling;
	ChessMove m_LastMove;
	int ctm;
	Square king[2];
	short ply;
	short move;
	Square epsquare[100];
	bool eppossible;
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

	static string  notation[MAXBOARDARRAY]		;
	Cstack <ChessMove> mstack[MAXMOVES];
	Pieceinfo_t pieces[MAXPIECES][COLORS];
	short maxpieces[2];
	boardstate_t state;
	Piece Attacks0x88[ATTACKTABLEMAX];
	Pieceinfo_t * Ox88Board[MAXBOARDARRAY];
	short pawndirection[COLORS];
	short pawnsecondrank[COLORS];
	short pawn_EP_rank[COLORS];
	Searchdata searchdata;
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
	* Main Functions
	*/
	int Evaluate(void);
	int NegaMax(int depth);
	SearchResult chessresult[MAXMOVES]; // public
	/*****************************************
	* Move Functions
	*/
	void GenerateMoves(void);
	//bool ValidateMove( string move);
	bool MakeMove(ChessMove cm);
	bool MakeMoveFromString( string cm);
	void UnmakeMove( ChessMove cm);

	
	void Command(string c);
	void SwitchSides(void)		{ 
		state.ctm = ColorNotOnMove();
	};
	short ColorOnMove(void)		{ return state.ctm;};
	short ColorNotOnMove(void)	{ return state.ctm == WHITE? BLACK:WHITE;};

	void Set(Piece p, Color c, Square s);
	void Set(Piece p, Color c, short r, short f);
	void MovePiece( Square s1, Square s2);
	void CapturePiece( Square s1, Square s2);
	void Clear(Square s);

	/****************************************
	* Check legality of move/position
	*/
	bool isPositionValid(void);
	bool isPositionValidOld(void);
	Piece PiecesThatCanAttack(/* From */ Square s1,/* to */ Square s2); 
	bool isAttackedbyPiece ( Square from, Square to, Color side, Piece p );
	/****************************************
	* ChessMove helper Funcs
	*/
	bool isSquare(Square sq)						{ return ( (sq & 0x88))? 0:1; } ;
	bool isEmpty(Square sq)							{ return ( Ox88Board[sq] == NULL);};

	bool isOpponent(Square sq)						{ return (  (isEmpty(sq) )? 0 : (Ox88Board[sq]->color == ColorNotOnMove()));};
	Piece ExtractPieceCaptured( ChessMove cm)		{ return ( ( cm >> 30) & BYTE) ; } ;

	Rank getRank(Square s)							{ return ( s >> 4) ; } ;
	File getFile(Square s)							{ return ( s & 7) ; } ;
	int  get64Index(Square s)						{ 
		if ( s > 128)
			PrintBoard();
		ASSERT(s > -1);
		ASSERT(s < 128);
		return ( Ox88to64[s]);
	};

	bool sameFile( Square sq1, Square sq2)			{ return ( getFile(sq1) == getFile(sq2))? 0:1; } ;
	bool sameRank( Square sq1, Square sq2)			{ return ( getRank(sq1) == getRank(sq2))? 0:1; } ;

	Square getFromSquare(ChessMove cm)				{ return (cm & BYTE) ; } ;
	Square getToSquare(ChessMove cm)				{ return ( ( cm >> 8) & BYTE) ; } ;
	Square getMoveType(ChessMove cm)				{ return ( ( cm >> 16) & BYTE) ; } ;
	Square getDataSquare(ChessMove cm)				{ return ( ( cm >> 24) & BYTE) ; } ;
	bool isCapture(ChessMove cm)					{ return ( getMoveType(cm) == MT_CAPTURE);};
	Piece getPiece(Square sq)						{ return (  (Ox88Board[sq] == NULL)?1 : Ox88Board[sq]->piece );};
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

	/****************************************
	* Testing funcs
	****************************************/
	void PrintBoard(void);
	void PrintDebugMove(ChessMove cm);
	__int64 perft(int depth);

}; // end class "ChessGame"
