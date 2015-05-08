#include "ChessMove.h"


ChessMove MakeMoveFromString(string move)
{
	ASSERT(move.length() > 3);
	string from = move.substr(0, 2);
	string to = move.substr(2, 2);

	return CM(MakeSquareFromString(from),
		MakeSquareFromString(to), EMPTY, EMPTY, EMPTY);
}

