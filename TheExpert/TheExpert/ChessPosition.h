#pragma once

#include "ChessPiece.h"
#include <string>
#include <vector>
#include "fixedLengthStack.h"

using namespace std;

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
	int castlingprivileges; //0 - 15 ( 0000 - 1111)
	int fiftymoverule;
	U64 positionkey;
	UNMAKEMOVE unmake[MAXMOVES];
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
void PrintBoard(ChessPosition * board);

void GenerateMoves(ChessPosition * board, MOVELIST * list);
