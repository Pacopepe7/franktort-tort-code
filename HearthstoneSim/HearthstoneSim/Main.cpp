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
	cardgame.Init();
	cardgame.LoadDeck("C:\\temp\\Warrior.hsd", 0);
	cardgame.LoadDeck("C:\\temp\\Warrior.hsd", 1);
	cardgame.deck[0].Randomize();
	cardgame.deck[1].Randomize();

	cardgame.hand[0].push_back(  cardgame.deck[0].draw());
	cardgame.hand[0].push_back(  cardgame.deck[0].draw());
	cardgame.hand[0].push_back(  cardgame.deck[0].draw());

	cardgame.hand[1].push_back(  cardgame.deck[1].draw());
	cardgame.hand[1].push_back(  cardgame.deck[1].draw());
	cardgame.hand[1].push_back(  cardgame.deck[1].draw());
	cardgame.hand[1].push_back(  cardgame.deck[1].draw());

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


