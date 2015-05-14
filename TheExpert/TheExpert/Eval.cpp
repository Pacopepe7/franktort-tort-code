#include "ChessPosition.h"
#include "ChessMove.h"
#include "Eval.h"
#include <iostream>
using namespace std; 

int Eval(ChessPosition * board)
{
	ASSERT(board->Materialcount[WHITE] > 0);
	ASSERT(board->Materialcount[BLACK] > 0);
	
	ASSERT(board->Materialcount[WHITE] < 20000);
	ASSERT(board->Materialcount[BLACK] < 20000);

	ASSERT(board->PSQT[WHITE] > -300);
	ASSERT(board->PSQT[BLACK] < 2000);

	ASSERT(board->PSQT[WHITE] > -300);
	ASSERT(board->PSQT[BLACK] < 2000);

	ASSERT(isValidColor(ColorOnMove()));
	ASSERT(isValidColor(ColorNotOnMove()));

	int materialdelta = board->Materialcount[ColorOnMove()] - board->Materialcount[ColorNotOnMove()];
	int psqtabledelta = board->PSQT[ColorOnMove()] - board->PSQT[ColorNotOnMove()];
	
	
	return (materialdelta);// +psqtabledelta);
	return 0;
}