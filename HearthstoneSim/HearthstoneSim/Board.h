//
// Francisco Tort
// February 18, 2014
//
//

#pragma once

#include "Card.h"
#include "Deck.h"

class Board
{
private:

	Card minions[MAXPLAYERS][MAXMINIONSONBOARD];
	Deck cardsonhand[MAXPLAYERS][MAXCARDSONHAND];
	int iCount[MAXPLAYERS];

public:
	Board(void) ;
	void play ( Card, Turn);
	~Board(void);

};

