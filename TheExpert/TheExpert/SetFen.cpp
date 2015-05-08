
#include "ChessPosition.h"
#include "utils.h"

bool SetFen(ChessPosition * board, string fen)
{

	ASSERT(fen.length() > 10);

	vector<string> tokens;
	Tokenize(fen, tokens, " ");
	int index = 0;
	int col = 0;
	int row = 0;

	do {
		switch (tokens[0][index]) {
		case 'K': SetPiece(board, WK, MakeSquare(row, col));	col++; break;
		case 'Q': SetPiece(board, WQ, MakeSquare(row, col));	col++; break;
		case 'R': SetPiece(board, WR, MakeSquare(row, col));	col++; break;
		case 'B': SetPiece(board, WB, MakeSquare(row, col));	col++; break;
		case 'N': SetPiece(board, WN, MakeSquare(row, col));	col++; break;
		case 'P': SetPiece(board, WP, MakeSquare(row, col));	col++; break;
		case 'k': SetPiece(board, BK, MakeSquare(row, col));	col++; break;
		case 'q': SetPiece(board, BQ, MakeSquare(row, col));	col++; break;
		case 'r': SetPiece(board, BR, MakeSquare(row, col));	col++; break;
		case 'b': SetPiece(board, BB, MakeSquare(row, col));	col++; break;
		case 'n': SetPiece(board, BN, MakeSquare(row, col));	col++; break;
		case 'p': SetPiece(board, BP, MakeSquare(row, col));	col++; break;
		case '/': row++; col = 0; break;
		case '1': col += 1; break;
		case '2': col += 2; break;
		case '3': col += 3; break;
		case '4': col += 4; break;
		case '5': col += 5; break;
		case '6': col += 6; break;
		case '7': col += 7; break;
		case '8': col += 8; break;
		};
		index++;
	} while (index < tokens[0].length());

	if (tokens[1] == "w") 
		board->sideToMove = WHITE;
	else 
		board->sideToMove = BLACK;


	index = 0;
	do {
		switch (tokens[2][index]) {
		case 'K': board->castlingprivileges |= WHITESHORT;  break;
		case 'Q': board->castlingprivileges |= WHITELONG;  break;
		case 'k': board->castlingprivileges |= BLACKSHORT;  break;
		case 'q': board->castlingprivileges |= BLACKLONG;  break;
		}
		index++;
	} while (index < tokens[2].length());

	//en passant quare
	if (tokens[3] == "-")
		board->enpassantsquare = INVALID;
	else
		board->enpassantsquare = MakeSquareFromString(tokens[3]);

	// 50 move rule counter
	if (tokens[4] == "-")
		board->fiftymoverule = 0;
	else
		board->fiftymoverule = MakeInt(tokens[5]);
	
	//move number
	board->Movenum = MakeInt(tokens[5]);


	ASSERT(isBoardOK(board));
	return true;
}