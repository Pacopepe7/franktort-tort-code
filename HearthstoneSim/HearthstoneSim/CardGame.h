


#pragma once

#include "Card.h"
#include "Player.h"
#include "Deck.h"
#include "Board.h"
#include "minion.h"
#include <vector>
using namespace std;

class CardGame
{
private:
	//Changes very seldom
	//TODO: Game rules
	//TODO: Card Rules
	Card allcards[400];
	int maxcards;

	//Data changes every game
	Player player[MAXPLAYERS];
	Deck deck[MAXPLAYERS];
	Board board;
	
	//Data changes every turn
	Turn stm;
	int mana;
	int manaused;
	int manaleft;
	
	//TODO: list of legal actions/moves if you will


	// Private Functions (public during debug)
	void Init(void);
	void ReadAllCards(void);

public:

	CardGame(void);
	Turn opponent(void) { return (stm == PLAYER1)? PLAYER2:PLAYER1;};
	void LoadPosition(string );
	void LoadDeck(string , int);
	void LoadHands(void);

	Card FindCard(string);
	void Play(string move);
	void PrintBoard(void);
	void run ( void );
	void Interact(int a, int v);
	bool GameOver(void);

	//funcs to resolve game rules
	bool bHasTaunt(int);

	//Funcs to resolve card rules

	~CardGame(void);
};

