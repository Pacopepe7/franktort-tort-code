/***************************************************************
* Francisco Tort
/************************************************
* 0 - 8 : from (8)
* 9- 16 : to (8)
* 17-22 : move type (6)
* 23-30 : data bits ( if ep move, ep square (is never a capture). if capture, captured piece.
* ////25 - 30 : Piece captured (6 - for undoMove)
* /////31-32: 4 options for piece promoted: Q=00,R=01,B=10,N=11
*/

#pragma once;

typedef unsigned __int32	ChessMove; 

typedef unsigned __int8		MoveType;

#define MT_NORMAL				 1
#define MT_PROMOTION			 2
#define MT_CAPTURE				 4
#define MT_ENPASSANT			 16			
#define MT_CASTLE				 32
#define MT_ENPASSANTPOSSIBLE	 64
#define MT_PAWNPUSH				128

// PROMOTION/CAPTURE encode/decode in a single byte
#define KNIGHT_CAP					1
#define BISHOP_CAP					2
#define ROOK_CAP					4
#define QUEEN_CAP					8

#define KNIGHT_PRO					16
#define BISHOP_PRO					32
#define ROOK_PRO					64
#define QUEEN_PRO					128

#define BYTE	 (1 | 2 | 4 | 8 | 16 | 32 | 64 | 128)

#define isCapture(cm)				(( getMoveType(cm) == MT_PAWNPUSH))

#define isPawnPush(cm)				(( getMoveType(cm) == MT_CAPTURE))
#define getMoveType(cm )			( ( ( cm >> 16) & BYTE) )
#define getDataSquare(cm)			(( ( cm >> 24) & BYTE))
#define getFromSquare(cm)			( (cm & BYTE) )
#define getToSquare(cm)				( ( ( cm >> 8) & BYTE) )

#define getCapture(p)			( (p & (KNIGHT_CAP | BISHOP_CAP | ROOK_CAP | QUEEN_CAP)) << 1)
#define getPromotion(p)			( ( p & (KNIGHT_PRO | BISHOP_PRO | ROOK_PRO | QUEEN_PRO) ) >> 3)
#define SetCapturePromotion(capture, promotion)	( ( capture >> 1) | ( promotion << 3) )
	


