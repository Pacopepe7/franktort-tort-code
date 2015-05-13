/*
TheMaster, a UCI chess playing engine
Copyright (C)2014 Francisco Tort
*/

#pragma once

#include "ChessMove.h"
#include <random>

typedef unsigned __int64 U64;



#define	TableSize				1500000
#define MAXZPIECES				33
#define MAXCOLORS				3
#define MAXSQUARES				128
#define MAXDEPTH				60

#define    hashfEXACT   0
#define    hashfALPHA   1
#define    hashfBETA    2

typedef struct tagHASHE {
	U64 key;
	int depth;
	int flags;
	int value;
	ChessMove best;
	U64 perft;
}   HASHE;


extern HASHE hash_table[TableSize];
extern U64 Zobrist[MAXZPIECES][MAXCOLORS][MAXSQUARES];
extern U64 moves[MAXMOVES];
extern U64 CastleKeys[16];
extern U64 SideHash;

extern U64 TTHits;
extern U64 Stores;
extern U64 Probes;
extern ChessMove movefromtable;

#define HASH_PCSQ(cp)			(board->positionkey ^= Zobrist[cp->pPiece >> 2][cp->cColor][cp->lLocation]);
#define HASH_EP(sq, c)			(board->positionkey ^= Zobrist[EMPTY][c][sq]);
#define HASH_SIDE()				(board->positionkey ^= SideHash);
#define HASH_CASTLE()			(board->positionkey ^= CastleKeys[board->castlingprivileges]);
#define HASH_MOVENUM()			(board->positionkey ^= moves[board->Movenum]);

void InitZobristTable(void);
int ProbeHash(U64 ZobristKey, int depth, int alpha, int beta);
void RecordHash(U64 ZobristKey, int depth, int val, int hashf);
U64 ProbeHashperft(U64 ZobristKey, int depth);
void RecordHashperft(U64 ZobristKey, int depth, U64 perft);
U64 rand64(void);
void PrintZTStats(void);
//