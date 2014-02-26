//
//
//
//
//


#include "CardGame.h"

void main ( void )
{
	CardGame cardgame;

	while ( ! cardgame.GameOver() )
		{
			cardgame.run();
	}

	int i;
	cin >> i;
	return ;
}


