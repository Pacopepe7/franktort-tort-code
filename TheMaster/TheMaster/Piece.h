/**********************************************************************************
* Francisco Tort
* Dec 30, 2009
* these are the values for the individual pieces ( plus the empty and Out value)
* The numbers are just bits turned on on an int to make it easy for the program 
* to tell if the piece is a KNIGHT ( and it with KNIGHT value) and color (and it with WHITE etc...)
*/
#pragma once

/************************************************
* 0 = EMPTY, 1 = BLACK, 2 = WHITE, 4 = PAWN, 8 = KNIGHT, 16 = BISHOP, 32 = ROOK, 64 = QUEEN, 128 = KING
*
*/
typedef unsigned __int8		Piece;

const Piece PAWN						= 0;
const Piece KNIGHT						= 1;
const Piece BISHOP						= 2;
const Piece ROOK						= 3;
const Piece QUEEN						= 4;
const Piece KING						= 5;

