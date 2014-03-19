/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "ChessBoard.h"

short ChessBoard::inttoboard[64] = { 
								A1, B1, C1, D1, E1, F1, G1, H1,
								A2, B2, C2, D2, E2, F2, G2, H2,
								A3, B3, C3, D3, E3, F3, G3, H3,
								A4, B4, C4, D4, E4, F4, G4, H4,
								A5, B5, C5, D5, E5, F5, G5, H5,
								A6, B6, C6, D6, E6, F6, G6, H6,
								A7, B7, C7, D7, E7, F7, G7, H7,
								A8, B8, C8, D8, E8, F8, G8, H8};

short ChessBoard::boardtoint[144] = { 
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0,	56, 57, 58, 59, 60, 61, 62, 63, 0, 0,
	0, 0,	48, 49, 50, 51, 52, 53, 54, 55, 0, 0,
	0, 0,	40, 41, 42, 43, 44, 45, 46, 47, 0, 0,
	0, 0,	32, 33, 34, 35, 36, 37, 38, 39, 0, 0,
	0, 0,	24, 25, 26, 27, 28, 29, 30, 31, 0, 0,
	0, 0,	16, 17, 18, 19, 20, 21, 22, 23, 0, 0,
	0, 0,	8, 9, 10, 11, 12, 13, 14, 15, 0, 0,
	0, 0,	0, 1, 2, 3, 4, 5, 6, 7, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	short ChessBoard::insideboadonly[64] = {
		110, 111, 112, 113, 114, 115, 116, 117,
		98 ,  99, 100, 101, 102, 103, 104, 105,
		 86,  87,  88,  89,  90,  91,  92,  93,
		 74,  75,  76,  77,  78,  79,  80,  81,
		 62,  63,  64,  65,  66,  67,  68,  69,
		 50,  51,  52,  53,  54,  55,  56,  57,
		 38,  39,  40,  41,  42,  43,  44,  45,
		 26,  27,  28,  29,  30,  31,  32,  33};

	char * ChessBoard::notation[144] = 
{
	" X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X",
	" X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X",
	" X", " X",	"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", " X", " X",
	" X", " X",	"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", " X", " X",
	" X", " X",	"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", " X", " X",
	" X", " X",	"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", " X", " X",
	" X", " X",	"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", " X", " X",
	" X", " X",	"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", " X", " X",
	" X", " X",	"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", " X", " X",
	" X", " X",	"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", " X", " X",
	" X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X",
	" X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X"
};
/**************************************************************
* This is the initial position on a chess game, 
* The OUT value is being used as a sentinel value to eliminate a lot of 
* special bounds checking (because every piece moved differently).
* 
*/
Piece ChessBoard::startingposition[144] = 
{ 
	OUT, 	OUT,	 OUT, 	OUT, 	OUT, 	OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT, 	OUT,
	OUT, 	OUT,	 OUT, 	OUT, 	OUT, 	OUT, 	OUT,	 OUT,	 OUT,	 OUT,	 OUT, 	OUT,
	OUT, 	OUT,	 BR, 	 BN, 	 BB, 	 BQ,	  BK,	  BB,	  BN,	  BR,	 OUT, 	OUT,
	OUT, 	OUT, 	 BP, 	 BP, 	 BP, 	 BP,	  BP,	  BP,	  BP,	  BP,	 OUT, 	OUT,
	OUT, 	OUT,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, 	OUT,	 OUT,
	OUT,	 OUT,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, 	OUT,	 OUT,
	OUT,	 OUT,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, 	OUT,	 OUT,
	OUT,	 OUT,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,	 OUT,	 OUT,
	OUT,	 OUT, 	 WP, 	 WP,	  WP, 	 WP,	  WP,	  WP,	  WP,	  WP,	 OUT, 	OUT,
	OUT,	 OUT, 	 WR,	  WN,	  WB,	  WQ,	  WK,	  WB,	  WN,	  WR,	 OUT, 	OUT,
	OUT,	 OUT, 	OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,
	OUT,	 OUT, 	OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT};

	
	int  ChessBoard::kingvectors[8]		= { NORTH, SOUTH, EAST, WEST, NORTHEAST, NORTHWEST, SOUTHWEST, SOUTHEAST };
	int  ChessBoard::knightvectors[8]	= {
	NORTH + NORTHWEST, NORTH + NORTHEAST, SOUTH + SOUTHWEST, SOUTH + SOUTHEAST, 
	WEST + NORTHWEST, EAST + NORTHEAST, WEST + SOUTHWEST, EAST + SOUTHEAST
	};
	int  ChessBoard::bishopvectors[8]	= { NORTHWEST,  NORTHEAST, SOUTHWEST, SOUTHEAST, 0, 0, 0, 0};
	int  ChessBoard::rookvectors[8]		= { NORTH, SOUTH, EAST, WEST , 0, 0, 0, 0};
	int  ChessBoard::queenvectors[8]		= { NORTH, SOUTH, EAST, WEST, NORTHEAST, NORTHWEST, SOUTHWEST, SOUTHEAST };
	/***************************************************************
	* Initialize the board and reset all the board information
	*/
	void ChessBoard::Init() 
	{
		for(int x = 0; x < 144; x++)
			currentposition[x] = startingposition[x];
		
		while ( ! m_movestack.empty())
		{   m_movestack.pop();  };

		m_boardState.castling.blacklong = true;
		m_boardState.castling.blackshort = true;
		m_boardState.castling.whitelong = true;
		m_boardState.castling.whiteshort = true;
		m_boardState.ply = 0;
		m_boardState.m_BestSoFar = 0;
		m_boardState.m_bWhitetomove = TRUE;
		m_boardState.m_sBlackkingposition = E8;
		m_boardState.m_sWhitekingposition = E1;
		m_boardState.m_BestValueSoFar = -30000;
		m_boardState.m_LastMove = 0;
	}
	

	/***
	* Chessboard construction, initialize the board to the initial position
	*/
	ChessBoard::ChessBoard ()
	{
		Init();
	}

	/***
	* Chessboard contructor with String as argument in FEN format.
	*/
	ChessBoard::ChessBoard (string FEN)
	{
		Init();
	}
	int ChessBoard::possibleMoves(Piece p )
	{
		if ( p & KING)  return 8;
		if ( p & QUEEN)  return 8;
		if ( p & BISHOP)  return 4;
		if ( p & ROOK)  return 4;
		if ( p & KNIGHT) return 8;
		return 0;
	};
	
	/**************************************************************
	* MakeString ()
	*/
	string ChessBoard::MakeString(ChessMove cm)
	{
		string move = "";
		int f = FROM(cm);
		int t = TO(cm);
		
		//if ( isPromotion(cm) )
		move = getNotation(f);
		move += getNotation(t);
		return move;
	}
	/**************************************************************
	* PrintBoard ()
	* Searches the array and prints a text representation of the piece on that position
	* If the square is "EMPTY", it prints ":::" if he square is dark to better approximate
	* a chess board.
	*/

	string ChessBoard::PrintBoard ( void ) 
	{
		string b = "";
		int x,y;
		for ( x = 0; x < 12; x ++) 
		{
			b = b + "\n";
			for ( y = 0; y < 12; y ++)
			{
				if(getPieceAt(x * 12 + y) != OUT )
				{				
					if(getPieceAt(x * 12 + y) == EMPTY)
					{
						if( ( (y + x) % 2) == 1 ) 
							b = b +  "   ";
						else
							b = b +  ":::";
					}
					else 
					{
						int type;
						type = getColorAt(x * 12 + y);
						if((type == WHITE) ) 
							b = b +  "W";
						else
							b = b +  "B";
						type = getPieceAt(x * 12 + y);
						if((type == PAWN))		b = b +  "P ";
						if((type == ROOK))		b = b +  "R ";
						if((type == KNIGHT) )	b = b +  "N ";
						if((type == BISHOP))	b = b +  "B ";
						if((type == QUEEN))		b = b +  "Q ";
						if((type == KING))		b = b +  "K ";
					}//end second if				
				}//end first if
			}//end for
		}//end 1st for
		return b;
	}


	
