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

void SetPiece(ChessPosition * board, ChessPiece  * piece);
void SetPiece(ChessPosition * board, Piece p, Location l);
void MovePiece(ChessPosition * board, Location, Location);
void Clear(ChessPosition * board, Location Square);

void MakeMove(ChessPosition * board, ChessMove chessmove);
ChessMove MakeMoveFromString(ChessPosition * board, string cm);
void UnMakeMove(ChessPosition * board, ChessMove cm);
bool SetFen(ChessPosition * board, string fen);
U64 perft(ChessPosition * board, int depth);
void PrintBoard(const ChessPosition * board);

void GenerateMoves(const ChessPosition * board, MOVELIST * list, bool quiet = true);
ChessMove RemoveMoveFromList(MOVELIST * list);
void OrderPV(MOVELIST *, LINE *, int depth);

bool isAttacked(const ChessPosition * board, const Location target, const Color color);

void AlphaBetaDriver(ChessPosition *);
int AlphaBeta(ChessPosition * board, int alpha, int beta, int depth, LINE * pline, int * nodes);
int QuietAlphaBeta(ChessPosition * board, int alpha, int beta);
int Eval(void);