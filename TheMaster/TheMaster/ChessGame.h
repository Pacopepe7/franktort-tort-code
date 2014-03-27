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
	bool m_bWhitetomove;
	short m_sWhitekingposition;
	short m_sBlackkingposition;
	short ply;
	short move;
	Square epsquare;
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
	boardstate_t m_boardState;
	Cstack <ChessMove> m_movestack;
	Pieceinfo_t pieces[MAXPIECES][COLORS];
	short maxpieces[2];
	boardstate_t state;
	Pieceinfo_t Ox88Board[128];
public:
	/**************************************
	* Constructor */
	ChessGame ( ); 
	/**************************************
	* Game Functions
	*/
	void Init(void);
	void Fen(string fen);
	void GenerateMoves(void);
	bool ValidateMove( string move);
	void MakeMove(ChessMove cm);
	void MakeMove( string cm);
	void MakeMove( Square from, Square to);
	void UnmakeMove( ChessMove cm);
	bool isPositionValid(void);
	int  Evaluate(void);
	void Command(string c);

	short ColorToMove(void)		{ return m_boardState.m_bWhitetomove? BLACK:WHITE;};
	short ColorNotToMove(void)	{ return m_boardState.m_bWhitetomove? WHITE:BLACK;};

	void Set(Piece p, Color c, Square s);
	void Set(Piece p, Color c, short r, short f);
	void MovePiece( Square s1, Square s2);
	void CapturePiece( Square s1, Square s2);
	void Clear(Square s);
	bool Attacks(Square s1, Square s2);
	/****************************************
	* ChessMove helper Funcs
	*/
	bool isSquare(Square sq)						{ return (( sq ) & 0x88)? 0:1; } ;
	bool isEmpty(Square sq)							{ return ( ! Ox88Board[sq].piece );};
	Piece ExtractPieceCaptured( ChessMove cm)		{ return ( ( cm >> 30) & BOTTOM6BITS) ; } ;
	Rank getRank(Square s)							{ return ( s >> 4) ; } ;
	File getFile(Square s)							{ return ( s & 7) ; } ;
	bool sameFile( Square sq1, Square sq2)			{ return ( getFile(sq1) == getFile(sq2))? 0:1; } ;
	bool sameRank( Square sq1, Square sq2)			{ return ( getRank(sq1) == getRank(sq2))? 0:1; } ;
	Square getFromSquare(ChessMove cm)				{ return (cm & BOTTOM6BITS) ; } ;
	Square getToSquare(ChessMove cm)				{ return ( ( cm >> 6) & BOTTOM6BITS) ; } ;
	Square getMoveType(ChessMove cm)				{ return ( ( cm >> 12) & BOTTOM6BITS) ; } ;
	Square getEPSquare(ChessMove cm)				{ return ( ( cm >> 18) & BOTTOM6BITS) ; } ;
	ChessMove CM( Square from, Square to, MoveType mt, Square epsq)
	{ return ( ( from ) | ( to << 6) | ( mt << 12) | (epsq << 18) ) ; }

	Square MakeSquare(short r, short c)				{ return 16 * r + c;};
	Square MakeSquare(string s)						{ 
		/*string sq;
		short r = s[0] - 65;
		short c = s[1] - 48;*/
		return 0 /* 8 * r + c*/;
	};

	/****************************************
	* Testing funcs
	****************************************/
	void PrintBoard(void);
	__int64 perft(int depth);

}; // end class "ChessGame"
