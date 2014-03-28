
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
	if ( ! isSquare(sq))
		return "ERROR!!!";
	return notation[sq];

}
void ChessGame::PrintMove(ChessMove cm)
{
	Square from = getFromSquare(cm);
	Square to = getToSquare(cm);

	cout << not(from) << "-" << not(to) << "   ";

}