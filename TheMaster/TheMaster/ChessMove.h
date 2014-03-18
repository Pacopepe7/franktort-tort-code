/***************************************************************
* Francisco Tort
* Dec 30, 2009
* ChessMove class creates a move from a pair of coordinates in the board array
* or a string in the form "e2e4[p]" where the first two characters are the 
* coordinates of the square the piece if being moved from, the second two
* characters are the coordinates of the square the piece is being moved to
* and the optional last character is for promotions,   
* */

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
* Piece type       XXXX for promotion
* Value of move         XXXXXXXXXXXXXXXX 16 bits (0-65536) or (-30000-30000)
************************************************************/

#include "definitions.h"

#pragma once
typedef bits unsigned int;

const bits FROM_MASK = (1 | 2 | 4 | 8 | 16 | 32);
const bits TO_MASK	= (FROM_MASK << 6);
const bits CAPTURE_MASK	= (1 << 12);
const bits PROMOTION_MASK = (CAPTURE_MASK << 1);
const bits ENPASSANT_MASK = (PROMOTION_MASK << 1);
const bits CASTLE_MASK = (ENPASSANT_MASK << 1);
const bits ENPASSANTPOSSIBLE_MASK = (CASTLE_MASK << 1);
const bits KNIGHT_MASK	= ( ENPASSANTPOSSIBLE_MASK >> 1);
const bits BISHOP_MASK	= ( KNIGHT_MASK >> 1);
const bits ROOK_MASK	= ( BISHOP_MASK >> 1);
const bits QUEEN_MASK	= ( ROOK_MASK >> 1);

const bits VALUE_MASK = (65535 << 22);

class ChessMove
{ 

private:
	bits m_uiChessMove;
	inline bits from ( void )  { return (m_uiChessMove & FROM_MASK); } ;
	inline bits to   ( void )  { return ((m_uiChessMove & TO_MASK) >> 6 ); } ;

public:
	ChessMove ( );
	ChessMove ( int from, int to );
	ChessMove ( int from, int to , int flags);
	bool isCapture(void) { return (m_uiChessMove & CAPTURE_MASK)? true:false;};
	bool isPromotion(void) { return (m_uiChessMove & PROMOTION_MASK)? true:false;};
	bool isEnPassant(void) { return (m_uiChessMove & ENPASSANT_MASK)? true:false;};
	bool isCastle(void) { return (m_uiChessMove & CASTLE_MASK)? true:false;};
	bool isEnPassantPossible(void) { return (m_uiChessMove & ENPASSANTPOSSIBLE_MASK)? true:false;};
	bool isKnight(void) { return (m_uiChessMove & KNIGHT_MASK)? true:false;};
	bool isBishop(void) { return (m_uiChessMove & BISHOP_MASK)? true:false;};
	bool isRook(void) { return (m_uiChessMove & ROOK_MASK)? true:false;};
	bool isQueen(void) { return (m_uiChessMove & QUEEN_MASK)? true:false;};
	
};// class ChessMove 

