#pragma once

#include "Card.h"
#include "Player.h"
#include "Deck.h"
#include "Board.h"

class CardGame
{
private:
	//Changes very seldom
	//TODO: Game rules
	//TODO: Card Rules
	//Card allcards[400];
	//int maxcards;

	//Data changes every game
	Player player[MAXPLAYERS];
	Board board;
	
	//Data changes every turn
	Turn turn;
	int Manapool;


	//TODO: list of legal actions/moves if you will


	// Private Functions
	void Init(void);
	void ReadAllCards(void);

public:

	CardGame(void);
	void run ( void );
	bool GameOver(void);
	~CardGame(void);
};

