/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "ChessBoard.h"
ChessMove ChessBoard::nullmove = ChessMove(0,0);
// notation array is useful when converting array indexes to Computer algebraic
//char* MyClass::stringTable[2] = { "mystring1", "myString2" };
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
unsigned int ChessBoard::inttoboard[64] = { A1, B1, C1, D1, E1, F1, G1, H1,
								A2, B2, C2, D2, E2, F2, G2, H2,
								A3, B3, C3, D3, E3, F3, G3, H3,
								A4, B4, C4, D4, E4, F4, G4, H4,
								A5, B5, C5, D5, E5, F5, G5, H5,
								A6, B6, C6, D6, E6, F6, G6, H6,
								A7, B7, C7, D7, E7, F7, G7, H7,
								A8, B8, C8, D8, E8, F8, G8, H8};

unsigned int ChessBoard::boardtoint[144] = { 
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


int ChessBoard::out [8]		= { 0, 0, 0, 0, 0, 0, 0, 0 };
int ChessBoard::empty [8]	= { 0, 0, 0, 0, 0, 0, 0, 0 };
int ChessBoard::whitepawn [8]= { NORTHEAST, NORTHWEST, 0, 0, 0, 0, 0, 0};
int ChessBoard::knight [8]   = 
{
	NORTH + NORTHWEST, NORTH + NORTHEAST, SOUTH + SOUTHWEST, SOUTH + SOUTHEAST, 
	WEST + NORTHWEST, EAST + NORTHEAST, WEST + SOUTHWEST, EAST + SOUTHEAST
};
int ChessBoard::bishop [8]	= { NORTHWEST,  NORTHEAST, SOUTHWEST, SOUTHEAST, 0, 0, 0, 0};
int ChessBoard::rook [8]		= { NORTH, SOUTH, EAST, WEST , 0, 0, 0, 0};
int ChessBoard::queen [8]	= { NORTH, SOUTH, EAST, WEST, NORTHEAST, NORTHWEST, SOUTHWEST, SOUTHEAST };
int ChessBoard::king[8]		= { NORTH, SOUTH, EAST, WEST, NORTHEAST, NORTHWEST, SOUTHWEST, SOUTHEAST };
int ChessBoard::blackpawn [8]= { SOUTHWEST, SOUTHEAST, 0, 0, 0, 0, 0, 0 };


/****************************************************************
*  Now lets create constants for every piece, see ChessPiece.java for move details
*                  -------------------------------------Piece type
*                  |       -----------------------------Color
*                  |       |      ----------------------value
*                  |       |      |      ---------------possible moves
*                  |       |      |      |           |--movement vectors
* ChessPiece ( int pt, int c, int v, int pm, int [] mv, Description) 
* - Added last: name
*/


ChessPiece  ChessBoard::OUT =	ChessPiece( _OUT,    _OUT,	 0,	"OUT"         , 0, out	);
ChessPiece  ChessBoard::EMPTY=	ChessPiece( _EMPTY,  _EMPTY,   0,	"EMPTY"       , 0, empty);
ChessPiece  ChessBoard::WP =	ChessPiece( PAWN,   WHITE, 100,	"White Pawn"  , 2, whitepawn	);
ChessPiece  ChessBoard::WN =	ChessPiece( KNIGHT, WHITE, 300,	"White Knight", 8, knight); 
ChessPiece  ChessBoard::WB =	ChessPiece( BISHOP, WHITE, 300,	"White Bishop", 4, bishop);
ChessPiece  ChessBoard::WR =	ChessPiece( ROOK ,  WHITE, 450,	"White Rook"  , 4, rook	);
ChessPiece  ChessBoard::WQ =	ChessPiece( QUEEN,  WHITE,1050,	"White Queen" , 8, queen);
ChessPiece  ChessBoard::WK =	ChessPiece( KING,   WHITE,   0,	"White King"  , 8, king );
ChessPiece  ChessBoard::BP =	ChessPiece( PAWN,   BLACK, 100,	"Black Pawn"  , 2, blackpawn);
ChessPiece  ChessBoard::BN =	ChessPiece( KNIGHT, BLACK, 300,	"Black Knight", 8, knight); 
ChessPiece  ChessBoard::BB =	ChessPiece( BISHOP, BLACK, 300,	"Black Bishop", 4, bishop);
ChessPiece  ChessBoard::BR =	ChessPiece( ROOK ,  BLACK, 450,	"Black Rook"  , 4, rook);
ChessPiece  ChessBoard::BQ =	ChessPiece( QUEEN,  BLACK,1050,	"Black Queen" , 8, queen);
ChessPiece  ChessBoard::BK =	ChessPiece( KING,   BLACK,   0,	"Black King"  , 8, king);

/**************************************************************
* This is the initial position on a chess game, 
* The OUT value is being used as a sentinel value to eliminate a lot of 
* special bounds checking (because every piece moved differently).
* 
*/
ChessPiece ChessBoard::startingposition[144] = 
{ 
	OUT, 	OUT,	 OUT, 	OUT, 	OUT, 	OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT, 	OUT,
	OUT, 	OUT,	 OUT, 	OUT, 	OUT, 	OUT, 	OUT,	 OUT,	 OUT,	 OUT,	 OUT, 	OUT,
	OUT, 	OUT,	  BR, 	 BN, 	 BB, 	 BQ,	  BK,	  BB,	  BN,	  BR,	 OUT, 	OUT,
	OUT, 	OUT, 	 BP, 	 BP, 	 BP, 	 BP,	  BP,	  BP,	  BP,	  BP,	 OUT, 	OUT,
	OUT, 	OUT,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, 	OUT,	 OUT,
	OUT,	 OUT,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, 	OUT,	 OUT,
	OUT,	 OUT,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, 	OUT,	 OUT,
	OUT,	 OUT,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,	 OUT,	 OUT,
	OUT,	 OUT, 	 WP, 	 WP,	  WP, 	 WP,	  WP,	  WP,	  WP,	  WP,	 OUT, 	OUT,
	OUT,	 OUT, 	 WR,	  WN,	  WB,	  WQ,	  WK,	  WB,	  WN,	  WR,	 OUT, 	OUT,
	OUT,	 OUT, 	OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,
	OUT,	 OUT, 	OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT,	 OUT};



	/***************************************************************
	* getDescription(x) returns the piece name at location x
	*/
	string ChessBoard::getDescription( int x ) 
	{
		/*if ( x >= 0 && x < 144) 
		return (currentposition[x].name);
		else*/
		return "NULL";
	}
	/***************************************************************
	* getPieceAt(x) returns the piece at location x
	*/
	int ChessBoard::getPieceAt( int x ) 
	{
		if ( x >= 0 && x < 144) 
			return (currentposition[x].piecetype);
		else
			return 0;
	}
	/***************************************************************
	* getColorAt(x) returns the piece at location x
	*/
	int ChessBoard::getColorAt( int x ) 
	{
		if ( x >= 0 && x < 144) 
			return ( currentposition[x].color );
		else
			return 0;
	}
	/***************************************************************
	* Initialize the board and reset all the board information
	*/
	void ChessBoard::Init() 
	{
		for(int x = 0; x < 144; x++)
			currentposition[x] = startingposition[x];
		chessmoveindex = -1;
		while ( ! CMEMPTY())
		{   CMPOP();  };
		//LastMove = nullmove;
		BestSoFar = nullmove;
		sidetomove = WHITE;
		LastMoveInt = 0;
		ply = 0;
		//parent = null;	
		whitekingposition = 114;
		blackkingposition = 30;
		//start new on castling privileges
		Castlingpriviledges.blacklong = true;
		Castlingpriviledges.blackshort = true;
		Castlingpriviledges.whitelong = true;
		Castlingpriviledges.whiteshort =true;


	}
	/**
	* Copy constructor for ChessBoard object
	* 
	*/
	ChessBoard ChessBoard::operator= ( ChessBoard copy )
	{
		//allocate the squares and copy the initial position over to the array
		for(int x = 0; x < 144; x++)
			currentposition[x] = copy.currentposition[x];
		// Flush the stack
		//chessmoves = new Stack<ChessMove>();
		chessmoveindex = -1;

		//white starts the game
		sidetomove = copy.sidetomove;
		//this keeps track of how deep are we in the tree
		ply = copy.ply;
		//make sure parent point to NULL, 	
		//parent = copy.parent;	
		whitekingposition = copy.whitekingposition;
		blackkingposition = copy.blackkingposition;
		//start anew on castling privileges
		Castlingpriviledges = copy.Castlingpriviledges;
		LastMoveInt = copy.LastMoveInt;
		return *this;

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
	* Assumes that the argument is a valid chess position in the FEN format
	* FEN is "Forsyth-Edwards Notation"; it is a standard for describing chess
	*  positions using the ASCII character set. see http://loiodice.com/chess/cc-fen.sht
	* Here's the FEN for the starting position: rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1
	* // not implemented 
	*/
	ChessBoard::ChessBoard (string FEN)
	{
		Init();
	}

	/*******************************************************************
	* MakeMove (ChessMove)
	* Makes the selected move on the board, returns true if this move can actually be made
	* false otherwise.
	* 
	*/
	bool ChessBoard::MakeMove ( ChessMove cm )
	{
		if ( cm.to == whitekingposition || cm.to == blackkingposition )
		{
			return false;
		}
		// update king position and castling priviledges
		if(currentposition[cm.from] == WK )
		{
			whitecancastlekingside = false;
			whitecancastlequeenside = false;
			whitekingposition = cm.to;
		}
		if(currentposition[cm.from] == BK)
		{
			blackcancastlekingside = false;
			blackcancastlequeenside = false;
			blackkingposition = cm.to;
		}
		if ( cm.from == A1 )
			whitecancastlequeenside = false;
		if ( cm.from == H1 )
			whitecancastlekingside = false;
		if ( cm.from == A8 )
			blackcancastlequeenside = false;
		if ( cm.from == H8 )
			blackcancastlekingside = false;

		//remove the piece in the "from" square and put in on the "to" square
		currentposition[cm.to] = currentposition[cm.from];
		currentposition[cm.from] = EMPTY;
		// special code for special moves
		if (cm.castle )
		{
			//System.out.println("Processing a castling move");
			if ( sidetomove == WHITE )
			{
				whitecancastlekingside = false;
				whitecancastlequeenside = false;
				if ( cm.to == G1)          // short castle
				{
					currentposition[F1] = currentposition[H1];
					currentposition[H1] = EMPTY;
				}
				else                                   // long castle
				{
					currentposition[D1] = currentposition[A1];
					currentposition[A1] = EMPTY;
				}
			}
			else
			{
				blackcancastlekingside = false;
				blackcancastlequeenside = false;
				if ( cm.to == G8)          // short castle
				{
					currentposition[F8] = currentposition[H8];
					currentposition[H8] = EMPTY;
				}
				else                                   // long castle
				{
					currentposition[D8] = currentposition[A8];
					currentposition[A8] = EMPTY;
				}
			} // end if tomove == WHITE
		} // end if castling
		if ( cm.promotion )
		{
			//System.out.println("Processing a promotion");

			switch ( cm.piecetype )
			{
			case QUEEN:
				currentposition[cm.to] = (sidetomove == WHITE) ? WQ : BQ;
				break;
			case ROOK:
				currentposition[cm.to] = (sidetomove == WHITE) ? WR : BR;
				break;
			case BISHOP:
				currentposition[cm.to] = (sidetomove == WHITE) ? WB : BB;
				break;
			case KNIGHT:
				currentposition[cm.to] = (sidetomove == WHITE) ? WN : BN;
				break;
			}
		}
		if ( cm.enpassant )
		{
			//System.out.println("Processing an enpassant move");

			if ( sidetomove == WHITE )
				currentposition[cm.to + SOUTH] = EMPTY;
			else
				currentposition[cm.to + NORTH] = EMPTY;
		}
		//This helps prevent an ilegal position where the side that just moved is in check! 
		// this is illegal in chess.
		if ( sidetomove == WHITE )
		{
			if (IsAttacked( whitekingposition, BLACK ) > 0 )
			{
				return false;
			}
		}
		else
		{
			if (IsAttacked( blackkingposition, WHITE ) > 0 )
			{
				return false;
			}
		} // end if tomove == WHITE

		// Everything seems to be in order, change sides, update ply and last move and return true.
		// Switch side to move
		sidetomove = (sidetomove == WHITE) ? BLACK : WHITE;
		//increment ply
		ply ++;
		// keep track of last move, for enpassant etc...
		LastMoveInt = 0;

		return true;
	}


	/*******************************************************************
	* GenerateMoves ()
	* Generates every move possible from this position taking into account the 
	* movement of the pieces.
	* todo: recognize that in chess, the king is never captured.
	*/
	//void ChessBoard::GenerateMoves ( void )
	//{
	//	int target = (sidetomove == WHITE) ? BLACK : WHITE;
	//	int vector, dest;
	//	ChessMove cm;
	//	//Flush the stack
	//	while ( ! chessmoves.empty() )
	//	{
	//		//chessmoves.clear();
	//		chessmoves.pop();
	//	}
	//	//cm = (ChessMove)chessmoves.pop();

	//	// search the board and if the piece at position X is ours, generate the moves
	//	for(int x = 0; x < MAXSQUARES; x++)
	//	{
	//		if( getPieceAt( x ) == _OUT )		//if "piece" at this location is out, skip
	//			continue;			
	//		if( getPieceAt( x ) == _EMPTY )		//if "piece" at this location is empty, skip
	//			continue;		
	//		if( getColorAt( x ) == target )		//if piece at this location is from the opponent, skip
	//			continue;			
	//		if( getColorAt( x ) == sidetomove )	//this is our piece
	//		{
	//			/******************************************************************
	//			* use the movement vectors to determine the possible moves of this piece
	//			* used for all pieces but only in one direction each for KINGS and KNIGHTS
	//			*/
	//			if ( getPieceAt(x) == PAWN )  // add PAWN moves
	//			{
	//				//add the moves by this pawn to the list
	//				// first add some variables to reuse this code for BLACK pawns also
	//				int seventhrank, direction, enpasantrank, secondrank;
	//				if ( getColorAt(x) == WHITE ) // White pawns move NORTH
	//				{
	//					secondrank = 8;
	//					seventhrank = 3;
	//					direction = NORTH;
	//					enpasantrank = 5;
	//				}
	//				else
	//				{
	//					secondrank = 3;
	//					seventhrank = 8;
	//					direction = SOUTH;
	//					enpasantrank = 6;
	//				} // end if( getColorAt( x )  ==  WHITE 
	//				//System.out.println("direction = " + direction);
	//				if ( (x / 12) == secondrank )
	//				{
	//					// setting the enpassantpossible flag to true on these moves
	//					//System.out.println("adding the special second rank pawn move");
	//					//System.out.println("from " + x + " to " + (x + direction));
	//					if( (getColorAt( (x + direction)  ) == _EMPTY ) && (getColorAt( (x + direction + direction) ) == _EMPTY ) )
	//						chessmoves.push(  ChessMove( x, x + direction + direction, false, false, false, false, 0, true));
	//				}
	//				if ( (x / 12) == seventhrank ) // if on 7th rank, add promoting moves
	//				{
	//					//System.out.println("adding promotion pawn moves" );
	//					if( getPieceAt(x + direction) == _EMPTY)
	//					{
	//						chessmoves.push(  ChessMove(x, x + direction, false, true, false, false, QUEEN, false));
	//						chessmoves.push(  ChessMove(x, x + direction, false, true, false, false, ROOK, false));
	//						chessmoves.push(  ChessMove(x, x + direction, false, true, false, false, KNIGHT, false));
	//						chessmoves.push(  ChessMove(x, x + direction, false, true, false, false, BISHOP, false));
	//					}
	//					if( getColorAt(x + direction  + EAST) == target )
	//					{					 
	//						chessmoves.push(  ChessMove(x, x + direction + EAST, true, true, false, false, QUEEN, false));
	//						chessmoves.push(  ChessMove(x, x + direction + EAST, true, true, false, false, ROOK, false));
	//						chessmoves.push(  ChessMove(x, x + direction + EAST, true, true, false, false, KNIGHT, false));
	//						chessmoves.push(  ChessMove(x, x + direction + EAST, true, true, false, false, BISHOP, false));
	//					}
	//					if( getColorAt(x + direction + WEST) == target )
	//					{
	//						chessmoves.push(  ChessMove(x, x + direction + WEST, true, true, false, false, QUEEN, false));
	//						chessmoves.push(  ChessMove(x, x + direction + WEST, true, true, false, false, ROOK, false));
	//						chessmoves.push(  ChessMove(x, x + direction + WEST, true, true, false, false, KNIGHT, false));
	//						chessmoves.push(  ChessMove(x, x + direction + WEST, true, true, false, false, BISHOP, false));
	//					}
	//				} //end promoting check
	//				else  // this must be a normal pawn move
	//				{
	//					//System.out.println("adding the normal pawn moves" );
	//					if( getColorAt( x + direction ) == _EMPTY )
	//						chessmoves.push(  ChessMove(x, x + direction ));

	//					// SEE IF CAN CAPTURE EAST
	//					if(  getColorAt( x + direction + EAST) == target )
	//						chessmoves.push(  ChessMove(x, x + direction + EAST, true));

	//					//SEE IF CAN CAPTURE WEST
	//					if(  getColorAt(x + direction + WEST) == target )
	//						chessmoves.push(  ChessMove(x, x +  direction + WEST, true));			
	//				}
	//				if (x / 12 == enpasantrank ) // if on 5th rank, check for EP capture
	//				{
	//					if ( ply > 2)  // no sense in asking before first move
	//						if ( LastMove.enpassantpossible )
	//						{
	//							if ( LastMove.to == x + WEST )
	//								chessmoves.push(  ChessMove(x, x + direction + WEST, true, false, true, false, BISHOP, false));
	//							if ( LastMove.to == x + EAST )
	//								chessmoves.push(  ChessMove(x, x + direction + EAST, true, false, true, false, BISHOP, false));
	//						}

	//				} // end if on 5th rank, check for EP capture

	//				continue;

	//			} // end if piece is a PAWN

	//			/**********************************************************************
	//			* KINGS, they move in every direction but only once.
	//			*  Special moves: - cannot move to check
	//			*                 - castle king side and queenside
	//			*/ 

	//			if ( getPieceAt(x) == KING  )  // add KING moves
	//			{
	//				for( vector = 0; vector < currentposition[x].possiblemoves ; vector++)
	//				{
	//					//System.out.println("Generating moves for " + getDescription( x ) + ", vertor = " + vector);
	//					//System.out.println("first vector is: " + squares[x].movementvectors[vector]);

	//					if( getPieceAt(x +  currentposition[x].movementvectors[vector]) == _EMPTY)
	//						chessmoves.push(  ChessMove( x, x +  currentposition[x].movementvectors[vector]) );
	//					if( getColorAt(x +  currentposition[x].movementvectors[vector]) == target)
	//						chessmoves.push(  ChessMove( x, x +  currentposition[x].movementvectors[vector], true) );
	//				}
	//				// add castling priviledges
	//				if ( sidetomove == WHITE )
	//				{
	//					if ( whitecancastlekingside ) 
	//					{
	//						//System.out.println("checking white short castle move");
	//						if ( getPieceAt( F1 ) == _EMPTY && getPieceAt(G1) == _EMPTY)       
	//						{
	//							if ( (IsAttacked(E1 , BLACK) +
	//								IsAttacked( F1, BLACK) + 
	//								IsAttacked( G1, BLACK)) == 0  )
	//							{
	//								//System.out.println("Adding white short castle move");
	//								chessmoves.push(  ChessMove( E1,G1, false, false, false, true, 0, false) );
	//							}
	//						}
	//					}
	//					if ( whitecancastlequeenside ) 
	//					{
	//						if ( getPieceAt( D1) == _EMPTY && getPieceAt( C1) == _EMPTY &&  getPieceAt( B1) == _EMPTY) 
	//						{
	//							if ( (IsAttacked( E1, BLACK) +
	//								IsAttacked(  D1, BLACK) + 
	//								IsAttacked(  C1, BLACK)) == 0  )
	//								chessmoves.push(  ChessMove( E1, C1, false, false, false, true, 0, false) );
	//						}
	//					}
	//				}
	//				else // adding black castling moves
	//				{
	//					if ( blackcancastlekingside ) 
	//					{
	//						if ( getPieceAt( F8) == _EMPTY && getPieceAt(G8 ) == _EMPTY)
	//						{

	//							if ( (IsAttacked(E8, WHITE) +
	//								IsAttacked(  F8, WHITE) + 
	//								IsAttacked(  G8, WHITE)) == 0  )
	//								chessmoves.push(  ChessMove(E8, G8, false, false, false, true, 0, false) );
	//						}
	//					}
	//					if ( blackcancastlequeenside ) 
	//					{
	//						if ( getPieceAt(D8) == _EMPTY && getPieceAt( C8) == _EMPTY &&  getPieceAt( B8) == _EMPTY)
	//						{

	//							if ( (IsAttacked( E8, WHITE) +
	//								IsAttacked(  D8, WHITE) + 
	//								IsAttacked(  C8, WHITE)) == 0  )
	//								chessmoves.push(  ChessMove( E8, C8, false, false, false, true, 0, false) );
	//						}
	//					}

	//				} // end if tomove is WHITE

	//				continue;
	//			}// end of checking for KING
	//			/**********************************************************************
	//			* this is a KNIGHT, they move in every direction but only once.
	//			*  
	//			*/ 

	//			if ( getPieceAt(x) == KNIGHT )  // add KNIGHT moves
	//			{
	//				for( vector = 0; vector < currentposition[x].possiblemoves ; vector++)
	//				{
	//					//System.out.println("Generating moves for " + getDescription( x ) + ", vertor = " + vector);
	//					//System.out.println("first vector is: " + squares[x].movementvectors[vector]);

	//					if( getPieceAt(x +  currentposition[x].movementvectors[vector]) == _EMPTY)
	//						chessmoves.push(  ChessMove( x, x +  currentposition[x].movementvectors[vector]) );
	//					if( getColorAt(x +  currentposition[x].movementvectors[vector]) == target)
	//						chessmoves.push(  ChessMove( x, x +  currentposition[x].movementvectors[vector], true) );
	//				}
	//				continue;
	//			} // end for KNIGHTS
	//			/************************************************************8
	//			* the piece is a Bishop, Queen or Rook, they all move 
	//			* in the same direction as long as they don't go outside the board
	//			* or find a piece of the same color. If they encounter a piece of
	//			* the opposite color, the move is added to the stack with move type = CAPTURE.
	//			*/
	//			for( vector = 0; vector < currentposition[x].possiblemoves ; vector++)
	//			{
	//				//System.out.println("Generating moves for " + getDescription( x ) + ", vertor = " + vector);
	//				//System.out.println("first vector is: " + squares[x].movementvectors[vector]);
	//				for(dest = x + currentposition[x].movementvectors[vector]; _EMPTY == getPieceAt( dest ) ; dest += currentposition[x].movementvectors[vector])
	//				{
	//					//System.out.println("Generating moves, movementvertors = " + squares[x].movementvectors[vector]);
	//					chessmoves.push(  ChessMove( x, dest) );
	//				}
	//				if( getColorAt(dest) == target)
	//					chessmoves.push(  ChessMove( x, dest, true) );
	//			} // end for vector...
	//		} // end if( getColorAt( x ) & tomove
	//	} // end for loop
	//} // end GenerateMoves( )
	/*******************************************************************
	* IsAttacked( Square, side)
	* Returns the number of pieces attacking "Square" by "side" 
	* 
	*/
	int ChessBoard::IsAttacked ( int sq, int side )
	{
		// skip to square x, check if a piece from "side" is attacking this square
		//checking for pawns, pawns are the only piece we care about the color, because they move 
		// differently depending on what color they are
		int otherside = (side == WHITE) ? BLACK : WHITE;
		int vector, dest;
		int total = 0;
		if ( side == WHITE ) 
		{
			if ( getPieceAt(sq + SOUTHEAST) == PAWN && getColorAt(sq + SOUTHEAST) == WHITE) 
				total ++;
			if ( getPieceAt(sq + SOUTHWEST) == PAWN && getColorAt(sq + SOUTHWEST) == WHITE) 
				total ++;
		}
		else
		{
			if ( getPieceAt(sq + NORTHEAST) == PAWN && getColorAt(sq + NORTHEAST) == BLACK) 
				total ++;
			if ( getPieceAt(sq + NORTHWEST) == PAWN && getColorAt(sq + NORTHWEST) == BLACK) 
				total ++;
		}
		for( vector = 0; vector < WK.possiblemoves ; vector++)
		{
			if( getPieceAt(sq +  WK.movementvectors[vector]) == KING && 
				getColorAt(sq +  WK.movementvectors[vector]) == side)
				total++;
		}
		for( vector = 0; vector < WN.possiblemoves ; vector++)
		{
			if( getPieceAt(sq +  WN.movementvectors[vector]) == KNIGHT && getColorAt(sq +  WN.movementvectors[vector]) == side)
				total++;
		}
		/************************************************************
		* the piece is a Bishop, Queen or Rook, they all move in the same direction as long as they don't go 
		* outside the board or find a piece of the same color. 
		*/
		for( vector = 0; vector < WQ.possiblemoves ; vector++)
		{
			for(dest = sq + WQ.movementvectors[vector]; getPieceAt(dest ) == _EMPTY; dest += WQ.movementvectors[vector]);
			//System.out.println("Square " + notation[sq] + " is attacked by a queen");
			if ( getPieceAt(dest) == QUEEN && getColorAt(dest ) == side)
			{
				//System.out.println("Square " + notation[sq] + " is attacked by a queen");

				total ++;
			}
		}
		/////////////////////////////////////
		for( vector = 0; vector < WR.possiblemoves ; vector++)
		{
			for(dest = sq + WR.movementvectors[vector]; getPieceAt( dest ) == _EMPTY; dest += WR.movementvectors[vector]);
			//System.out.println("Square " + notation[sq] + " is attacked by a queen");
			if ( getPieceAt(dest) == ROOK && getColorAt(dest ) == side)
			{
				//System.out.println("Square " + notation[sq] + " is attacked by a rook");
				total ++;
			}
		}
		for( vector = 0; vector < WB.possiblemoves ; vector++)
		{
			for(dest = sq + WB.movementvectors[vector]; getPieceAt(dest ) == _EMPTY; dest += WB.movementvectors[vector]);
			//System.out.println("Square " + notation[sq] + " is attacked by a queen");
			if ( getPieceAt(dest) == BISHOP && getColorAt(dest ) == side)
			{
				//System.out.println("Square " + notation[sq] + " is attacked by a bishop");

				total ++;
			}
		}
		//System.out.println("Square " + notation[sq] + " is attacked " + total + " times.");
		return total;
	} // end IsAttacked


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
				if(getPieceAt(x * 12 + y) != _OUT )
				{				
					if(getPieceAt(x * 12 + y) == _EMPTY)
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


	/**************************************************************
	* Input: 2 char string
	* output: index of the string in "notation" array
	*/
	int ChessBoard::getIndex(string x)
	{
		for (int c = NOTATIONMIN; c < NOTATIONMAX; c++)
			if ( notation[c] == x )
				return c;
		return INVALID;
	} // getIndex
	/**************************************************************
	*/
	unsigned int ChessBoard::CMPOP(void)
	{
		if ( ! CMEMPTY() )
			return chessmoves_arr[chessmoveindex--];
		return (0);

	} 
	/**************************************************************
	*/
	bool ChessBoard::CMEMPTY(void)	
	{
		if ( chessmoveindex < 0 )
			return true;
		return false;	
	}

	/**************************************************************
	*/
	void ChessBoard::CMPUSH(unsigned int cm)
	{
			chessmoves_arr[chessmoveindex++] = cm;
	} 



/**********************************************************
* 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 = short is 2 bytes, 16 bits
* 00000000000000000000000000000000000000000000000000= 32 bit integer
* 
* XXXXXX         from is 0-63, 2^6, 6 bits to store from
* to    XXXXXX   is 0-63, 2^6, 6 bits to store to
* Is capture  X  one bit
* Is promotion X one bit
* is enpassant  X move? one bit
* Is castle      X one bit
* Is enpassant    X possible? one bit
* Piece type       XXX for promotion
* Value of move       XXXXXXXXXXXXXXXX 16 bits (0-65536) or (-30000-30000)
************************************************************/


/*******************************************************************
* MakeIntMove (unsigned int)
* Makes the selected move on the board, returns true if this move can actually be made
* false otherwise.
* 
*/


#define FROM( cm ) (inttoboard[cm & FROM_MASK])
#define TO( cm )   (inttoboard[ (cm & TO_MASK) >> 6])
#define CASTLE( cm ) (cm & CASTLE_MASK)
#define CAPTURE(cm)  (cm & CAP_MASK)
#define PROMOTION(cm) ( cm & PROMOTION_MASK)
#define PIECE(cm)     (( cm & PIECE_MASK)<<3)
#define ENPASSANT(cm)  (( cm & ENPASSANT_MASK))


bool ChessBoard::MakeIntMove ( unsigned int cm )
{
	castling tempCastlingpriviledges = Castlingpriviledges;
	if ( TO(cm) == whitekingposition || TO(cm) == blackkingposition )
	{
		return false;
	}
	// update king position and castling priviledges
	if(currentposition[FROM(cm)] == WK && ! CASTLE(cm))
	{
		Castlingpriviledges.whiteshort = false;
		Castlingpriviledges.whitelong = false;
		whitekingposition = TO(cm);
	}
	if(currentposition[FROM(cm)] == BK && !CASTLE(cm))
	{
		Castlingpriviledges.blackshort = false;
		Castlingpriviledges.blacklong = false;
		blackkingposition = TO(cm);
	}
	if ( FROM(cm) == A1 )
		Castlingpriviledges.whitelong = false;
	if ( FROM(cm) == H1 )
		Castlingpriviledges.whiteshort = false;
	if ( FROM(cm) == A8 )
		Castlingpriviledges.blacklong = false;
	if ( FROM(cm) == H8 )
		Castlingpriviledges.blackshort = false;

	//remove the piece in the "from" square and put in on the "to" square
	currentposition[TO(cm)] = currentposition[FROM(cm)];
	currentposition[FROM(cm)] = EMPTY;
	// special code for special moves
	if (CASTLE(cm) )
	{
		//System.out.println("Processing a castling move");
		if ( sidetomove == WHITE )
		{
			Castlingpriviledges.whitelong = false;
			Castlingpriviledges.whiteshort = false;
			whitekingposition = TO(cm);
			if ( TO(cm) == G1)          // short castle
			{
				currentposition[F1] = currentposition[H1];
				currentposition[H1] = EMPTY;
			}
			else                                   // long castle
			{
				currentposition[D1] = currentposition[A1];
				currentposition[A1] = EMPTY;
			}
		}
		else
		{
			Castlingpriviledges.blackshort = false;
			Castlingpriviledges.blacklong = false;
			blackkingposition = TO(cm);
			if ( TO(cm) == G8)          // short castle
			{
				currentposition[F8] = currentposition[H8];
				currentposition[H8] = EMPTY;
			}
			else                                   // long castle
			{
				currentposition[D8] = currentposition[A8];
				currentposition[A8] = EMPTY;
			}
		} // end if tomove == WHITE
	} // end if castling
	if ( PROMOTION(cm) )
	{
		//System.out.println("Processing a promotion");

		switch ( PIECE(cm) )
		{
		case QUEEN:
			currentposition[TO(cm)] = (sidetomove == WHITE) ? WQ : BQ;
			break;
		case ROOK:
			currentposition[TO(cm)] = (sidetomove == WHITE) ? WR : BR;
			break;
		case BISHOP:
			currentposition[TO(cm)] = (sidetomove == WHITE) ? WB : BB;
			break;
		case KNIGHT:
			currentposition[TO(cm)] = (sidetomove == WHITE) ? WN : BN;
			break;
		}
	}
	if ( ENPASSANT(cm) )
	{
		//System.out.println("Processing an enpassant move");

		if ( sidetomove == WHITE )
			currentposition[TO(cm) + SOUTH] = EMPTY;
		else
			currentposition[TO(cm) + NORTH] = EMPTY;
	}
	//This helps prevent an ilegal position where the side that just moved is in check! 
	// this is illegal in chess.
	if ( sidetomove == WHITE )
	{
		if (IsAttacked( whitekingposition, BLACK ) > 0 )
		{
			Castlingpriviledges = tempCastlingpriviledges;
			return false;
		}
	}
	else
	{
		if (IsAttacked( blackkingposition, WHITE ) > 0 )
		{
			Castlingpriviledges = tempCastlingpriviledges;
			return false;
		}
	} // end if tomove == WHITE

	// Everything seems to be in order, change sides, update ply and last move and return true.
	// Switch side to move
	sidetomove = (sidetomove == WHITE) ? BLACK : WHITE;
	//increment ply
	ply ++;
	// keep track of last move, for enpassant etc...
	LastMoveInt = cm;

	return true;
}
