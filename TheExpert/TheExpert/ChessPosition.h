#pragma once

#include "ChessPiece.h"
#include <string>
#include <vector>
#include "fixedLengthStack.h"
#include "zobrist.h"

using namespace std;

/***********************************************
*
* Thanks http://chessprogramming.wikispaces.com/Bruce+Moreland
***********************************************/
typedef struct LINE {
	int cmove;              // Number of moves in the line.
	ChessMove argmove[50];  // The line.
}   LINE;

struct ChessPosition
{
	ChessPiece * Ox88Board[MAXBOARDARRAY0x88];
	ChessPiece pieces[MAXPIECES][MAXCOLOR];
	Location KingPosition[MAXCOLOR];
	int numPieces[MAXCOLOR];
	Color sideToMove;

	int Movenum;
	int ply;
	int historyply;
	Location enpassantsquare;
	Piece capturedpiece;
	int castlingprivileges; //0 - 15 ( 0000 - 1111)
	int fiftymoverule;
	U64 positionkey;
	UNMAKEMOVE unmake[MAXMOVES];
	int Materialcount[MAXCOLOR];
	int PSQT[MAXCOLOR];
} ;


bool isBoardOK(ChessPosition * board);
void InitializeBoard(ChessPosition * board);

/* Move making funcs*/
void SetPiece(ChessPosition * board, ChessPiece  * piece, bool update = true);
void SetPiece(ChessPosition * board, Piece p, Location l, bool update = true);
void MovePiece(ChessPosition * board, Location, Location, bool update = true);
void Clear(ChessPosition * board, Location Square, bool update = true);
void MakeMove(ChessPosition * board, ChessMove chessmove, bool update = true);
void UnMakeMove(ChessPosition * board, ChessMove cm, bool update = true);

/* Null Move */
void MakeNullMove(ChessPosition * board);
void UnMakeNullMove(ChessPosition * board);

ChessMove MakeMoveFromString(ChessPosition * board, string cm);

bool SetFen(ChessPosition * board, string fen);
U64 perft(ChessPosition * board, int depth);
void PrintBoard(const ChessPosition * board);

void GenerateMoves(const ChessPosition * board, MOVELIST * list, bool quiet = true);
ChessMove RemoveMoveFromList(MOVELIST * list);
bool OrderPV(MOVELIST *, LINE *, int depth);

bool isAttacked(const ChessPosition * board, const Location target, const Color color);

void AlphaBetaDriver(ChessPosition *, S_SEARCHINFO * );
int AlphaBeta(ChessPosition * board, int alpha, int beta, int depth, LINE * pline, S_SEARCHINFO *, bool DoNullMove = true);
int QuietAlphaBeta(ChessPosition * board, int alpha, int beta, S_SEARCHINFO *info);
int Eval(void);