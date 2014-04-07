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
#define ASSERT //
#endif
//
#define STARTPOS "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"