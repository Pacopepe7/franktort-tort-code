/***********************************************************************************
* Values and Scores
* Francisco Tort
* March 18, 2014
*/

#include "Definitions.h"

//////////////////////////////////////////////////////
//http://chessprogramming.wikispaces.com/Point+Value
//////////////////////////////////////////////////////

#define PAWN_WEIGHT				100
#define KNIGHT_WEIGHT			320
#define BISHOP_WEIGHT			330
#define ROOK_WEIGHT				525
#define QUEEN_WEIGHT			1000

#define BISHOPPAIR				50
#define KNIGHTPAIR				25
#define ROOKPAIR				25

#define EXCHANGE				(ROOK_WEIGHT - BISHOP_WEIGHT)