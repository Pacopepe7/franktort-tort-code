#include "chess.h"
#include "utils.h"

/* THIS is the way its mapped */
int Ox88to64[MAXBOARDARRAY0x88] = {
	0, 1, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0,
	8, 9, 10, 11, 12, 13, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0,
	16, 17, 18, 19, 20, 21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0,
	24, 25, 26, 27, 28, 29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0,
	32, 33, 34, 35, 36, 37, 38, 39, 0, 0, 0, 0, 0, 0, 0, 0,
	40, 41, 42, 43, 44, 45, 46, 47, 0, 0, 0, 0, 0, 0, 0, 0,
	48, 49, 50, 51, 52, 53, 54, 55, 0, 0, 0, 0, 0, 0, 0, 0,
	56, 57, 58, 59, 60, 61, 62, 63, 0, 0, 0, 0, 0, 0, 0, 0 };

/* THIS is the way its mapped */
int Board64toOx88[64] = {
	0, 1, 2, 3, 4, 5, 6, 7,
	16, 17, 18, 19, 20, 21, 22, 23,
	32, 33, 34, 35, 36, 37, 38, 39,
	48, 49, 50, 51, 52, 53, 54, 55,
	64, 65, 66, 67, 68, 69, 70, 71,
	80, 81, 82, 83, 84, 85, 86, 87,
	96, 97, 98, 99, 100, 101, 102, 103,
	112, 113, 114, 115, 116, 117, 118, 119 };

string notation[MAXBOARDARRAY0x88] = {
	"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "X", "X", "X", "X", "X", "X", "X", "X",
	"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "X", "X", "X", "X", "X", "X", "X", "X",
	"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", "X", "X", "X", "X", "X", "X", "X", "X",
	"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "X", "X", "X", "X", "X", "X", "X", "X",
	"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "X", "X", "X", "X", "X", "X", "X", "X",
	"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "X", "X", "X", "X", "X", "X", "X", "X",
	"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "X", "X", "X", "X", "X", "X", "X", "X",
	"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "X", "X", "X", "X", "X", "X", "X", "X"
};
int castling[MAXBOARDARRAY0x88] = {
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
	15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
};

int movement[64][8][8];
int  kingvectors[8] = { NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST };
int  knightvectors[8] = {
	NORTH + NORTHWEST, NORTH + NORTHEAST, EAST + NORTHEAST, EAST + SOUTHEAST,
	SOUTH + SOUTHEAST, SOUTH + SOUTHWEST, WEST + SOUTHWEST, WEST + NORTHWEST };
int  bishopvectors[8] = { NORTHEAST, SOUTHEAST, SOUTHWEST, NORTHWEST, 0, 0, 0, 0 };
int  rookvectors[8] = { NORTH, SOUTH, EAST, WEST, 0, 0, 0, 0 };

int  queenvectors[8] = { NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST };


/* Functions */



Location MakeSquareFromString(string s)						{
	for (int i = 0; i < 128; i++)
		if (isSquare(i) && notation[i] == s)
			return i;
	ASSERT("INVALID SQUARE");
	return -1;
};

int CountBits(U64 b) {
	int r;
	for (r = 0; b; r++, b &= b - 1);
	return r;
}