



#include "ChessBoard.h"
#include <vector>
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


/*******************************************************************
* MakeMove (ChessMove)
* Makes the selected move on the board, returns true if this move can actually be made
* false otherwise.
* 
*/


#define FROM( cm ) (inttoboard[cm & FROM_MASK])
#define TO( cm )   (inttoboard[ (cm & TO_MASK) >> 6])
#define CASTLE( cm ) (cm & CASTLE_MASK)
#define CAPTURE(cm)  (cm & CAP_MASK)
#define PROMOTION(cm) ( cm & PROMOTION_MASK)
#define PIECE(cm)     (( cm & PIECE_MASK)<<2)
#define ENPASSANT(cm)  (( cm & ENPASSANT_MASK))

//#define INTTOBOARD( x ) inttoboard[x]
//#define BOARDTOINT( x ) boardtoint[x]


bool ChessBoard::MakeIntMove ( unsigned int cm )
{
	if ( TO(cm) == whitekingposition || TO(cm) == blackkingposition )
	{
		return false;
	}
	// update king position and castling priviledges
	if(currentposition[FROM(cm)] == WK )
	{
		whitecancastlekingside = false;
		whitecancastlequeenside = false;
		whitekingposition = TO(cm);
	}
	if(currentposition[FROM(cm)] == BK)
	{
		blackcancastlekingside = false;
		blackcancastlequeenside = false;
		blackkingposition = TO(cm);
	}
	if ( FROM(cm) == A1 )
		whitecancastlequeenside = false;
	if ( FROM(cm) == H1 )
		whitecancastlekingside = false;
	if ( FROM(cm) == A8 )
		blackcancastlequeenside = false;
	if ( FROM(cm) == H8 )
		blackcancastlekingside = false;

	//remove the piece in the "from" square and put in on the "to" square
	currentposition[TO(cm)] = currentposition[FROM(cm)];
	currentposition[FROM(cm)] = EMPTY;
	// special code for special moves
	if (CASTLE(cm) )
	{
		//System.out.println("Processing a castling move");
		if ( sidetomove == WHITE )
		{
			whitecancastlekingside = false;
			whitecancastlequeenside = false;
			if ( TO(cm) == G1)          // short castle
			{
				currentposition[F1] = currentposition[H1];
				currentposition[H1] = EMPTY;
			}
			else                                   // long castle
			{
				currentposition[D1] = currentposition[A1];
				currentposition[A1] = EMPTY;
			}
		}
		else
		{
			blackcancastlekingside = false;
			blackcancastlequeenside = false;
			if ( TO(cm) == G8)          // short castle
			{
				currentposition[F8] = currentposition[H8];
				currentposition[H8] = EMPTY;
			}
			else                                   // long castle
			{
				currentposition[D8] = currentposition[A8];
				currentposition[A8] = EMPTY;
			}
		} // end if tomove == WHITE
	} // end if castling
	if ( PROMOTION(cm) )
	{
		//System.out.println("Processing a promotion");

		switch ( PIECE(cm) )
		{
		case QUEEN:
			currentposition[TO(cm)] = (sidetomove == WHITE) ? WQ : BQ;
			break;
		case ROOK:
			currentposition[TO(cm)] = (sidetomove == WHITE) ? WR : BR;
			break;
		case BISHOP:
			currentposition[TO(cm)] = (sidetomove == WHITE) ? WB : BB;
			break;
		case KNIGHT:
			currentposition[TO(cm)] = (sidetomove == WHITE) ? WN : BN;
			break;
		}
	}
	if ( ENPASSANT(cm) )
	{
		//System.out.println("Processing an enpassant move");

		if ( sidetomove == WHITE )
			currentposition[TO(cm) + SOUTH] = EMPTY;
		else
			currentposition[TO(cm) + NORTH] = EMPTY;
	}
	//This helps prevent an ilegal position where the side that just moved is in check! 
	// this is illegal in chess.
	if ( sidetomove == WHITE )
	{
		if (IsAttacked( whitekingposition, BLACK ) > 0 )
		{
			return false;
		}
	}
	else
	{
		if (IsAttacked( blackkingposition, WHITE ) > 0 )
		{
			return false;
		}
	} // end if tomove == WHITE

	// Everything seems to be in order, change sides, update ply and last move and return true.
	// Switch side to move
	sidetomove = (sidetomove == WHITE) ? BLACK : WHITE;
	//increment ply
	ply ++;
	// keep track of last move, for enpassant etc...
	//LastMove = cm;

	return true;
}
