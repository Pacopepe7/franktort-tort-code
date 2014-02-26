//
// Francisco Tort
// February 19, 2014
//
//

#include "CardGame.h"
#include "Board.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

CardGame::CardGame(void)
{
	Init();
}
void CardGame::Init(void)
{
	FTDEBUG("Initializing CardGame", DEBUGALL);
	turn = PLAYER1;
	player[0] = Player(PLAYER1, WARRIOR);
	player[1] = Player(PLAYER2, WARRIOR);
	FTDEBUG("CardGame initialized", DEBUGALL);
	ReadAllCards();

}
bool CardGame::GameOver ( void )
{
	// TODO: fix for ties/both die at the same time
	if (! player[PLAYER1].bIsAlive() )
		return true;
	if (! player[PLAYER2].bIsAlive() )
		return true;
	return false;
}
void CardGame::run(void)
{
	player[turn].play(board, deck[turn].draw());
	turn = (turn==PLAYER1?PLAYER2:PLAYER1); 
}
void CardGame::ReadAllCards(void)
{
	  maxcards = 0;
	  string line;
      ifstream myfile ("Hearthstone Sortable List.csv");
      if (myfile.is_open())
      {
      while ( getline (myfile,line) )
		  allcards[maxcards++] = Card(line);
	  }
    myfile.close();
}
CardGame::~CardGame(void)
{
}
