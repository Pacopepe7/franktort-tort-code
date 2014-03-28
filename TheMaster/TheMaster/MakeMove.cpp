
/*******************************************************************
* MakeIntMove (unsigned int)
* Makes the selected move on the board, returns true if this move can actually be made
* false otherwise.
* 
*/
#include "ChessGame.h"
#include <iostream>
using namespace std;

void ChessGame::MakeMove(ChessMove cm)
{
	//assumes the move has been validated! (to do...)
	int our, theirs; // reusable counters
	Square from = getFromSquare(cm);
	Square to = getToSquare(cm);
	Square epsq =  getEPSquare(cm);
	MoveType mt = getMoveType(cm);

	cout << "From: " << (int)from << ", To: " << (int)to << endl;
	//Piece q = getPromotingPiece(cm);
#ifdef _DEBUG
	if ( ! isSquare(from)) 
		return;
	if ( ! isSquare(to))
		return;
#endif
	//Ep moves
	if ( epsq == to)
	{


		return;
	}
	// no capture
	if ( isEmpty(to)) 
	{
		MovePiece(from, to);
		return;
	}
	//Capture
	{

		return;
	}


	/************************************************/
	//Update move info

	state.m_bWhitetomove = state.m_bWhitetomove? false: true;

	if ( mt != MT_CAPTURE )
				state.fiftymoverule ++;
	state.m_LastMove = cm;
	state.ply++;

}