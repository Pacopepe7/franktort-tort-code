//
// Francisco Tort
// February 18, 2014
//
//

#include "Card.h"

#pragma once

class Deck
{
private:
	int iCount;
	bool bPopulated;
	Card card[30];
	

public:
	Deck(void);
	void Add(Card c);
	void Randomize( void );
	Card draw(void);
	void Deck::PrintDeck(void);

	~Deck(void);

};

