/***************************************************************
* Francisco Tort
* Jan 2, 2009
* 
***************************************************************/
#include "chessmove.h"
/**************************************************************
* ChessMove contructor
* This contructor does not take into account that the move is in the context of a chess game
*/
ChessMove::ChessMove ( )
{
	from = 0;
	to = 0;
	capture = 0; // normal move until it is given a ChessBoard context
	promotion = 0;
	enpassant = 0;
	castle = 0;
	piecetype = QUEEN;
	value = 0;

}
ChessMove::ChessMove ( int x, int y )
{
	from = x;
	to = y;
	capture = 0; // normal move until it is given a ChessBoard context
	promotion = 0;
	enpassant = 0;
	castle = 0;
	piecetype = QUEEN;
	value = 0;
}
/**************************************************************
* ChessMove contructor
* This contructor does not take into account that the move is in the context of a chess game
*/
ChessMove::ChessMove ( int x, int y , int c)
{
	from = x;
	to = y;
	capture = c; // normal move until it is given a ChessBoard context
	promotion = 0;
	enpassant = 0;
	castle = 0;
	piecetype = 0;
	value = 0;
}

/**************************************************************
* A chessmove refined contructor, 
* it does take into account the chess move as part of a chess game
*/
ChessMove::ChessMove ( int x, int y , int cap , int p , int e , int cas , int pt, int ep)
{
	from = x;
	to = y;
	capture = cap;
	promotion = p;
	enpassant = e;
	castle = cas;
	piecetype = pt;
	enpassantpossible = ep;
}
/**************************************************************
*Breaks down a chess move string into a ChessMove
*/
//ChessMove::ChessMove ( string move )
//{
//
//	if ( move.length() == 4 )
//	{
//
//
//	}
//} // ChessMove ( String move )

/**************************************************************
* Input: 2 char string
* output: index of the string in "notation" array
*/
int ChessMove::getIndex(string x)
{
	for (int c = NOTATIONMIN; c < NOTATIONMAX; c++)
		if ( notation[c] == x )
			return c;
	return INVALID;
} // getIndex

/**************************************************************
* Inout: 2 char string
* output: index of the string in "notation" array
*/
string ChessMove::getString(int index)
{
	if ( index < NOTATIONMIN || index > NOTATIONMAX )
		return "INVALID INDEX";
	return notation[index];

} // getString

/**************************************************************
* ToString ()
* Helper class to return an english description of the move
*/
string ChessMove::ToString ( void )
{
	string output;
	if ( ! promotion )
	{
		output = (string)notation[this->from] + (string)notation[this->to] ;
	}
	else
	{
		output = (string)notation[this->from] + (string)notation[this->to];
		if(piecetype == QUEEN )
			output = output + "q";
		if(piecetype == ROOK )
			output = output + "r";
		if(piecetype == BISHOP )
			output = output + "b";
		if(piecetype == KNIGHT )
			output = output + "n";
	}
	return output;
}
// notation array is useful when converting array indexes to Computer algebraic ("a1b2")
//char* MyClass::stringTable[2] = { "mystring1", "myString2" };
char * ChessMove::notation[144] = {
	" X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X",
	" X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X",
	" X", " X", "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", " X", " X",
	" X", " X", "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", " X", " X",
	" X", " X", "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", " X", " X",
	" X", " X", "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", " X", " X",
	" X", " X", "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", " X", " X",
	" X", " X", "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", " X", " X",
	" X", " X", "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", " X", " X",
	" X", " X", "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", " X", " X",
	" X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X",
	" X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X"
};