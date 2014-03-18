/***************************************************************
* Francisco Tort
* Jan 2, 2009
* 
***************************************************************/
#include "chessmove.h"
/**************************************************************
* ChessMove contructor
*/
ChessMove::ChessMove ( )
{
	m_uiChessMove = 0;
}
ChessMove::ChessMove ( int x, int y )
{
	m_uiChessMove = (x | (y << 6));
}
/**************************************************************
* ChessMove contructor
*/
ChessMove::ChessMove ( int x, int y , int f)
{
	m_uiChessMove = (x | (y << 6));
	m_uiChessMove = (m_uiChessMove | f);
}

