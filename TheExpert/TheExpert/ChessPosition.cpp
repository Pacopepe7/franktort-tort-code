#include "ChessPosition.h"
#include "utils.h"

#include <vector>




void InitializeBoard(ChessPosition * board)
{
	ASSERT(board);

	int i;
	for (i = 0; i < MAXBOARDARRAY0x88; i++)
		board->Ox88Board[i] = NULL;
	for (i = 0; i < MAXPIECES; i++){
		board->pieces[i][WHITE].pPiece = EMPTY;
		board->pieces[i][WHITE].cColor = NOCOLOR;
		board->pieces[i][WHITE].lLocation = INVALID;
		board->pieces[i][WHITE].nextPiece = INVALID;
		board->pieces[i][WHITE].PreviousPiece = INVALID;

		board->pieces[i][BLACK].pPiece = EMPTY;
		board->pieces[i][BLACK].cColor = NOCOLOR;
		board->pieces[i][BLACK].lLocation = INVALID;
		board->pieces[i][BLACK].nextPiece = INVALID;
		board->pieces[i][BLACK].PreviousPiece = INVALID;
	}
	board->KingPosition[WHITE] = INVALID;
	board->KingPosition[BLACK] = INVALID;
	board->numPieces[WHITE] = 0;
	board->numPieces[BLACK] = 0;

	board->sideToMove = NOCOLOR;
	board->Movenum = 0;
	board->ply = 0;
	board->historyply = 0;
	board->enpassantsquare = 0;
	board->castlingprivileges = 0;
	board->fiftymoverule = 0;
	board->positionkey = 0;
}

bool isBoardOK(ChessPosition * board)
{
	ASSERT(isSquare(board->KingPosition[WHITE]));
	ASSERT(isSquare(board->KingPosition[BLACK]));
	ASSERT(board->numPieces[WHITE ] > 0);
	ASSERT(board->numPieces[BLACK ] > 0);
	ASSERT(board->numPieces[WHITE] < (MAXPIECES + 1));
	ASSERT(board->numPieces[BLACK] < (MAXPIECES + 1));

	return true;
}
void SetPiece(ChessPosition * board, ChessPiece  * piece)
{


}
void SetPiece(ChessPosition * board, Piece piece, Location square)
{
	ASSERT(board);
	ASSERT(CountBits(piece) == 2);
	ASSERT(isSquare(square));
	ASSERT(isPiece(piece));
	ASSERT(isEmpty(square));
	Color color = getPieceColor(piece);
	ASSERT(color == WHITE || color == BLACK);
	//cout << "Piece is " << piece << " Square : " << (int)square << endl;
	//cout << " Color is : " << color << endl;
	//ASSERT(board->pieces[board->numPieces[color]][color].pPiece == EMPTY);
	board->numPieces[color]++;
	int index;
	bool foundemptyslot = false;
	for (index = 0; index < MAXPIECES; index++)
		if (board->pieces[index][color].lLocation == INVALID){
			break;
		}

	board->pieces[index][color].cColor = color;
	board->pieces[index][color].lLocation = square;
	board->pieces[index][color].pPiece = piece;
	board->pieces[index][color].index = index;
	board->Ox88Board[square] = &board->pieces[index][color];
	//board->pieces[board->numPieces[color]][color].nextPiece;
	//board->pieces[board->numPieces[color]][color].PreviousPiece;
	
	if (piece == WK)
		board->KingPosition[WHITE] = square;
	if (piece == BK)
		board->KingPosition[BLACK] = square;
}
void Clear(ChessPosition * board, Location square)
{
	ASSERT(isBoardOK(board));
	ASSERT(isSquare(square));
	ASSERT(!isEmpty(square));
	ASSERT(isPiece(board->Ox88Board[square]->pPiece));

	int index = board->Ox88Board[square]->index;
	Color color = board->Ox88Board[square]->cColor;

	ASSERT(color == WHITE || color == BLACK);

	board->numPieces[color]--;

	board->pieces[index][color].cColor = NOCOLOR;
	board->pieces[index][color].lLocation = INVALID;
	board->pieces[index][color].pPiece = EMPTY;
	//board->pieces[board->Ox88Board[square]->index][board->Ox88Board[square]->nextPiece;
	//board->pieces[board->Ox88Board[square]->index][board->Ox88Board[square]->PreviousPiece;
	//if (index > board->numPieces[color] - 1)
	//(board->pieces[index][color]) = (board->pieces[board->numPieces[color] - 1][color]);

	
	board->Ox88Board[square] = NULL;
	ASSERT(isBoardOK(board));
}
void MovePiece(ChessPosition * board, Location from, Location to)
{
	ASSERT(isBoardOK(board));
	ASSERT(isSquare(from));
	ASSERT(isSquare(to));
	ASSERT(!isEmpty(from));
	ASSERT(isEmpty(to));

	ChessPiece * piece = board->Ox88Board[from];
	board->Ox88Board[from] = NULL;

	piece->lLocation = to;
	board->Ox88Board[to] = piece;

	ASSERT(isBoardOK(board));
}