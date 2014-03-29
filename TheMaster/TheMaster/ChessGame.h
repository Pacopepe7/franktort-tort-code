/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Definitions.h"
#include <string>
#include "utils.h"
#include "fixedLengthStack.h"

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
	ChessMove m_BestSoFar;
	int m_BestValueSoFar;
	ChessMove m_LastMove;
	bool ctm;
	Square king[2];
	short ply;
	short move;
	Square epsquare[100];
	bool eppossible;
	short fiftymoverule;

};

class ChessGame 
{
private:
	static int  kingvectors[8]		;
	static int  knightvectors[8]	;
	static int  bishopvectors[8]	;
	static int  rookvectors[8]		;
	static int  queenvectors[8]		;
	static string  notation[128]		;
	Cstack <ChessMove> mstack[250];
	Pieceinfo_t pieces[MAXPIECES][COLORS];
	short maxpieces[2];
	boardstate_t state;
	Piece Attacks0x88[260];
	Pieceinfo_t Ox88Board[128];
	short pawndirection[COLORS];
	short pawnsecondrank[COLORS];
	short pawn_EP_rank[COLORS];
public:
	/**************************************
	* Constructor */
	ChessGame ( ); 
	/**************************************
	* Game Functions
	*/
	void Init(void);
	void InitTables(void);

	void Fen(string fen);
	void GenerateMoves(void);
	bool ValidateMove( string move);
	bool MakeMove(ChessMove cm);
	bool MakeMove( string cm);
	bool MakeMove( Square from, Square to);
	void UnmakeMove( ChessMove cm);

	int  Evaluate(void);
	void Command(string c);
	void SwitchSides(void)		{ 
		if ( state.ctm == WHITE)
			state.ctm = BLACK;
		else
			state.ctm = WHITE;
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
	bool Attacks(Square s1, Square s2); 

	bool isAttacked ( Square sq, Color side );
	/****************************************
	* ChessMove helper Funcs
	*/
	bool isSquare(Square sq)						{ return (  sq & 0x88)? 0:1; } ;
	bool isEmpty(Square sq)							{ return ( Ox88Board[sq].piece == 0  );};

	bool isOpponent(Square sq)						{ return ( Ox88Board[sq].color == ColorNotOnMove());};
	Piece ExtractPieceCaptured( ChessMove cm)		{ return ( ( cm >> 30) & BYTE) ; } ;

	Rank getRank(Square s)							{ return ( s >> 4) ; } ;
	File getFile(Square s)							{ return ( s & 7) ; } ;

	bool sameFile( Square sq1, Square sq2)			{ return ( getFile(sq1) == getFile(sq2))? 0:1; } ;
	bool sameRank( Square sq1, Square sq2)			{ return ( getRank(sq1) == getRank(sq2))? 0:1; } ;

	Square getFromSquare(ChessMove cm)				{ return (cm & BYTE) ; } ;
	Square getToSquare(ChessMove cm)				{ return ( ( cm >> 8) & BYTE) ; } ;
	Square getMoveType(ChessMove cm)				{ return ( ( cm >> 16) & BYTE) ; } ;
	Square getDataSquare(ChessMove cm)				{ return ( ( cm >> 24) & BYTE) ; } ;
	Piece getPiece(Square sq)						{ return (  Ox88Board[sq].piece );};
	ChessMove CM( Square from, Square to, MoveType mt, Square data)
	{ return ( ( from ) | ( to << 8) | ( mt << 16) | (data << 24) ) ; }
	void PrintMove(ChessMove cm);
	string not(Square sq);
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
	__int64 perft(int depth);

}; // end class "ChessGame"
