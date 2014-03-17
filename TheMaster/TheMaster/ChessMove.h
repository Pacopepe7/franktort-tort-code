/***************************************************************
* Francisco Tort
* Dec 30, 2009
* ChessMove class creates a move from a pair of coordinates in the board array
* or a string in the form "e2e4[p]" where the first two characters are the 
* coordinates of the square the piece if being moved from, the second two
* characters are the coordinates of the square the piece is being moved to
* and the optional last character is for promotions,   
* */

/**********************************************************
* 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 = short is 2 bytes, 16 bits
* 00000000000000000000000000000000000000000000000000= 32 bit integer
* 
* XXXXXX         from is 0-63, 2^6, 6 bits to store from
* to    XXXXXX   is 0-63, 2^6, 6 bits to store to
* Is capture  X  one bit
* Is promotion X one bit
* is enpassant  X possible? one bit
* Is castle      X one bit
* Piece type      XXX for promotion
* Is enpassant       X possible? one bit
* Value of move       XXXXXXXXXXXXXXXX 16 bits (0-65536) or (-30000-30000)
************************************************************/

#include "definitions.h"
#include <string>

const int FROM_MASK = 63;
const int TO_MASK	= 4032;
const int CAP_MASK	= 4096;


using namespace std;

class ChessMove
{ 

public:

	

	static char  *notation[144];
	unsigned int move;
	int from;				// from square
	int to;				// to square
	int capture;			// check, capture, enpassant etc...
	int promotion;		//
	int enpassant;
	int castle;			//
	int piecetype;			// for promotion
	int enpassantpossible;//
	int value;				// the move's value after evaluating the position.

	public:
	ChessMove ( );
	ChessMove ( int from, int to );
	ChessMove ( int from, int to , int capture);
	ChessMove ( int from, int to , int capture , int promotion , int enpassant , int castle , int piecetype, int enpassantpossible);
	//ChessMove ( string move 
	//int from(void) { return (move & FROM_MASK);};
	//int to (void)  { return ((move & TO_MASK) << 6);};
	

	string ToString(void);
	int getIndex( string str);
	string getString ( int index);



};// class ChessMove 

