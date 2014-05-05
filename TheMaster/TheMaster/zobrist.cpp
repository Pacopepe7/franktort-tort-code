/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort
*/

#include "zobrist.h"

U64 rand64(void)
{
    return rand() ^ ((U64)rand() << 15) ^ ((U64)rand() << 30) ^
        ((U64)rand() << 45) ^ ((U64)rand() << 60);
}

void InitZobristTable(void)
{



}