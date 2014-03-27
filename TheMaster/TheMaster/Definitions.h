/**********************************************************************************
* Francisco Tort
* Dec 30, 2009
* these are the values for the individual pieces ( plus the empty and Out value)
* The numbers are just bits turned on on an int to make it easy for the program 
* to tell if the piece is a KNIGHT ( and it with KNIGHT value) and color (and it with WHITE etc...)
*/
#pragma once

const unsigned int TRUE	= 1;
const unsigned int FALSE= 0;

/************************************************
* COLORS
*/
typedef short	Color;
const Color WHITE						= 0;
const Color BLACK						= 1;
const Color NOCOLOR						= 2;

const Color COLORS						= 2;

const short MAXPIECES					= 16;
const short INVALIDSQUARE				= 64;		
/************************************************
* PIECES
*/
typedef unsigned __int8		Piece;

const Piece EMPTY						= 0;
const Piece PAWN						= 1; 
const Piece KNIGHT						= 2;
const Piece BISHOP						= 4;
const Piece ROOK						= 8;
const Piece QUEEN						= 16;
const Piece KING						= 32;

/************************************************
* 0 - 6 : from (6)
* 7- 12 : to (6)
* 13-18 : move type (6)
* 19-24 : en Passant Square (6)
* 25 - 30 : Piece captured (6 - for undoMove)
* 31-32: 4 options for piece promoted: Q=00,R=01,B=10,N=11
*/
typedef unsigned __int32	ChessMove; 


typedef unsigned __int8		MoveType;

const MoveType MT_ENPASSANTPOSSIBLE		= 1;
const MoveType MT_PROMOTION				= 2;
const MoveType MT_CAPTURE				= 4;
const MoveType MT_NORMAL				= 8;					
const MoveType MT_ENPASSANT				= 16;			
const MoveType MT_CASTLE				= 32;

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
const Direction  NORTH		=	16;
const Direction  SOUTH		=  -16;
const Direction  EAST		=	1;
const Direction  WEST		=	-1;
const Direction  NORTHEAST	=	( NORTH + EAST );
const Direction  NORTHWEST	=	( NORTH + WEST );
const Direction  SOUTHEAST	=	( SOUTH + EAST );
const Direction  SOUTHWEST	=	( SOUTH + WEST );


const int INVALID		=	128;

/*****************************************/
#define POSSIBLEMOVESKING 8
#define POSSIBLEMOVESKNIGHT 8
#define POSSIBLEMOVESROOK 4
#define POSSIBLEMOVESBISHOP 4
#define POSSIBLEMOVESQUEEN 8

/************************************************
* MASKS
*/
const Mask BOTTOM6BITS	= (1 | 2 | 4 | 8 | 16 | 32);

enum { A1 =  0, B1, C1, D1, E1, F1, G1, H1,
	   A2 = 16, B2, C2, D2, E2, F2, G2, H2,
	   A3 = 32, B3, C3, D3, E3, F3, G3, H3,
	   A4 = 48, B4, C4, D4, E4, F4, G4, H4,
	   A5 = 64, B5, C5, D5, E5, F5, G5, H5,
	   A6 = 80, B6, C6, D6, E6, F6, G6, H6, 
	   A7 = 96, B7, C7, D7, E7, F7, G7, H7,
	   A8 =112, B8, C8, D8, E8, F8, G8, H8};


