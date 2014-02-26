/***************************************************************
* Francisco Tort
* Dec 30, 2009
* ChessMove class creates a move from a pair of coordinates in the board array
* or a string in the form "e2e4[p]" where the first two characters are the 
* coordinates of the square the piece if being moved from, the second two
* characters are the coordinates of the square the piece is being moved to
* and the optional last character is for promotions,   
* */

#include "definitions.h"
#include <string>

using namespace std;

class ChessMove
{ 
public:
	ChessMove ( );
	ChessMove ( int from, int to );
	ChessMove ( int from, int to , bool capture);
	ChessMove ( int from, int to , bool capture , bool promotion , bool enpassant , bool castle , int piecetype, bool enpassantpossible);
	ChessMove ( string move );
	string ToString(void);

public:

	int getIndex( string str);
	string getString ( int index);

	static char  *notation[144];
	int from;				// from square
	int to;				// to square
	bool capture;			// check, capture, enpassant etc...
	bool promotion;		//
	bool enpassant;
	bool castle;			//
	int piecetype;			// for promotion
	bool enpassantpossible;//
	int value;				// the move's value after evaluating the position.




};// class ChessMove 

