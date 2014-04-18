
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
	Square data =  getDataSquare(cm);
	MoveType mt = getMoveType(cm);

	ASSERT( isSquare(from));
	ASSERT( isSquare(to));
	cout << not(from) << "-" << not(to) << "   " <<  " data: " << (int)data << " Type: " << (int) mt << endl;

}
void ChessGame::PrintMovePlain(ChessMove cm)
{
	Square from = getFromSquare(cm);
	Square to = getToSquare(cm);
	Square data =  getDataSquare(cm);
	MoveType mt = getMoveType(cm);

	ASSERT( isSquare(from));
	ASSERT( isSquare(to));
	cout << not(from) << not(to) << " ";

}