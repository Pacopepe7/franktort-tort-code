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
	void Randomize( void );

public:
	Deck(void);
	Deck(HeroClasses);
	
	void ReadDeck(string);
	Card draw(void);
	void Deck::PrintDeck(void);

	~Deck(void);

};

