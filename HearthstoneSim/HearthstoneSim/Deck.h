//
// Francisco Tort
// February 18, 2014
//
//

#include "Card.h"

#ifndef DECK_H
#define DECK_H

#define FULLDECK	30

class Deck
{
private:

	int iCount;
	bool bPopulated;
	Card card[30];
	
public:
	Deck(void);
	~Deck(void);


	int size(void)				{ return iCount ; } ;
	bool isEmpty(void)			{ return iCount == 0;} ;
	bool isFull(void)			{ return iCount == FULLDECK;};
	void Add(Card c);
	void Shuffle( void );
	Card draw(void);

	/**********************************
	* I/O
	**********************************/
	void Deck::PrintDeck(void);


};

#endif