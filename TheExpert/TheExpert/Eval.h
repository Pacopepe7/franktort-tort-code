/***********************************************************************************
* Values and Scores
* Francisco Tort
* March 12, 2015
*/
#include "ChessPosition.h"

//////////////////////////////////////////////////////
//http://chessprogramming.wikispaces.com/Point+Value
//////////////////////////////////////////////////////

#define PAWN_WEIGHT				100
#define KNIGHT_WEIGHT			320
#define BISHOP_WEIGHT			325
#define ROOK_WEIGHT				500
#define QUEEN_WEIGHT			975

#define BISHOPPAIR				50
#define KNIGHTPAIR				25
#define ROOKPAIR				25

#define PAWNON6TH				75
#define PAWNON7TH				150

#define PAWNSON6TH				500

#define EXCHANGE				(ROOK_WEIGHT - BISHOP_WEIGHT)

#define MATE					18000
#define INF						20000

int Eval(ChessPosition * board);