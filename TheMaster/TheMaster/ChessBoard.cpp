/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "ChessBoard.h"

unsigned int ChessBoard::inttoboard[64] = { 
								A1, B1, C1, D1, E1, F1, G1, H1,
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


	
