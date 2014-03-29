
/*****************************************
* Attacks0x88
* Pre-calculate all the pieces that can attack one square from another square. 
* http://web.archive.org/web/20071214140839/http://www.seanet.com/~brucemo/topics/0x88.htm
* 
*/

#include "ChessGame.h"


void ChessGame::InitTables ( void )
{
	//Attacks0x88
	Piece temp[128];
	for (int i = 0; i < 128; i++)
		temp[i] = EMPTY;

	temp[A1] = QUEEN;


}