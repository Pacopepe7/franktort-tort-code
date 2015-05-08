#pragma once

#include "ChessPosition.h"
#include "ChessMove.h"


/***********************************************
*
* Thanks http://chessprogramming.wikispaces.com/Bruce+Moreland
***********************************************/
typedef struct LINE {
	int cmove;              // Number of moves in the line.
	ChessMove argmove[50];  // The line.
}   LINE;

