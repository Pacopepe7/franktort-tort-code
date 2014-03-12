/****************************************************
* 
*
*/
#include "CardGame.h"

bool CardGame::bHasTaunt(int t)
{
	for ( int i = 0; i < minions[t].size(); i++)
	{
		if ( minions[t][i].bTaunt )
			return true;
	}
	return false;
}