
/*******************************************************************
* MakeIntMove (unsigned int)
* Makes the selected move on the board, returns true if this move can actually be made
* false otherwise.
* 
*/
#include "ChessBoard.h"


bool ChessBoard::MakeMove ( ChessMove cm )
{

	int f = FROM(cm);
	int t = TO (cm);


	boardstate_t tempboardstate = m_boardState;
	Piece tomove = m_boardState.m_bWhitetomove? WHITE:BLACK;

	if ( TO(cm) == m_boardState.m_sWhitekingposition || TO(cm) == m_boardState.m_sBlackkingposition )
	{
		return false;
	}
	// update king position and castling priviledges
	if(isKing((FROM(cm))) && isWhite((FROM(cm))) )
	{
		 m_boardState.castling.whiteshort = false;
		 m_boardState.castling.whitelong = false;
		m_boardState.m_sWhitekingposition = TO(cm);
	}
	if(isKing((FROM(cm))) && isBlack((FROM(cm))))
	{
		m_boardState.castling.blacklong = false;
		m_boardState.castling.blackshort = false;
		m_boardState.m_sBlackkingposition = TO(cm);
	}
	if ( FROM(cm) == A1 )
		 m_boardState.castling.whitelong = false;
	if ( FROM(cm) == H1 )
		m_boardState.castling.whiteshort = false;
	if ( FROM(cm) == A8 )
		m_boardState.castling.blacklong = false;
	if ( FROM(cm) == H8 )
		m_boardState.castling.blackshort = false;

	//remove the piece in the "from" square and put in on the "to" square
	currentposition[TO(cm)] = currentposition[FROM(cm)];
	currentposition[FROM(cm)] = EMPTY;
	// special code for special moves
	if (isCaslte(cm) )
	{
		//System.out.println("Processing a castling move");
		if ( tomove == WHITE )
		{
			m_boardState.castling.whitelong = false;
			m_boardState.castling.whiteshort = false;
			m_boardState.m_sWhitekingposition = TO(cm);
			if ( TO(cm) == G1)          // short castle
			{
				currentposition[F1] = currentposition[H1];
				currentposition[H1] = EMPTY;
			}
			else                         // long castle
			{
				currentposition[D1] = currentposition[A1];
				currentposition[A1] = EMPTY;
			}
		}
		else
		{
			m_boardState.castling.blackshort = false;
			m_boardState.castling.blacklong = false;
			m_boardState.m_sBlackkingposition = TO(cm);
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
	if ( isPromotion(cm) )
	{
		int t = TO(cm);
		int f = FROM (cm);
		
		//System.out.println("Processing a promotion");
		if ( cm & QUEEN ) 
				currentposition[TO(cm)] = (tomove == WHITE) ? WQ : BQ;
		if ( cm & ROOK ) 
				currentposition[TO(cm)] = (tomove == WHITE) ? WR : BR;
		if ( cm & BISHOP ) 
				currentposition[TO(cm)] = (tomove == WHITE) ? WB : BB;
		if ( cm & KNIGHT ) 
				currentposition[TO(cm)] = (tomove == WHITE) ? WN : BN;
	}
	if ( isEP(cm) )
	{
		if ( tomove == WHITE )
			currentposition[TO(cm) + SOUTH] = EMPTY;
		else
			currentposition[TO(cm) + NORTH] = EMPTY;
	}
	//This helps prevent an ilegal position where the side that just moved is in check! 
	// this is illegal in chess.
	if ( tomove == WHITE )
	{
		if (IsAttacked( m_boardState.m_sWhitekingposition, BLACK ) > 0 )
		{
			m_boardState = tempboardstate;
			return false;
		}
	}
	else
	{
		if (IsAttacked( m_boardState.m_sBlackkingposition, WHITE ) > 0 )
		{
			m_boardState = tempboardstate;
			return false;
		}
	} // end if tomove == WHITE

	// Everything seems to be in order, change sides, update ply and last move and return true.
	// Switch side to move
	m_boardState.m_bWhitetomove = (m_boardState.m_bWhitetomove) ? FALSE : TRUE;
	//increment ply
	m_boardState.ply ++;
	// keep track of last move, for enpassant etc...
	m_boardState.m_LastMove = cm;

	return true;
}
