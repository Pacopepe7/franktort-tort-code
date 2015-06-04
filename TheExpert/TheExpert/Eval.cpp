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
	int pawnpos;
	int pawnshelter = 0;
	int stm = board->sideToMove;
	int materialdelta = 0;
	int psqtabledelta = 0;
	//pawnpos = board->KingPosition[stm] + pawndirection[stm];
	//	if (isSquare(pawnpos) && !isEmpty(pawnpos))
	//		pawnshelter += 5;
	//	pawnpos = board->KingPosition[stm] + pawndirection[stm] + EAST;
	//	if (isSquare(pawnpos) && !isEmpty(pawnpos))
	//		pawnshelter += 5;
	//	pawnpos = board->KingPosition[stm] + pawndirection[stm] + WEST;
	//	if (isSquare(pawnpos) && !isEmpty(pawnpos))
	//		pawnshelter += 5;


	materialdelta = board->Materialcount[ColorOnMove()] - board->Materialcount[ColorNotOnMove()];
	//psqtabledelta = board->PSQT[ColorOnMove()] - board->PSQT[ColorNotOnMove()];
	
	
	return (materialdelta + psqtabledelta + pawnshelter);
	
}