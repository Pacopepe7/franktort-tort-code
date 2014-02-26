/**********************************************************************************
* Francisco Tort
* Dec 30, 2009
* these are the values for the individual pieces ( plus the empty and Out value)
* The numbers are just bits turned on on an int to make it easy for the program 
* to tell if the piece is a KNIGHT ( and it with KNIGHT value) and color (and it with WHITE etc...)
*/
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

const int  _EMPTY	=	0;  
const int  BLACK	=	1;
const int  WHITE	=	2;
const int  PAWN		=	4;
const int  KNIGHT	=	8;
const int  BISHOP	=	16;
const int  ROOK		=	32;
const int  QUEEN	=	64;
                    
const int  KING		=	128;
const int  _OUT		=	(KING | QUEEN); 

/* For move type of board & move type on move */
const int  NORMAL		= 0;                    // this move is just a normal move
const int  WHITESHORT	=	1;                  // if this bit is set, white can castle short
const int  WHITELONG	=	2;                  // if this bit is set, white can castle long
const int  BLACKSHORT	=	4;                  // if this bit is set, black can castle short
const int  BLACKLONG	=	8;                  // if this bit is set, black can castle long
const int  CHECK		=	16;                 // This move is a check
const int  CAPTURE		=	32;                 // this move is a capture
const int  ENPASSANT	=	64;                 // this move is a en passant capture
const int  PAWNIN7TH	=	128;                // this move pushes a pawn to the seventh
const int  MT_QUEEN		=	256;                // move type QUEEN
const int  MT_ROOK		=	512;                // move type ROOK
const int  MT_BISHOP	=	1024;               // move type BISHOP
const int  MT_KNIGHT	=	2048;               // move type KNIGHT
const int  MT_PROMOTION	=	4096;               // move type PROMOTION

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
const int INVALID		=	-1;
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


#endif

