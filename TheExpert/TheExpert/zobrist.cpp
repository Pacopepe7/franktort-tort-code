/*
TheMaster, a UCI chess playing engine
Copyright (C)2014 Francisco Tort
*/

#include "zobrist.h"
#include "iostream"

#include <time.h>

using namespace std;

#define MAXDEPTHFORTT		20	

HASHE hash_table[TableSize];
U64 Zobrist[MAXZPIECES][MAXCOLORS][MAXSQUARES];
U64 CastleKeys[16];
U64 moves[MAXMOVES];
U64 SideHash;
ChessMove movefromtable;
U64 TTHits;
U64 Probes;
U64 Stores;
U64 rand64(void)
{
	return rand() ^ ((U64)rand() << 15) ^ ((U64)rand() << 30) ^
		((U64)rand() << 45) ^ ((U64)rand() << 60);
}

void InitZobristTable(void)
{
	srand(time((time_t)NULL));
	for (int p = 0; p < MAXZPIECES; p++)
		for (int c = 0; c < MAXCOLORS; c++)
			for (int sq = 0; sq < MAXSQUARES; sq++)
				Zobrist[p][c][sq] = rand64();

	for (int p = 0; p < MAXMOVES; p++)
		moves[MAXMOVES] = rand64();
	for (int i = 0; i < TableSize; i++)
	{
		hash_table[i].best = 0;
		hash_table[i].depth = 0;
		hash_table[i].flags = 0;
		hash_table[i].key = 0;

		hash_table[i].perft = 0;
		hash_table[i].value = 0;
	}
	SideHash = rand64();
	for (U64 i = 0; i < 16; i++)
		CastleKeys[i] = rand64();
	TTHits = 0;
	Probes = 0;
	Stores = 0;
}

void PrintZTStats(void)
{
	cout << "--------------------------------" << endl;
	cout << "Probes    : " << Probes << endl;
	cout << "Stores    : " << Stores << endl;
	cout << "Hits      : " << TTHits << endl;

	InitZobristTable();
}

int ProbeHash(U64 ZobristKey, int depth, int alpha, int beta)
{
	HASHE * phashe = &hash_table[ZobristKey % TableSize];

	if (phashe->key == ZobristKey) {
		if (phashe->depth == (MAXDEPTHFORTT - depth)) {
			if (phashe->flags == hashfEXACT)
				return phashe->value;
			if ((phashe->flags == hashfALPHA) &&
				(phashe->value <= alpha))
				return alpha;
			if ((phashe->flags == hashfBETA) &&
				(phashe->value >= beta))
				return beta;
		}
		movefromtable = phashe->best;
	}
	return -1;
}


void RecordHash(U64 ZobristKey, int depth, int val, int hashf)
{
	HASHE * phashe = &hash_table[ZobristKey % TableSize];

	phashe->key = ZobristKey;

	phashe->best = movefromtable;
	phashe->value = val;
	phashe->flags = hashf;
	phashe->depth = depth;
}

void RecordHashperft(U64 ZobristKey, int depth, U64 perft)
{
	HASHE * phashe = &hash_table[ZobristKey % TableSize];
	Stores++;
	phashe->key = ZobristKey;
	phashe->depth = depth;
	phashe->perft = perft;

}

U64 ProbeHashperft(U64 ZobristKey, int depth)
{
	HASHE * phashe = &hash_table[ZobristKey % TableSize];
	Probes++;
	if (phashe->key == ZobristKey) {
		if (phashe->depth == depth) {
			return phashe->perft;
		}
	}
	return 0;
}