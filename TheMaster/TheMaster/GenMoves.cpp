/*******************************************************************
* GenerateIntMoves ()
* Generates every move possible from this position taking into account the 
* movement of the pieces.
* 
*/

#include "ChessBoard.h"
#include <vector>

void ChessBoard::GenerateMoves ( void )
{
	Piece tomove = m_boardState.m_bWhitetomove? WHITE:BLACK;
	Piece enemy  = (tomove == WHITE)? BLACK:WHITE;
	
	int vector, x;
	

	// search the board and if the piece at position X is ours, generate the moves
	for(int i = 0; i < 64; i++)
	{	
		x = insideboadonly[i];

		if(  isColor(x,tomove)  )	
		{
			
			/******************************************************************
			* use the movement vectors to determine the possible moves of this piece
			* used for all pieces but only in one direction each for KINGS and KNIGHTS
			*/
			if ( isPawn(x) )  // add PAWN moves
			{
				//add the moves by this pawn to the list
				// first add some variables to reuse this code for BLACK pawns also
				int seventhrank, dir, enpasantrank, secondrank;
				if ( isWhite(x) ) // White pawns move NORTH
				{
					secondrank = 8;
					seventhrank = 3;
					dir = NORTH;
					enpasantrank = 5;
				}
				if ( isBlack(x) )
				{
					secondrank = 3;
					seventhrank = 8;
					dir = SOUTH;
					enpasantrank = 6;
				}  

				if ( Rank(x) == secondrank )
				{
					// setting the enpassantpossible flag to true on these moves
					if( isEmpty (x + dir)  && isEmpty(x + dir + dir) )
						m_movestack.push( CHESSMOVE(x, x + dir + dir, MT_ENPASSANTPOSSIBLE));
						
				}
				if ( Rank(x) == seventhrank ) // if on 7th rank, add promoting moves
				{
					//System.out.println("adding promotion pawn moves" );
					if( isEmpty (x + dir) )
					{
						m_movestack.push( CHESSMOVE(x, x + dir, QUEEN | MT_PROMOTION));
						m_movestack.push( CHESSMOVE(x, x + dir, ROOK | MT_PROMOTION));
						m_movestack.push( CHESSMOVE(x, x + dir, BISHOP | MT_PROMOTION));
						m_movestack.push( CHESSMOVE(x, x + dir, KNIGHT | MT_PROMOTION));
					}
					if( isColor(x + dir  + EAST, enemy) )
					{		
						m_movestack.push( CHESSMOVE(x, x + dir + EAST, QUEEN | MT_PROMOTION | MT_CAPTURE));
						m_movestack.push( CHESSMOVE(x, x + dir + EAST, ROOK | MT_PROMOTION | MT_CAPTURE));
						m_movestack.push( CHESSMOVE(x, x + dir + EAST, BISHOP | MT_PROMOTION | MT_CAPTURE));
						m_movestack.push( CHESSMOVE(x, x + dir + EAST, KNIGHT | MT_PROMOTION | MT_CAPTURE));
					}
					if( isColor(x + dir  + WEST, enemy) )
					{
						m_movestack.push( CHESSMOVE(x, x + dir + WEST, QUEEN | MT_PROMOTION | MT_CAPTURE));
						m_movestack.push( CHESSMOVE(x, x + dir + WEST, ROOK | MT_PROMOTION | MT_CAPTURE));
						m_movestack.push( CHESSMOVE(x, x + dir + WEST, BISHOP | MT_PROMOTION | MT_CAPTURE));
						m_movestack.push( CHESSMOVE(x, x + dir + WEST, KNIGHT | MT_PROMOTION | MT_CAPTURE));
					}
				} //end promoting check
				// this must be a normal pawn move
				else
				{
					//System.out.println("adding the normal pawn moves" );
					if( isEmpty( x + dir ) )
						m_movestack.push( CHESSMOVE(x, x + dir, MT_NORMAL));

					// SEE IF CAN CAPTURE EAST
					if(  isColor(x + dir  + EAST, enemy))
						m_movestack.push( CHESSMOVE(x, x + dir + EAST, MT_NORMAL));
						
					//SEE IF CAN CAPTURE WEST
					if(  isColor(x + dir  + WEST, enemy))
						m_movestack.push( CHESSMOVE(x, x + dir + WEST, MT_NORMAL));
				}
				if (Rank(x) == enpasantrank ) // if on 5th rank, check for EP capture
				{
					if ( isEPPossible(m_boardState.m_LastMove) )
					{
						if ( TO(m_boardState.m_LastMove) == x + WEST )
							m_movestack.push( CHESSMOVE(x, x + dir + WEST, MT_ENPASSANT));
							
						if ( TO(m_boardState.m_LastMove) == x + EAST )
							m_movestack.push( CHESSMOVE(x, x + dir + EAST, MT_ENPASSANT));
					}
				} // end if on 5th rank, check for EP capture

				continue;

			} // end if piece is a PAWN

			/**********************************************************************
			* KINGS, they move in every direction but only once.
			*  Special moves: - cannot move to check
			*                 - castle king side and queenside
			*/ 

			if ( isKing(x)  && isColor(x,tomove) )  // add KING moves
			{
				for( vector = 0; vector < possibleMoves(KING) ; vector++)
				{
					if( isEmpty(x +  kingvectors[vector]) )
						m_movestack.push( CHESSMOVE(x, x + kingvectors[vector] , MT_NORMAL));
					if( isColor(x + kingvectors[vector], enemy))
						m_movestack.push( CHESSMOVE(x, x + kingvectors[vector] , MT_CAPTURE));
				}
				// add castling priviledges
				if ( isWhite(tomove) )
				{
					if ( m_boardState.castling.whiteshort ) 
					{
						//System.out.println("checking white short castle move");
						if ( isEmpty( F1 )  && isEmpty(G1) )       
						{
							if (! (isAttacked(E1 , BLACK) |
								isAttacked( F1, BLACK) | 
								isAttacked( G1, BLACK))   )
							{
								//System.out.println("Adding white short castle move");
								m_movestack.push( CHESSMOVE(E1, G1 , MT_CASTLE));
							}
						}
					}
					if ( m_boardState.castling.whitelong ) 
					{
						if ( isEmpty( D1) && isEmpty( C1) &&  isEmpty( B1)) 
						{
							if ( !(isAttacked( E1, BLACK) |
								isAttacked(  D1, BLACK) | 
								isAttacked(  C1, BLACK))   )
								m_movestack.push( CHESSMOVE(E1, C1 , MT_CASTLE));
						}
					}
				}
				else // adding black castling moves
				{
					if (  m_boardState.castling.blackshort ) 
					{
						if ( isEmpty( F8) && isEmpty(G8 ) )
						{

							if ( !(isAttacked(E8, WHITE) |
								isAttacked(  F8, WHITE) |
								isAttacked(  G8, WHITE))   )
								m_movestack.push( CHESSMOVE(E8, G8 , MT_CASTLE));
						}
					}
					if ( m_boardState.castling.blacklong ) 
					{
						if ( isEmpty(D8) && isEmpty( C8) &&  isEmpty( B8) )
						{

							if ( !(isAttacked( E8, WHITE) |
								isAttacked(  D8, WHITE) | 
								isAttacked(  C8, WHITE))  )
								m_movestack.push( CHESSMOVE(E8, C8 , MT_CASTLE));
						}
					}

				} // end if tomove is WHITE

				continue;
			}// end of checking for KING
			/**********************************************************************
			* this is a KNIGHT, they move in every direction but only once.
			*  
			*/ 

			if ( isKnight(x) && isColor(x,tomove) )  // add KNIGHT moves
			{
				for( vector = 0; vector < possibleMoves(KNIGHT) ; vector++)
				{
					//System.out.println("Generating moves for " + getDescription( x ) + ", vertor = " + vector);
					//System.out.println("first vector is: " + squares[x].movementvectors[vector]);

					if( isEmpty(x +  knightvectors[vector]))
						m_movestack.push( CHESSMOVE(x, x + knightvectors[vector] , MT_NORMAL));
					if( isColor(x + knightvectors[vector], enemy))
						m_movestack.push( CHESSMOVE(x, x + knightvectors[vector] , MT_CAPTURE));
				}
				continue;
			} // end for KNIGHTS
			/************************************************************8
			* 
			*/
			int dest;
			if (isQueen(x) && isColor(x,tomove))
			for( vector = 0; vector <  possibleMoves(QUEEN); vector++)
			{
				for( dest = x + queenvectors[vector]; isEmpty( dest )   ; dest +=  queenvectors[vector])
				{
					m_movestack.push( CHESSMOVE(x, dest , MT_NORMAL));
				}
				if( isColor(dest, enemy))
					m_movestack.push( CHESSMOVE(x, dest , MT_CAPTURE));
					
			} // end 
			if (isBishop(x) && isColor(x,tomove))
			for( vector = 0; vector <  possibleMoves(BISHOP); vector++)
			{
				for( dest = x + bishopvectors[vector]; isEmpty( dest )  ; dest +=  bishopvectors[vector])
				{
					m_movestack.push( CHESSMOVE(x, dest , MT_NORMAL));
				}
				if( isColor(dest, enemy))
					m_movestack.push( CHESSMOVE(x, dest , MT_CAPTURE));
					
			} // end
			if (isRook(x) && isColor(x,tomove))
			for( vector = 0; vector <  possibleMoves(ROOK); vector++)
			{
				for( dest = x + rookvectors[vector]; isEmpty( dest ) ; dest +=  rookvectors[vector])
				{
					m_movestack.push( CHESSMOVE(x, dest , MT_NORMAL));
				}
				if( isColor(dest, enemy))
					m_movestack.push( CHESSMOVE(x, dest , MT_CAPTURE));
					
			} // end
		} // end if( getColorAt( x ) & tomove
	} // end for loop
} // end GenerateMoves( )