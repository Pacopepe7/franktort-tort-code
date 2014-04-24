/**********************************************************************************
* Francisco Tort
* Apr 7, 2014
*/


#define TRUE	 1
#define FALSE	 0

#define FORWARD						 1
#define BACK						(-1)

#define MAXPIECES					 16
#define INVALIDSQUARE				 64		

/***********************************************/
#define NONE					0
#define SHORT					1
#define LONG					2
#define BOTH					3
/************************************************
* OTHER TYPES
*/
typedef unsigned __int32	Mask;
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



/************************************************
* MASKS
*/
#define MAXBOARDARRAY	128
#define INVALID			(-1)
#define MAXMOVES		250
#define ATTACKTABLEINDEXOFFSET	260
#define ATTACKTABLEMAX			(ATTACKTABLEINDEXOFFSET * 2)

//#undef NDEBUG
#ifdef _DEBUG
#define ASSERT assert
#else
#define ASSERT /********/
#endif

#define STARTPOS "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

/************************************************
* Macros
************************************************/
#define KingPos(side)			( state[ply].king[side])
#define isSquare(sq)			( (sq & 0x88)? false: true )
#define isEmpty(sq)				( Ox88Board[sq] == NULL) 
#define isColor( sq, c)			( Ox88Board[sq]->color == c)

#define isOpponent(sq)			( ( (isEmpty(sq) )? 0 : (Ox88Board[sq]->color == opp)))
#define isOurs(sq)				( ( (isEmpty(sq) )? 0 : (Ox88Board[sq]->color == ctm)))

#define IsInCheck( )			( isAttacked(KingPos(ctm), opp))

#define sameFile( sq1, sq2)		( ( getFile(sq1) == getFile(sq2))? 0:1 )
#define sameRank( sq1, sq2)		( ( getRank(sq1) == getRank(sq2))? 0:1 )
#define getRank(sq)				( ( sq >> 4) )
#define getFile(sq)				( ( sq & 7) )

#define MakeSquare(r, c)		( 16 * r + c)

/*********************************************
* Color related Macros
*********************************************/
#define ColorOnMove()			( ctm )
#define ColorNotOnMove()		( opp )
/*************************************************
* Getters
**************************************************/
#define getColor(sq)			( ( (Ox88Board[sq] == NULL )? NOCOLOR :(Ox88Board[sq]->color )))
#define getPiece(sq)			( ( (Ox88Board[sq] == NULL) ? EMPTY : Ox88Board[sq]->piece ))



