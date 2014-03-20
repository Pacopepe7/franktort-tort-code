/***********************************************************************************
* Values and Scores
* Francisco Tort
* March 18, 2014
*/

#include "Definitions.h"

typedef  unsigned int score;

//////////////////////////////////////////////////////
//http://chessprogramming.wikispaces.com/Point+Value
//////////////////////////////////////////////////////

score PAWN_WEIGHT		= 100;
score KNIGHT_WEIGHT		= 350;
score BISHOP_WEIGHT		= 350;
score ROOK_WEIGHT		= 525;
score QUEEN_WEIGHT		= 1000;


static int PSQT_WP[64];
//static int PSQT_BP[64];

static int PSQT_N[64];
static int PSQT_B[64];
static int PSQT_R[64];
static int PSQT_Q[64];
static int PSQT_K[64];