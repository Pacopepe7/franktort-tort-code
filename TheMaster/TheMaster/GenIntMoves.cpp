	/*******************************************************************
	* GenerateIntMoves ()
	* Generates every move possible from this position taking into account the 
	* movement of the pieces.
	* 
	*/

#include "ChessBoard.h"
#include <vector>
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
* Piece type      XXX for promotion
* Is enpassant       X possible? one bit
* Value of move       XXXXXXXXXXXXXXXX 16 bits (0-65536) or (-30000-30000)
************************************************************/

#define CHESSMOVE( from,  to, cap, prom, ep, castle, piece, eppossible) \
				 ( ((boardtoint[from] ) ) | \
				  ((boardtoint[to]<<6)	) | \
				  ((cap<<12)           ) | \
				  ((prom<<13)          ) | \
				  ((ep<<14)            ) | \
				  ((castle << 15)      ) | \
				  ((eppossible << 16)       ) | \
				  (((piece>>3) << 17   ) ) )
// piece shift is 19. but knights (the first promotable piece is 4 so shifting back 2 - 17
#define SIMPLECHESSMOVE( from,  to) \
				 ( (boardtoint[from]) | \
				 ( (boardtoint[to]<<6)  ) )

#define CAPTURECHESSMOVE( from,  to, cap) \
				 ( (boardtoint[from]) | \
				 ( (boardtoint[to]<<6)  ) | \
				   ((cap<<12)           ) )
#define ENPASSANT(cm)  (( cm & ENPASSANT_MASK))
#define ENPASSANTPOSSIBLE(cm) (( cm & ENPASSANTPOSSIBLE_MASK))
#define FROM( cm ) (inttoboard[cm & FROM_MASK])
#define TO( cm )   (inttoboard[ ((cm<<6) & TO_MASK)])

	void ChessBoard::GenerateIntMoves ( void )
	{
		int target = (sidetomove == WHITE) ? BLACK : WHITE;
		int vector, dest;

		// search the board and if the piece at position X is ours, generate the moves
		for(int x = 0; x < 144; x++)
		{
			if( getPieceAt( x ) == _OUT )		//if "piece" at this location is out, skip
				continue;			
			if( getPieceAt( x ) == _EMPTY )		//if "piece" at this location is empty, skip
				continue;		
			if( getColorAt( x ) == target )		//if piece at this location is from the opponent, skip
				continue;			
			if( getColorAt( x ) == sidetomove )	//this is our piece
			{
				/******************************************************************
				* use the movement vectors to determine the possible moves of this piece
				* used for all pieces but only in one direction each for KINGS and KNIGHTS
				*/
				if ( getPieceAt(x) == PAWN )  // add PAWN moves
				{
					//add the moves by this pawn to the list
					// first add some variables to reuse this code for BLACK pawns also
					int seventhrank, direction, enpasantrank, secondrank;
					if ( getColorAt(x) == WHITE ) // White pawns move NORTH
					{
						secondrank = 8;
						seventhrank = 3;
						direction = NORTH;
						enpasantrank = 5;
					}
					else
					{
						secondrank = 3;
						seventhrank = 8;
						direction = SOUTH;
						enpasantrank = 6;
					} // end if( getColorAt( x )  ==  WHITE 
					
					if ( (x / 12) == secondrank )
					{
						// setting the enpassantpossible flag to true on these moves
						if( (getColorAt( (x + direction)  ) == _EMPTY ) && (getColorAt( (x + direction + direction) ) == _EMPTY ) )
							CMPUSH(  CHESSMOVE( x, x + direction + direction, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE));
					}
					if ( (x / 12) == seventhrank ) // if on 7th rank, add promoting moves
					{
						//System.out.println("adding promotion pawn moves" );
						if( getPieceAt(x + direction) == _EMPTY)
						{
							CMPUSH(  CHESSMOVE(x, x + direction, FALSE, TRUE, FALSE, FALSE, QUEEN, FALSE));
							CMPUSH(  CHESSMOVE(x, x + direction, FALSE, TRUE, FALSE, FALSE, ROOK, FALSE));
							CMPUSH(  CHESSMOVE(x, x + direction, FALSE, TRUE, FALSE, FALSE, KNIGHT, FALSE));
							CMPUSH(  CHESSMOVE(x, x + direction, FALSE, TRUE, FALSE, FALSE, BISHOP, FALSE));
						}
						if( getColorAt(x + direction  + EAST) == target )
						{					 
							CMPUSH(  CHESSMOVE(x, x + direction + EAST, TRUE, TRUE, FALSE, FALSE, QUEEN, FALSE));
							CMPUSH(  CHESSMOVE(x, x + direction + EAST, TRUE, TRUE, FALSE, FALSE, ROOK, FALSE));
							CMPUSH(  CHESSMOVE(x, x + direction + EAST, TRUE, TRUE, FALSE, FALSE, KNIGHT, FALSE));
							CMPUSH(  CHESSMOVE(x, x + direction + EAST, TRUE, TRUE, FALSE, FALSE, BISHOP, FALSE));
						}
						if( getColorAt(x + direction + WEST) == target )
						{
							CMPUSH(  CHESSMOVE(x, x + direction + WEST, TRUE, TRUE, FALSE, FALSE, QUEEN, FALSE));
							CMPUSH(  CHESSMOVE(x, x + direction + WEST, TRUE, TRUE, FALSE, FALSE, ROOK, FALSE));
							CMPUSH(  CHESSMOVE(x, x + direction + WEST, TRUE, TRUE, FALSE, FALSE, KNIGHT, FALSE));
							CMPUSH(  CHESSMOVE(x, x + direction + WEST, TRUE, TRUE, FALSE, FALSE, BISHOP, FALSE));
						}
					} //end promoting check
					  // this must be a normal pawn move
					else
					{
						//System.out.println("adding the normal pawn moves" );
						if( getColorAt( x + direction ) == _EMPTY )
							CMPUSH(  SIMPLECHESSMOVE(x, x + direction ));

						// SEE IF CAN CAPTURE EAST
						if(  getColorAt( x + direction + EAST) == target )
							CMPUSH(  CAPTURECHESSMOVE(x, x + direction + EAST, TRUE));

						//SEE IF CAN CAPTURE WEST
						if(  getColorAt(x + direction + WEST) == target )
							CMPUSH(  CAPTURECHESSMOVE(x, x +  direction + WEST, TRUE));			
					}
					if (x / 12 == enpasantrank ) // if on 5th rank, check for EP capture
					{
						
							if ( ENPASSANTPOSSIBLE(LastMoveInt) )
							{
								if ( TO(LastMoveInt) == x + WEST )
									CMPUSH(  CHESSMOVE(x, x + direction + WEST, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE));
								if ( TO(LastMoveInt) == x + EAST )
									CMPUSH(  CHESSMOVE(x, x + direction + EAST, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE));
							}

					} // end if on 5th rank, check for EP capture

					continue;

				} // end if piece is a PAWN

				/**********************************************************************
				* KINGS, they move in every direction but only once.
				*  Special moves: - cannot move to check
				*                 - castle king side and queenside
				*/ 

				if ( getPieceAt(x) == KING  )  // add KING moves
				{
					for( vector = 0; vector < currentposition[x].possiblemoves ; vector++)
					{
						if( getPieceAt(x +  currentposition[x].movementvectors[vector]) == _EMPTY)
							CMPUSH(  SIMPLECHESSMOVE( x, x +  currentposition[x].movementvectors[vector]) );
						if( getColorAt(x +  currentposition[x].movementvectors[vector]) == target)
							CMPUSH(  CAPTURECHESSMOVE( x, x +  currentposition[x].movementvectors[vector], TRUE) );
					}
					// add castling priviledges
					if ( sidetomove == WHITE )
					{
						if ( Castlingpriviledges.whiteshort ) 
						{
							//System.out.println("checking white short castle move");
							if ( getPieceAt( F1 ) == _EMPTY && getPieceAt(G1) == _EMPTY)       
							{
								if ( (IsAttacked(E1 , BLACK) +
									IsAttacked( F1, BLACK) + 
									IsAttacked( G1, BLACK)) == 0  )
								{
									//System.out.println("Adding white short castle move");
									CMPUSH(  CHESSMOVE( E1,G1, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE) );
								}
							}
						}
						if ( Castlingpriviledges.whitelong ) 
						{
							if ( getPieceAt( D1) == _EMPTY && getPieceAt( C1) == _EMPTY &&  getPieceAt( B1) == _EMPTY) 
							{
								if ( (IsAttacked( E1, BLACK) +
									IsAttacked(  D1, BLACK) + 
									IsAttacked(  C1, BLACK)) == 0  )
									CMPUSH(  CHESSMOVE( E1, C1, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE) );
							}
						}
					}
					else // adding black castling moves
					{
						if ( Castlingpriviledges.blackshort ) 
						{
							if ( getPieceAt( F8) == _EMPTY && getPieceAt(G8 ) == _EMPTY)
							{

								if ( (IsAttacked(E8, WHITE) +
									IsAttacked(  F8, WHITE) + 
									IsAttacked(  G8, WHITE)) == 0  )
									CMPUSH(  CHESSMOVE(E8, G8, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE) );
							}
						}
						if ( Castlingpriviledges.blacklong ) 
						{
							if ( getPieceAt(D8) == _EMPTY && getPieceAt( C8) == _EMPTY &&  getPieceAt( B8) == _EMPTY)
							{

								if ( (IsAttacked( E8, WHITE) +
									IsAttacked(  D8, WHITE) + 
									IsAttacked(  C8, WHITE)) == 0  )
									CMPUSH(  CHESSMOVE( E8, C8, FALSE, FALSE, FALSE, TRUE, FALSE, FALSE) );
							}
						}

					} // end if tomove is WHITE

					continue;
				}// end of checking for KING
				/**********************************************************************
				* this is a KNIGHT, they move in every direction but only once.
				*  
				*/ 

				if ( getPieceAt(x) == KNIGHT )  // add KNIGHT moves
				{
					for( vector = 0; vector < currentposition[x].possiblemoves ; vector++)
					{
						//System.out.println("Generating moves for " + getDescription( x ) + ", vertor = " + vector);
						//System.out.println("first vector is: " + squares[x].movementvectors[vector]);

						if( getPieceAt(x +  currentposition[x].movementvectors[vector]) == _EMPTY)
							CMPUSH(  SIMPLECHESSMOVE( x, x +  currentposition[x].movementvectors[vector]) );
						if( getColorAt(x +  currentposition[x].movementvectors[vector]) == target)
							CMPUSH(  CAPTURECHESSMOVE( x, x +  currentposition[x].movementvectors[vector], TRUE) );
					}
					continue;
				} // end for KNIGHTS
				/************************************************************8
				* the piece is a Bishop, Queen or Rook, they all move 
				* in the same direction as long as they don't go outside the board
				* or find a piece of the same color. If they encounter a piece of
				* the opposite color, the move is added to the stack with move type = CAPTURE.
				*/
				for( vector = 0; vector < currentposition[x].possiblemoves ; vector++)
				{
					//System.out.println("Generating moves for " + getDescription( x ) + ", vertor = " + vector);
					//System.out.println("first vector is: " + squares[x].movementvectors[vector]);
					for(dest = x + currentposition[x].movementvectors[vector]; _EMPTY == getPieceAt( dest ) ; dest += currentposition[x].movementvectors[vector])
					{
						//System.out.println("Generating moves, movementvertors = " + squares[x].movementvectors[vector]);
						CMPUSH(  SIMPLECHESSMOVE( x, dest) );
					}
					if( getColorAt(dest) == target)
						CMPUSH(  CAPTURECHESSMOVE( x, dest, TRUE) );
				} // end for vector...
			} // end if( getColorAt( x ) & tomove
		} // end for loop
	} // end GenerateMoves( )