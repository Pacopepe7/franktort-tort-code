
/*****************************************
* Attacks0x88
* Pre-calculate all the pieces that can attack one square from another square. 
* http://web.archive.org/web/20071214140839/http://www.seanet.com/~brucemo/topics/0x88.htm
* 
*/

#include "ChessGame.h"
#include <assert.h>

// if delta = 1, then S2 is to the right (EAST) of S1 : [ A1(112) - B1(113) ] = -1, B1 is to the left (west) of A1, which it is 
// First Square is from, second square is to
// Smallest diff: A8(0) - H1 (-119) = -119
// Largest diff : H1(119) - A8 (0) - 119
void ChessGame::InitAttackTables ( void )
{
		if( debug )
		cout << "Initializing Attack Tables\n";

	Square curr, sq;
	int diff, c;
	for ( c = 0; c < ATTACKTABLEMAX; c++)
		Attacks0x88[c] = EMPTY;


	//pawns
	Attacks0x88[ATTACKTABLEINDEXOFFSET + NORTHEAST] = Attacks0x88[ATTACKTABLEINDEXOFFSET + NORTHEAST] | PAWN;
	Attacks0x88[ATTACKTABLEINDEXOFFSET + NORTHWEST] = Attacks0x88[ATTACKTABLEINDEXOFFSET + NORTHWEST] | PAWN;
	Attacks0x88[ATTACKTABLEINDEXOFFSET + SOUTHEAST] = Attacks0x88[ATTACKTABLEINDEXOFFSET + SOUTHEAST] | PAWN;
	Attacks0x88[ATTACKTABLEINDEXOFFSET + SOUTHWEST] = Attacks0x88[ATTACKTABLEINDEXOFFSET + SOUTHWEST] | PAWN;
	for ( curr = 0; curr < 128; curr++)
	{
		if (!isSquare(curr))
			continue;
		for ( c = 0; c < 8; c++)
		{
			for ( sq = curr + queenvectors[c]; isSquare(sq) ; sq += queenvectors[c])
			{
				diff = curr - sq;
				diff += ATTACKTABLEINDEXOFFSET;
				ASSERT(diff > 0 );
				ASSERT(diff < (ATTACKTABLEINDEXOFFSET * 2));
				Attacks0x88[diff] = Attacks0x88[diff] | QUEEN;
			}
		}
		for ( c = 0; c < 4; c++)
		{
			for ( sq = curr + rookvectors[c]; isSquare(sq) ; sq += rookvectors[c])
			{
				diff = curr - sq;
				diff += ATTACKTABLEINDEXOFFSET;
				ASSERT(diff > 0 );
				ASSERT(diff < (ATTACKTABLEINDEXOFFSET * 2));
				Attacks0x88[diff] = Attacks0x88[diff] | ROOK;
			}
		}
		for ( c = 0; c < 4; c++)
		{
			for ( sq = curr + bishopvectors[c]; isSquare(sq) ; sq += bishopvectors[c])
			{
				diff = curr - sq;
				diff += ATTACKTABLEINDEXOFFSET;
				ASSERT(diff > 0 );
				ASSERT(diff < (ATTACKTABLEINDEXOFFSET * 2));
				Attacks0x88[diff] = Attacks0x88[diff] | BISHOP;
			}
		}
		for ( c = 0; c < 8; c++)
		{
			sq = curr + knightvectors[c];
			{
				diff = curr - sq;
				diff += ATTACKTABLEINDEXOFFSET;
				ASSERT(diff > 0 );
				ASSERT(diff < (ATTACKTABLEINDEXOFFSET * 2));
				Attacks0x88[diff] = Attacks0x88[diff] | KNIGHT;
			}
		}

		for ( c = 0; c < 8; c++)
		{
			sq = curr + kingvectors[c];
			{
				diff = curr - sq;
				diff += ATTACKTABLEINDEXOFFSET;
				ASSERT(diff > 0 );
				ASSERT(diff < (ATTACKTABLEINDEXOFFSET * 2));
				Attacks0x88[diff] = Attacks0x88[diff] | KING;
			}
		}
	}
}
