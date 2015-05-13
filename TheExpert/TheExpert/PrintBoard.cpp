#include "ChessPosition.h"
#include "utils.h"

#include <iostream>

using namespace std;

void PrintBoard(const ChessPosition * board)
{
	ASSERT(board);
	cout << "---------------------------------------------------------" << endl;
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
			if ((getPiece(MakeSquare(r, c)) | getColor(MakeSquare(r, c))) == WP)
				cout << "P";
			if ((getPiece(MakeSquare(r, c)) | getColor(MakeSquare(r, c))) == WN)
				cout << "N";
			if ((getPiece(MakeSquare(r, c)) | getColor(MakeSquare(r, c))) == WB)
				cout << "B";
			if ((getPiece(MakeSquare(r, c)) | getColor(MakeSquare(r, c))) == WR)
				cout << "R";
			if ((getPiece(MakeSquare(r, c)) | getColor(MakeSquare(r, c))) == WQ)
				cout << "Q";
			if ((getPiece(MakeSquare(r, c)) | getColor(MakeSquare(r, c))) == WK)
				cout << "K";
			if ((getPiece(MakeSquare(r, c)) | getColor(MakeSquare(r, c))) == BP)
				cout << "p";
			if ((getPiece(MakeSquare(r, c)) | getColor(MakeSquare(r, c))) == BN)
				cout << "n";
			if ((getPiece(MakeSquare(r, c)) | getColor(MakeSquare(r, c))) == BB)
				cout << "b";
			if ((getPiece(MakeSquare(r, c)) | getColor(MakeSquare(r, c))) == BR)
				cout << "r";
			if ((getPiece(MakeSquare(r, c)) | getColor(MakeSquare(r, c))) == BQ)
				cout << "q";
			if ((getPiece(MakeSquare(r, c)) | getColor(MakeSquare(r, c))) == BK)
				cout << "k";
		}
		cout << endl;
	}
	cout << "On move : " << ((board->sideToMove == WHITE) ? "WHITE" : "BLACK") << endl;
	
	cout << "White king at : " << notation[board->KingPosition[WHITE]] << endl;
	cout << "Black king at : " << notation[board->KingPosition[BLACK]] << endl;

	if ( board->historyply > 0)
	for (r = 0; r < board->historyply; r++)
		cout << MakeMoveString(board->unmake[r].move) << " ";
	cout << endl;
	cout << "Castling string: " <<
		((board->castlingprivileges & WHITESHORT) ? "K" : "") << 
		((board->castlingprivileges & WHITELONG) ? "Q" : "") << 
		((board->castlingprivileges & BLACKSHORT) ? "k" : "") <<
		((board->castlingprivileges & BLACKLONG) ? "q" : "")
		<< endl;
	cout << "EP Square " << ((board->enpassantsquare == INVALID) ? "na":notation[board->enpassantsquare]) << endl;
	//cout << "Key: " << board->positionkey << endl;
	printf("Key:%llX\n", board->positionkey);
	//cout << "PSQT for Black: " << psqtCount[BLACK] << endl;
	cout << "MaxPieces WHITE: " << board->numPieces[WHITE] << endl;
	cout << "MaxPieces BLACK: " << board->numPieces[BLACK] << endl;
}