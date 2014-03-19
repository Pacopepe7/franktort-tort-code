/**********************************************************************************
* Francisco Tort
* Dec 30, 2009
* these are the values for the individual pieces ( plus the empty and Out value)
* The numbers are just bits turned on on an int to make it easy for the program 
* to tell if the piece is a KNIGHT ( and it with KNIGHT value) and color (and it with WHITE etc...)
*/
#pragma once

/************************************************/

typedef unsigned int Piece;
typedef  unsigned int ChessMove;

const unsigned int TRUE	= 1;
const unsigned int FALSE= 0;
const Piece BLACK		= 1;
const Piece WHITE		= 2;
const Piece COLOR_MASK	= (WHITE | BLACK);




const Piece PAWN				= 1 << 4;
const Piece KNIGHT				= PAWN << 1;
const Piece BISHOP				= KNIGHT << 1;
const Piece ROOK				= BISHOP << 1;
const Piece QUEEN				= ROOK << 1;
const Piece KING				= QUEEN << 1;
const Piece OUT					= KING << 1;
const Piece EMPTY				= OUT << 1;
const Piece MT_ENPASSANTPOSSIBLE = EMPTY << 1;
const Piece MT_PROMOTION		= MT_ENPASSANTPOSSIBLE << 1;
const Piece MT_CAPTURE			= MT_PROMOTION << 1;
const Piece MT_NORMAL			= MT_CAPTURE << 1;						// this move is just a normal move
const Piece MT_ENPASSANT		= MT_NORMAL << 1;						// this move is a en passant capture
const Piece MT_CASTLE			= MT_ENPASSANT << 1;



const Piece FROM_MASK		= (1 | 2 | 4 | 8 | 16 | 32);
const Piece TO_MASK	= (FROM_MASK << 6);
const Piece PIECE_MASK	= (PAWN | KNIGHT | BISHOP | ROOK | QUEEN | KING | OUT | EMPTY);
const Piece BP			=  ( BLACK | PAWN);
const Piece BR			=  ( BLACK | ROOK);
const Piece BN			=  ( BLACK | KNIGHT);
const Piece BB			=  ( BLACK | BISHOP);
const Piece BQ			=  ( BLACK | QUEEN);
const Piece BK			=  ( BLACK | KING);

const Piece WP			=  ( WHITE | PAWN);
const Piece WR			=  ( WHITE | ROOK);
const Piece WN			=  ( WHITE | KNIGHT);
const Piece WB			=  ( WHITE | BISHOP);
const Piece WQ			=  ( WHITE | QUEEN);
const Piece WK			=  ( WHITE | KING);

/* Directions to move on board ( based on a 12 square wide board representation)
* These are vectors that allow the program to comunicate moves
* and move the piece correctly in the array.
*/
const int  NORTH		=	-12;
const int  SOUTH		=	12;
const int  EAST			=	1;
const int  WEST			=	-1;
const int  NORTHEAST	 =	( NORTH + EAST );
const int  NORTHWEST	 =	( NORTH + WEST );
const int  SOUTHEAST	=	( SOUTH + EAST );
const int  SOUTHWEST	=	( SOUTH + WEST );
const int NOTATIONMAX	=	144;
const int MAXSQUARES	=	144;
const int NOTATIONMIN	=	0;
const int COMPMIN		=   16  ;
const int COMPMAX		=   144 - 16;
const int INVALID		=	-1;

/*****************************************/
#define POSSIBLEMOVESKING 8
#define POSSIBLEMOVESKNIGHT 8
#define POSSIBLEMOVESROOK 4
#define POSSIBLEMOVESBISHOP 4
#define POSSIBLEMOVESQUEEN 8

const int A8 = 26;
const int B8 = 27;
const int C8 = 28;
const int D8 = 29;
const int E8 = 30;
const int F8 = 31;
const int G8 = 32;
const int H8 = 33;

const int A7 = 38;
const int B7 = 39;
const int C7 = 40;
const int D7 = 41;
const int E7 = 42;
const int F7 = 43;
const int G7 = 44;
const int H7 = 45;

const int A6 = 50;
const int B6 = 51;
const int C6 = 52;
const int D6 = 53;
const int E6 = 54;
const int F6 = 55;
const int G6 = 56;
const int H6 = 57;

const int A5 = 62;
const int B5 = 63;
const int C5 = 64;
const int D5 = 65;
const int E5 = 66;
const int F5 = 67;
const int G5 = 68;
const int H5 = 69;

const int A4 = 74;
const int B4 = 75;
const int C4 = 76;
const int D4 = 77;
const int E4 = 78;
const int F4 = 79;
const int G4 = 80;
const int H4 = 81;

const int A3 = 86;
const int B3 = 87;
const int C3 = 88;
const int D3 = 89;
const int E3 = 90;
const int F3 = 91;
const int G3 = 92;
const int H3 = 93;

const int A2 = 98;
const int B2 = 99;
const int C2 = 100;
const int D2 = 101;
const int E2 = 102;
const int F2 = 103;
const int G2 = 104;
const int H2 = 105;

const int A1 = 110;
const int B1 = 111;
const int C1 = 112;
const int D1 = 113;
const int E1 = 114;
const int F1 = 115;
const int G1 = 116;
const int H1 = 117;

/*
/* codes for promotion values 
 static const int  KNIGHT=	8;
 static const int  BISHOP=	16;
 static const int  ROOK=	32;
 static const int  QUEEN=	64;
 // For move type of board & move type on move 
 static const int  NORMAL = 0;                      // this move is just a normal move
 static const int  WHITESHORT	=	1;                  // if this bit is set, white can castle short
 static const int  WHITELONG	=	2;                   // if this bit is set, white can castle long
 static const int  BLACKSHORT	=	4;                  // if this bit is set, black can castle short
 static const int  BLACKLONG	=	8;                   // if this bit is set, black can castle long
 static const int  CHECK		=	16;                     // This move is a check
 static const int  CAPTURE	=	32;                    // this move is a capture
 static const int  ENPASSANT	=	64;                  // this move is a en passant capture
 static const int  PAWNIN7TH	=	128;                 // this move pushes a pawn to the seventh
 static const int  MT_QUEEN	=	256;                  // move type QUEEN
 static const int  MT_ROOK	=	512;                   // move type ROOK
 static const int  MT_BISHOP	=	1024;                // move type BISHOP
 static const int  MT_KNIGHT	=	2048;                // move type KNIGHT
 static const int  MT_PROMOTION	=	4096;             // move type PROMOTION
 */



 /**********************************************************************************
  * 
  * these are the values for the individual pieces ( plus the empty and Out value)
  * The numbers are just bits turned on on an int to make it easy for the program 
  * to tell if the piece is a KNIGHT ( and it with KNIGHT value) and color (and it with WHITE etc...)
  

 static const int  BLACK=	1;
 static const int  WHITE=	2;
 static const int  PAWN=	4;
 static const int  KNIGHT=	8;
 static const int  BISHOP=	16;
 static const int  ROOK=	32;
 static const int  QUEEN=	64;
 static const int  _EMPTY =  0;                      
 static const int  KING=	128;
 static const int  _OUT=		(KING | QUEEN); 
 
 /* For move type of board & move type on move 
 const int  NORMAL = 0;                      // this move is just a normal move
 const int  WHITESHORT	=	1;                  // if this bit is set, white can castle short
 const int  WHITELONG	=	2;                   // if this bit is set, white can castle long
 const int  BLACKSHORT	=	4;                  // if this bit is set, black can castle short
 const int  BLACKLONG	=	8;                   // if this bit is set, black can castle long
 const int  CHECK		=	16;                     // This move is a check
 const int  CAPTURE	=	32;                    // this move is a capture
 const int  ENPASSANT	=	64;                  // this move is a en passant capture
 const int  PAWNIN7TH	=	128;                 // this move pushes a pawn to the seventh
 const int  MT_QUEEN	=	256;                  // move type QUEEN
 const int  MT_ROOK	=	512;                   // move type ROOK
 const int  MT_BISHOP	=	1024;                // move type BISHOP
 const int  MT_KNIGHT	=	2048;                // move type KNIGHT
 const int  MT_PROMOTION	=	4096;             // move type PROMOTION

 /* Directions to move on board ( based on a 12 square wide board representation)
  * These are vectors that allow the program to comunicate moves
  * and move the piece correctly in the array.
  
 static const int  NORTH=	-12;
 static const int  SOUTH=	12;
 static const int  EAST=	1;
 static const int  WEST=	-1;
 static const int  NORTHEAST =	( NORTH + EAST );
 static const int  NORTHWEST =	( NORTH + WEST );
 static const int  SOUTHEAST =	( SOUTH + EAST );
 static const int  SOUTHWEST =	( SOUTH + WEST );
*/


