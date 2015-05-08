#include "ChessPosition.h"
#include "utils.h"

#include <iostream>

using namespace std;

void PrintBoard(ChessPosition * board)
{
	ASSERT(board);
	int r, c;
	for (r = 0; r < 8; r++){
		for (c = 0; c < 8; c++){
			if (!isSquare(MakeSquare(r, c)))
				continue;
			if (isEmpty(MakeSquare(r, c))){
				cout << " ";
				continue;
			}
				
			//if (board->Ox88Board[MakeSquare(r, c) == NULL])
			//	cout << ".";
			if (board->Ox88Board[MakeSquare(r, c)]->pPiece == WP)
				cout << "P";
			if (board->Ox88Board[MakeSquare(r, c)]->pPiece == WN)
				cout << "N";
			if (board->Ox88Board[MakeSquare(r, c)]->pPiece == WB)
				cout << "B";
			if (board->Ox88Board[MakeSquare(r, c)]->pPiece == WR)
				cout << "R";
			if (board->Ox88Board[MakeSquare(r, c)]->pPiece == WQ)
				cout << "Q";
			if (board->Ox88Board[MakeSquare(r, c)]->pPiece == WK)
				cout << "K";
			if (board->Ox88Board[MakeSquare(r, c)]->pPiece == BP)
				cout << "p";
			if (board->Ox88Board[MakeSquare(r, c)]->pPiece == BN)
				cout << "n";
			if (board->Ox88Board[MakeSquare(r, c)]->pPiece == BB)
				cout << "b";
			if (board->Ox88Board[MakeSquare(r, c)]->pPiece == BR)
				cout << "r";
			if (board->Ox88Board[MakeSquare(r, c)]->pPiece == BQ)
				cout << "q";
			if (board->Ox88Board[MakeSquare(r, c)]->pPiece == BK)
				cout << "k";
		}
		cout << endl;
	}
	cout << "On move : " << ((board->sideToMove == WHITE)? "WHITE":"BLACK") << endl;
	cout << "---------------------------------------------------------" << endl;
	//cout << "White king at : " << not(state[ply].king[WHITE]) << endl;
	//cout << "Black king at : " << not(state[ply].king[BLACK]) << endl;
	//cout << "Material for White: " << materialCount[WHITE] << endl;
	//cout << "Material for Black: " << materialCount[BLACK] << endl;
	//cout << "PSQT for White: " << psqtCount[WHITE] << endl;
	//cout << "PSQT for Black: " << psqtCount[BLACK] << endl;
	//cout << "MaxPieces WHITE: " << maxpieces[WHITE] << endl;
	//cout << "MaxPieces BLACK: " << maxpieces[BLACK] << endl;
}