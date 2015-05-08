/***********************************************
* Definitions
***********************************************/
#pragma once

#include <string>
#include <assert.h>
#
using namespace std;

#define STARTPOS "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

/************************************************
* MASKS
*/
#define MAXBOARDARRAY0x88	128
#define MAXMOVELIST			250
#define MAXPIECES			16
#define INVALID			(-1)
#define MAXMOVES		256
#define ATTACKTABLEINDEXOFFSET	260
#define ATTACKTABLEMAX			(ATTACKTABLEINDEXOFFSET * 2)

enum {
	A1 = 0, B1, C1, D1, E1, F1, G1, H1,
	A2 = 8, B2, C2, D2, E2, F2, G2, H2,
	A3 = 16, B3, C3, D3, E3, F3, G3, H3,
	A4 = 24, B4, C4, D4, E4, F4, G4, H4,
	A5 = 32, B5, C5, D5, E5, F5, G5, H5,
	A6 = 40, B6, C6, D6, E6, F6, G6, H6,
	A7 = 48, B7, C7, D7, E7, F7, G7, H7,
	A8 = 56, B8, C8, D8, E8, F8, G8, H8,
};



extern string notation[MAXBOARDARRAY0x88];
extern int movement[64][8][8];
extern int castling[MAXBOARDARRAY0x88];

/* 0x88 math */



#define isSquare(sq)			( (sq & 0x88)? false: true )
#define getRank(sq)				( ( sq >> 4) )
#define getFile(sq)				( ( sq & 7) )
#define sameFile( sq1, sq2)		( ( getFile0x88(sq1) == getFile0x88(sq2))? 0:1 )
#define sameRank( sq1, sq2)		( ( getRank0x88(sq1) == getRank0x88(sq2))? 0:1 )


/************************************************
* Macros
************************************************/
#define KingPos(side)			( KingPosition[side])
#define isSquare(sq)			( (sq & 0x88)? false: true )
#define isPiece(p)				( (p & PIECE) )
#define isEmpty(sq)				( board->Ox88Board[sq] == NULL) 
#define isColor( sq, c)			( Ox88Board[sq]->cColor == c)

#define isOpponent(sq)			( ( (board->Ox88Board[sq]->cColor & ColorNotOnMove())))
#define isOurs(sq)				( ( (board->Ox88Board[sq]->cColor & ColorOnMove())))

#define IsInCheck( )			( isAttacked(board->KingPos(board->sideToMove), ColorNotOnMove()))


#define getRank(sq)				( ( sq >> 4) )
#define getFile(sq)				( ( sq & 7) )

#define MakeSquare(r, c)		( (16 * r) + c)

/*********************************************
* Color related Macros
*********************************************/
#define ColorOnMove()			( board->sideToMove )
#define ColorNotOnMove()		( board->sideToMove == WHITE? BLACK:WHITE )
/*************************************************
* Getters
**************************************************/
#define getColor(sq)			( (board->Ox88Board[sq]->cColor ))
#define getPiece(sq)			( (board->Ox88Board[sq]->pPiece ))

#define Opponent()				( board->sideToMove == WHITE? BLACK:WHITE)



/* Piece movement vectors*/
extern int kingvectors[8];
extern int knightvectors[8];
extern int bishopvectors[8];
extern int rookvectors[8];
extern int queenvectors[8];
extern int whitepawnvectors[4];
extern int blackpawnvectors[4];

#define  NORTH		(16)
#define  SOUTH		(-16)
#define  EAST		(1)
#define  WEST		(-1)
#define  NORTHEAST	( NORTH + EAST )
#define  NORTHWEST	( NORTH + WEST )
#define  SOUTHEAST	( SOUTH + EAST )
#define  SOUTHWEST	( SOUTH + WEST )

/* Typedefines */

typedef int Location;
typedef unsigned __int64 U64;
typedef int Color;
typedef  __int32 ChessMove;

typedef struct {
	ChessMove move[MAXMOVELIST];
	int index;
}MOVELIST;


typedef struct {
	ChessMove	move;
	int			castlingprivileges;
	Location	enpassantsquare;
	int			fiftymoverule;
	U64			positionkey;
} UNMAKEMOVE;

#define NOCOLOR		0
#define BLACK		1
#define WHITE		2
#define MAXCOLOR	3

#define isWhite(c)					( c & WHITE)
#define isBlack(c)					( c & BLACK)
#define getPieceColor(p)			( p & MAXCOLOR)


#define EMPTY		0
#define PAWN		4
#define KNIGHT		8
#define BISHOP		16
#define ROOK		32
#define	QUEEN		64
#define KING		128

#define PIECE (PAWN | KNIGHT | BISHOP | ROOK | QUEEN | KING )

#define WK			(WHITE | KING)
#define WQ			(WHITE | QUEEN)
#define WR			(WHITE | ROOK)
#define WB			(WHITE | BISHOP)
#define WN			(WHITE | KNIGHT)
#define WP			(WHITE | PAWN)

#define BK			(BLACK | KING)
#define BQ			(BLACK | QUEEN)
#define BR			(BLACK | ROOK)
#define BB			(BLACK | BISHOP)
#define BN			(BLACK | KNIGHT)
#define BP			(BLACK | PAWN)

/* Defines for Attack table*/
#define WHITEPAWN12		1
#define BLACKPAWN12		2
#define KNIGHT12		3
#define BISHOP12		4
#define ROOK12			5
#define QUEEN12			6
#define KING12			7
#define EPSQUARE		8
#define MAXPIECES12		9

typedef unsigned int Piece;


#define isSlider(p)		(p & 0x4)

/* Castling privileges */
#define WHITESHORT					1
#define WHITELONG					2
#define BLACKSHORT					4
#define BLACKLONG					8

//Move generation constants

#define MAXQUEENVECTORS		8
#define MAXROOKVECTORS		4
#define MAXBISHOPVECTORS	4
#define MAXKNIGHTVECTORS	8
#define MAXKINGVECTORS		8


/* Functions */
Location MakeSquareFromString(string);
void InitMovementTable(void);
int CountBits(U64 b);

#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed ",#n); \
printf("On %s ",__DATE__); \
printf("At %s ",__TIME__); \
printf("In File %s ",__FILE__); \
printf("At Line %d\n",__LINE__); \
exit(1);}
#endif