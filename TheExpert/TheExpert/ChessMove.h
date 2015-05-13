#pragma once
/***************************************************************
* Francisco Tort
/************************************************
* 0000 0000 0000 0000 0000 1111 1111 : from (8)
* 0000 0000 0000 1111 1111 0000 0000 : to (8)
* 0000 0001 1111 0000 0000 0000 0000 : captured Piece (qrbnp).
* 0001 1110 0000 0000 0000 0000 0000 : Promoted Piece (qrbn).
* 0010 0000 0000 0000 0000 0000 0000 : EP_Possible 0x2000000
* 0100 0000 0000 0000 0000 0000 0000 : EP_CAPTURE  0x4000000
* 1000 0000 0000 0000 0000 0000 0000 : Castle flag 0x8000000
****************************************************************/
#include "chess.h"

using namespace std;

 
#define KNIGHT_FLAG					1
#define BISHOP_FLAG					2
#define ROOK_FLAG					4
#define QUEEN_FLAG					8
#define PAWN_FLAG					16

#define SQUAREMASK					(0x00000FF)
#define CAPTUREDPIECEMASK			(0x000001F)
#define PROMOTIONPIECEMASK			(0x000000F)

#define MT_ENPASSANTPOSSIBLE		(0x2000000)
#define MT_EPCAPTURE				(0x4000000)
#define MT_CASTLE					(0x8000000)

#define FromSquare(cm)				(cm & SQUAREMASK)
#define ToSquare(cm)				( (cm >> 8) & SQUAREMASK)
#define Capture(cm)					( (cm >> 16) & CAPTUREDPIECEMASK)
#define Promotion(cm)				( (cm >> 21) & PROMOTIONPIECEMASK)
#define EPPossible(cm)				( (cm & MT_ENPASSANTPOSSIBLE))
#define EPCapture(cm)				( (cm & MT_EPCAPTURE))
#define Castle(cm)					( (cm & MT_CASTLE))



#define CM(from, to, CapPiece, ProPiece, flag)		\
(( from | ((to << 8)) |\
((CapPiece << 16))    |\
((ProPiece << 21))    |\
(flag)))

#define GetMoveFrom(list)				( list.move[--list.index])				
#define MovesStillLeft(list)			(list.index != -1)

ChessMove MakeMoveFromString(string move);
string MakeMoveString(ChessMove cm);



