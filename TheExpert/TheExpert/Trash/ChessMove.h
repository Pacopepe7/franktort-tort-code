/**
Francisco Tort
Feb 20, 2015

*/
/***************************************************************
* Francisco Tort
/***************************************************************/
#include "Color.h"
#include "Pieces.h"

#pragma once;


#define MT_NORMAL				 1
#define MT_PROMOTION			 2
#define MT_CAPTURE				 4
#define MT_ENPASSANT			 16			
#define MT_CASTLE				 32
#define MT_ENPASSANTPOSSIBLE	 64
#define MT_PAWNPUSH				128

typedef struct
{
	short int from;
	short int to;
	short int movetype;
	Piece capturedpiece;
	Piece promotionpiece;

} ChessMove;




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
#define PIECEMASK (2 | 4 | 8 | 16 )

#define isCapture(cm)				(( getMoveType(cm) & MT_CAPTURE))
#define isPromotion(cm)				(( getMoveType(cm) == MT_PROMOTION))
#define isPawnPush(cm)				(( getMoveType(cm) == MT_PAWNPUSH))
#define isPromotionCapture(cm)		(( getMoveType(cm) == ( MT_PROMOTION | MT_CAPTURE)))
#define getMoveType(cm )			( ( ( cm >> 16) & BYTE) )
#define getDataSquare(cm)			(( ( cm >> 24) & BYTE))
#define getFromSquare(cm)			( (cm & BYTE) )
#define getToSquare(cm)				( ( ( cm >> 8) & BYTE) )

#define getCapture(p)			( (p >> 3) & PIECEMASK)
#define getPromotion(p)			( (p << 1) & PIECEMASK)
#define SetCapturePromotion(capture, promotion)	( ( capture << 3) | ( promotion >> 1) )



