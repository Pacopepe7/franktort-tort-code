/**********************************************************************************
* Francisco Tort
Apr 7, 2014
*/
#pragma once

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

#define MAXPIECES					 16

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