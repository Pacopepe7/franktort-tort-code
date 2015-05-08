

#include "Color.h"
#include "Pieces.h"
#include "Chess.h"
#include <iostream>

// for each of the 64 locations/squares
// for each of the 8 pieces, 
// for each of the 2 sides (for pawns)
// how many steps from this square&piece&direction, steps
//static int movement[64][8][8]



//void InitMovementTable(void)
//{
//	std::cout << "entering Init movement table\n";
//
//	std::cout << "Initializing movement table\n";
//
//	//Location loc;
//	int sq, vectors, curr;
//	for (sq = 0; sq < 64; sq++)
//		for (vectors = 0; vectors < 8; vectors++)
//			for (curr = 0; curr < MAXPIECES12; curr++)
//				movement[sq][vectors][curr] = 0;
//
//	for (curr = 0; curr < 64; curr++)
//	{	//Queen first
//		for (vectors = 0; vectors < MAXQUEENVECTORS; vectors++)
//		{
//			for (sq = Board64toOx88[curr] + queenvectors0x88[vectors]; isSquare0x88(sq); sq += queenvectors0x88[vectors])
//			{
//				//std::cout << "from = " << notation[Board64toOx88[curr]] << " sq = " << sq << " Not = " << notation[sq] << " vectors = " << vectors << "\n";
//				movement[curr][vectors][QUEEN8]++;
//			}	
//			//cout << " attacks = " << movement[curr][vectors][QUEEN8] << endl;
//		}
//		//cout << " Changing vector "  << endl;
//	}
//
//	for (curr = 0; curr < 64; curr++)
//	{	//ROOK 
//		for (vectors = 0; vectors < MAXROOKVECTORS; vectors++)
//		{
//			for (sq = Board64toOx88[curr] + rookvectors0x88[vectors]; isSquare0x88(sq); sq += rookvectors0x88[vectors])
//			{
//				//std::cout << "from = " << notation[Board64toOx88[curr]] << " sq = " << sq << " Not = " << notation[sq] << " vectors = " << vectors << "\n";
//				movement[curr][vectors][ROOK8]++;
//			}
//		}
//	}
//	for (curr = 0; curr < 64; curr++)
//	{	//BISHOP 
//		for (vectors = 0; vectors < MAXBISHOPVECTORS; vectors++)
//		{
//			for (sq = Board64toOx88[curr] + bishopvectors0x88[vectors]; isSquare0x88(sq); sq += bishopvectors0x88[vectors])
//			{
//				//std::cout << "from = " << notation[Board64toOx88[curr]] << " sq = " << sq << " Not = " << notation[sq] << " vectors = " << vectors << "\n";
//				movement[curr][vectors][BISHOP8]++;
//			}
//		}
//	}
//
//	for (curr = 0; curr < 64; curr++)
//	{	//KNIGHT 
//		for (vectors = 0; vectors < MAXKNIGHTVECTORS; vectors++)
//		{
//			sq = Board64toOx88[curr] + knightvectors0x88[vectors];
//			if (isSquare0x88(sq))
//				movement[curr][vectors][KNIGHT8]++;
//		}
//	}
//
//	for (curr = 0; curr < 64; curr++)
//	{	//KING 
//		for (vectors = 0; vectors < MAXKINGVECTORS; vectors++)
//		{
//			sq = Board64toOx88[curr] + kingvectors0x88[vectors];
//			if (isSquare0x88(sq))
//				movement[curr][vectors][KING8]++;
//		}
//	}
//
//	//for (curr = 0; curr < 64; curr++)
//	//{	//WHITEPAWNS & BLACKPAWNS are special cases...
//	//	for (vectors = 0; vectors < MAXKINGVECTORS; vectors++)
//	//	{
//	//		sq = Board64toOx88[curr] + kingvectors[vectors];
//	//		if (isSquare(sq))
//	//			ChessPiece::movement[curr][vectors][KING8]++;
//	//	}
//	//}
//
//	std::cout << "Terminating movement table\n";
//}