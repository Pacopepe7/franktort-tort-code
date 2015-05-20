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
	board->Materialcount[WHITE] = 0;
	board->Materialcount[BLACK] = 0;
	board->PSQT[WHITE] = 0;
	board->PSQT[BLACK] = 0;
	board->sideToMove = NOCOLOR;
	board->Movenum = 0;
	board->ply = 0;
	board->historyply = 0;
	board->enpassantsquare = INVALID;
	board->enpassantsquare = INVALID;
	board->castlingprivileges = 0;
	board->fiftymoverule = 0;
	InitZobristTable();
	board->positionkey = rand64();
}

bool isBoardOK(ChessPosition * board)
{
	ASSERT(isSquare(board->KingPosition[WHITE]));
	ASSERT(isSquare(board->KingPosition[BLACK]));
	ASSERT(board->numPieces[WHITE ] > 0);
	ASSERT(board->numPieces[BLACK ] > 0);
	ASSERT(board->numPieces[WHITE] < (MAXPIECES + 1));
	ASSERT(board->numPieces[BLACK] < (MAXPIECES + 1));
	ASSERT(getPiece(board->KingPosition[WHITE]) & KING);
	ASSERT(getPiece(board->KingPosition[BLACK]) & KING);
	ASSERT(getColor(board->KingPosition[WHITE]) == WHITE);
	ASSERT(getColor(board->KingPosition[BLACK]) == BLACK);
	ASSERT(board->historyply < MAXMOVES);
	ASSERT(board->historyply > -1);

	ASSERT(board->Materialcount[WHITE] > 0);
	ASSERT(board->Materialcount[BLACK] > 0);
	ASSERT(board->Materialcount[WHITE] < 20000);
	ASSERT(board->Materialcount[BLACK] < 20000);
	ASSERT(board->PSQT[WHITE] > -300);
	ASSERT(board->PSQT[BLACK] < 4000);
	ASSERT(board->PSQT[WHITE] > -300);
	ASSERT(board->PSQT[BLACK] < 4000);

	return true;
}
void SetPiece(ChessPosition * board, ChessPiece  * piece)
{


}
void SetPiece(ChessPosition * board, Piece piece, Location square, bool making)
{
	ASSERT(board);
	ASSERT(CountBits(piece) == 2);
	ASSERT(isSquare(square));
	ASSERT(isPiece(piece));
	ASSERT(isEmpty(square));
	Color color = getPieceColor(piece);
	ASSERT(isValidColor(color));
	ASSERT((piece & PIECE));
	//cout << "Piece is " << piece << " Square : " << (int)square << endl;
	//cout << " Color is : " << color << endl;
	//ASSERT(board->pieces[board->numPieces[color]][color].pPiece == EMPTY);

	int index;

	for (index = 0; index < MAXPIECES; index++)
		if (board->pieces[index][color].lLocation == INVALID){
			break;
		}
	

	board->numPieces[color]++;

	board->pieces[index][color].cColor = color;
	board->pieces[index][color].lLocation = square;
	board->pieces[index][color].pPiece = (piece & PIECE);
	board->pieces[index][color].index = index;
	board->Ox88Board[square] = &board->pieces[index][color];
	//board->pieces[board->numPieces[color]][color].nextPiece;
	//board->pieces[board->numPieces[color]][color].PreviousPiece;
	

	if (piece & KING){
		board->KingPosition[color] = square;
		board->PSQT[color] += PSQT_P[PSQT(square, color)];
	}

	board->Materialcount[color] += PieceValue(piece);
	if (making){
		HASH_PCSQ(board->Ox88Board[square]);
		if (piece & PAWN) board->PSQT[color] += PSQT_P[PSQT(square, color)];
		if (piece & KNIGHT) board->PSQT[color] += PSQT_N[PSQT(square, color)];
		if (piece & BISHOP) board->PSQT[color] += PSQT_B[PSQT(square, color)];
		if (piece & ROOK) board->PSQT[color] += PSQT_R[PSQT(square, color)];
		if (piece & QUEEN) board->PSQT[color] += PSQT_Q[PSQT(square, color)];
	}

	
}
void Clear(ChessPosition * board, Location square, bool making )
{
	ASSERT(isBoardOK(board));
	ASSERT(isSquare(square));
	ASSERT(!isEmpty(square));
	ASSERT(isPiece(board->Ox88Board[square]->pPiece));
	//ASSERT(getPiece(square) & KING);

	ChessPiece * piece = board->Ox88Board[square];
	
	int index = piece->index;
	Color color = piece->cColor;
	ASSERT(isValidColor(color));
	if (making){
		HASH_PCSQ(piece);
		if (piece->pPiece & PAWN) board->PSQT[color] -= PSQT_P[PSQT(square, color)];
		if (piece->pPiece & KNIGHT) board->PSQT[color] -= PSQT_N[PSQT(square, color)];
		if (piece->pPiece & BISHOP) board->PSQT[color] -= PSQT_B[PSQT(square, color)];
		if (piece->pPiece & ROOK) board->PSQT[color] -= PSQT_R[PSQT(square, color)];
		if (piece->pPiece & QUEEN) board->PSQT[color] -= PSQT_Q[PSQT(square, color)];
		if (piece->pPiece & KING) board->PSQT[color] -= PSQT_K[PSQT(square, color)];
	}

	board->Materialcount[color] -= PieceValue(piece->pPiece); 
	board->numPieces[color]--;
	board->pieces[index][color].cColor = NOCOLOR;
	board->pieces[index][color].lLocation = INVALID;
	board->pieces[index][color].pPiece = EMPTY;
	board->pieces[index][color].index = INVALID;
	board->Ox88Board[square] = NULL;
	ASSERT(isBoardOK(board));
}
void MovePiece(ChessPosition * board, Location from, Location to, bool making)
{
	ASSERT(isBoardOK(board));
	ASSERT(isSquare(from));
	ASSERT(isSquare(to));
	ASSERT(!isEmpty(from));

	ChessPiece * piece = board->Ox88Board[from];
	ASSERT((piece->pPiece >> 2) < MAXZPIECES);
	ASSERT((piece->pPiece >> 2) > 0);
	ASSERT(piece->lLocation < MAXSQUARES);
	ASSERT(piece->lLocation >= 0 );
	ASSERT(isValidColor(piece->cColor) );


	Color color = piece->cColor;
	ASSERT(isValidColor(color));
	Location square = piece->lLocation;
	ASSERT(piece->pPiece & PIECE);
	if (making){
		HASH_PCSQ(piece);
		if (piece->pPiece & PAWN) board->PSQT[color] -= PSQT_P[PSQT(square, color)];
		if (piece->pPiece & KNIGHT) board->PSQT[color] -= PSQT_N[PSQT(square, color)];
		if (piece->pPiece & BISHOP) board->PSQT[color] -= PSQT_B[PSQT(square, color)];
		if (piece->pPiece & ROOK) board->PSQT[color] -= PSQT_R[PSQT(square, color)];
		if (piece->pPiece & QUEEN) board->PSQT[color] -= PSQT_Q[PSQT(square, color)];
		if (piece->pPiece & KING) board->PSQT[color] -= PSQT_K[PSQT(square, color)];
	}
	board->Ox88Board[from] = NULL;
	piece->lLocation = to;
	board->Ox88Board[to] = piece;
	if (piece->pPiece & KING)
		board->KingPosition[piece->cColor] = to;
	piece = board->Ox88Board[to];
	square = to;

	if (making){
		HASH_PCSQ(piece);
		if (piece->pPiece & PAWN) board->PSQT[color] += PSQT_P[PSQT(square, color)];
		if (piece->pPiece & KNIGHT) board->PSQT[color] += PSQT_N[PSQT(square, color)];
		if (piece->pPiece & BISHOP) board->PSQT[color] += PSQT_B[PSQT(square, color)];
		if (piece->pPiece & ROOK) board->PSQT[color] += PSQT_R[PSQT(square, color)];
		if (piece->pPiece & QUEEN) board->PSQT[color] += PSQT_Q[PSQT(square, color)];
		if (piece->pPiece & KING) board->PSQT[color] += PSQT_K[PSQT(square, color)];
	}
	ASSERT(isBoardOK(board));
}