#pragma once
/***************************************************************
* Francisco Tort
/************************************************
* 0000 0000 0000 0000 0000 1111 1111 : from (8)
* 0000 0000 0000 1111 1111 0000 0000 : to (8)
* 0000 0001 1111 0000 0000 0000 0000 : captured Piece (pnbrq).
* 0001 1110 0000 0000 0000 0000 0000 : Promoted Piece (nbrq).
* 0010 0000 0000 0000 0000 0000 0000 : EP_Possible 0x2000000
* 0100 0000 0000 0000 0000 0000 0000 : Castle flag 0x4000000
* 1000 0000 0000 0000 0000 0000 0000 : Not used.   0x8000000 
****************************************************************/
#include "chess.h"

using namespace std;

 
#define KNIGHT_FLAG					1
#define BISHOP_FLAG					2
#define ROOK_FLAG					4
#define QUEEN_FLAG					8
#define PAWN_FLAG					16

#define SQUAREMASK					(0xFF)
#define CAPTUREDPIECEMASK			(0x1F)
#define PROMOTIONPIECEMASK			(0x0F)

#define FromSquare(cm)				(cm & SQUAREMASK)
#define ToSquare(cm)				( (cm >> 8) & SQUAREMASK)
#define Capture(cm)					( (cm >> 16) & CAPTUREDPIECEMASK)
#define Promotion(cm)				( (cm >> 21) & PROMOTIONPIECEMASK)

#define MT_ENPASSANTPOSSIBLE		(0x2000000)
#define MT_CASTLE					(0x4000000)

#define CM(from, to, CapPiece, ProPiece, flag)		\
(( from | ((to << 8)) |\
((CapPiece << 16))    |\
((ProPiece << 21))    |\
(flag)))

#define GetMoveFrom(list)				( list.move[--list.index])				
#define MovesStillLeft(list)			(list.index != -1)

ChessMove MakeMoveFromString(string move);
string MakeMoveString(ChessMove cm);



