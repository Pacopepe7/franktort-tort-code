/***********************************************************************************
* ChessPiece Class
* Francisco Tort
* Dec 30, 2009
*/

#include "definitions.h"
#pragma once

class ChessPiece
{
private:
	Piece m_uiPiece;        
	
public:
	ChessPiece ( )
	{

	}	

	ChessPiece ( unsigned int p)
	{
		m_uiPiece = p;
	}
	inline Piece getColor(void)	{ return ( m_uiPiece & COLOR_MASK); } ;
	inline Piece getPiece(void)	{ return ( m_uiPiece & PIECE_MASK); } ;


}; 

