/***********************************************************************************
* ChessPiece Class
* Francisco Tort
* Dec 30, 2009
*/

#include "definitions.h"
#include <string>
using namespace std;
#pragma once
class ChessPiece
{
public:
	int piecetype;        // OUT/EMPTY/Pawn/knight/bishop/rook/queen/king ( 4/6/16/32/64/128 )
	int color;            // WHITE - BLACK (1 - 2)
	int value;            // 100 for pawn, 300 for knight, 350 for Bishop,
	// 450 for Rook, 900 for Queen, 0 for king (special case)
	//string name;          // for getDescription()
	int possiblemoves;    // 2 for the pawn (NORTHEAST and NORTHWEST) etc...
	int movementvectors[8];//movement vector
	/***********************************************
	* Chess piece Constructors
	* 
	*/
	ChessPiece ( )
	{
	}
	ChessPiece ( int pt, int c, int v, string n, int pm, int mv[])
	{
		piecetype = pt;
		color = c;
		value = v;
		//name = n;
		possiblemoves = pm;
		for (int c = 0; c < pm; c++)
			movementvectors[c] = mv[c];
	}
	bool operator==(ChessPiece rhs)
	{
		if ( piecetype == rhs.piecetype &&
			color == rhs.color  )
			return true;
		return false;
	}


}; // end class

