
/*******************************************************************
* MakeIntMove (unsigned int)
* Makes the selected move on the board, returns true if this move can actually be made
* false otherwise.
* 
*/
#include "ChessGame.h"
#include <iostream>
using namespace std;

string ChessGame::not(Square sq)
{
	ASSERT( isSquare(sq));
	return notation[sq];
}
void ChessGame::PrintMove(ChessMove cm)
{
	Square from = getFromSquare(cm);
	Square to = getToSquare(cm);
	//cout << (int) from << " " << (int) to << endl;
	ASSERT( isSquare(from));
	ASSERT( isSquare(to));
	cout << not(from) << "-" << not(to) << "   " << endl;

}