/**********************************************************************************
* Francisco Tort
* Dec 30, 2009
* these are the values for the individual pieces ( plus the empty and Out value)
* The numbers are just bits turned on on an int to make it easy for the program 
* to tell if the piece is a KNIGHT ( and it with KNIGHT value) and color (and it with WHITE etc...)
*/
#pragma once

#define TRUE	 1
#define FALSE	 0

/************************************************
* COLORS
*/
typedef short	Color;

#define WHITE						 0
#define BLACK						 1
#define NOCOLOR						 2

#define COLORS						 2

#define MAXPIECES					 16
#define INVALIDSQUARE				 64		

/************************************************
* PIECES
*/
typedef unsigned __int8		Piece;

#define EMPTY						 0
#define PAWN						 1
#define KNIGHT						 2
#define BISHOP						 4
#define ROOK						 8
#define QUEEN						 16
#define KING						 32

/************************************************
* 0 - 8 : from (8)
* 9- 16 : to (8)
* 17-22 : move type (6)
* 23-30 : data bits ( if ep move, ep square (is never a capture). if capture, captured piece.
* ////25 - 30 : Piece captured (6 - for undoMove)
* /////31-32: 4 options for piece promoted: Q=00,R=01,B=10,N=11
*/
typedef unsigned __int32	ChessMove; 


typedef unsigned __int8		MoveType;

#define MT_NORMAL				 1
#define MT_PROMOTION			 2
#define MT_CAPTURE				 4
#define MT_ENPASSANT			 16			
#define MT_CASTLE				 32
#define MT_ENPASSANTPOSSIBLE	 64

/************************************************
* OTHER TYPES
*/
typedef unsigned __int32	Mask;
typedef unsigned __int8		Square;
typedef __int8				Direction;
typedef __int8				Rank;
typedef __int8				File;
/************************************************/


/****************************************************************
* Directions to move on board ( based on 0x88)
* These are vectors that allow the program to comunicate moves
* and move the piece correctly in the array.
*/
#define  NORTH			(-16)
#define  SOUTH			(16)
#define  EAST			(+1)
#define  WEST			(-1)
#define  NORTHEAST		( NORTH + EAST )
#define  NORTHWEST		( NORTH + WEST )
#define  SOUTHEAST		( SOUTH + EAST )
#define  SOUTHWEST		( SOUTH + WEST )


const int INVALID		=	128;

/************************************************
* MASKS
*/
#define BYTE	 (1 | 2 | 4 | 8 | 16 | 32 | 64 | 128)

enum { A8 =  0, B8, C8, D8, E8, F8, G8, H8,
	   A7 = 16, B7, C7, D7, E7, F7, G7, H7,
	   A6 = 32, B6, C6, D6, E6, F6, G6, H6,
	   A5 = 48, B5, C5, D5, E5, F5, G5, H5,
	   A4 = 64, B4, C4, D4, E4, F4, G4, H4,
	   A3 = 80, B3, C3, D3, E3, F3, G3, H3, 
	   A2 = 96, B2, C2, D2, E2, F2, G2, H2,
	   A1 =112, B1, C1, D1, E1, F1, G1, H1};

