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
	Player player[2];
	Deck deck[2];
	vector <Card> hand[2];
	Board board;
	
	//Data changes every turn
	int turn;
	int mana;
	int manaused;
	int manaleft;
	int Manapool;
	vector<minion> minions[2];


	//TODO: list of legal actions/moves if you will


	// Private Functions (public during debug)
	void Init(void);
	void ReadAllCards(void);

public:

	CardGame(void);
	int opponent(void) { return turn == 1? 0:1;};
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

