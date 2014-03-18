/***********************************************************************************
* Values and Scores
* Francisco Tort
* March 18, 2014
*/

#include "Definitions.h"

typedef scores unsigned int;

score PAWN_WEIGTH		= 100;
score KNIGHT_WEIGHT		= 300;
score BISHOP_WEIGHT		= 325;
score ROOK_WEIGHT		= 500;
score QUEEN_WEIGHT		= 900;

struct eval_scores_t{
	score BISHOP_PAIR		= 50;
	score KNIGHT_PAIR		= 20;
	} evalscores;




