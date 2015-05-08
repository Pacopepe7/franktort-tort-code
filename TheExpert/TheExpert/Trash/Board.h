/**
Francisco Tort
Feb 20, 2015

*/
#include <vector>

#include "Pieces.h"

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

 typedef struct Board
{
	Piece * squares[64];
	Piece piecelist[16][2];



} Board_t;