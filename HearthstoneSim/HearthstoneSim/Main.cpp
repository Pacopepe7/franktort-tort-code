//
//
//
//
//


#include "CardGame.h"

void main ( void )
{
	string input;
	CardGame cardgame;

	//cardgame.LoadPosition("C:\\temp\\testboard1.hsb");
	
	cardgame.LoadDeck("C:\\Users\\Paquito\\Google Drive\\programming\\temp\\Warrior.hsd", PLAYER1);
	cardgame.LoadDeck("C:\\Users\\Paquito\\Google Drive\\programming\\temp\\Warrior.hsd", PLAYER2);

	cardgame.LoadHands();
	cardgame.PrintBoard();
	while ( ! cardgame.GameOver() )
		{
			getline(cin, input);
			if ( input == "quit") 
				break;
			cardgame.Play(input);
			cardgame.PrintBoard();
	}

	
	return ;
}


