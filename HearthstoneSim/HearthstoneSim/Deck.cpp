//
// Francisco Tort
// February 19, 2014
//
//

#include "Deck.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Deck::Deck(void)
{
	iCount = 0;
	bPopulated = false;
}
//Deck::Deck(HeroClasses heroclass)
//{
//	for ( int c = 0; c < MAXCARDSONDECK; c++)
//		card[iCount++] = Card();
//
//}
void Deck::Add(Card c)
{
	if ( iCount == 30)
		return;
	card[iCount++] = c;
	if ( iCount == 30)
		bPopulated = true;
}
Card Deck::draw( void )
{
	if ( iCount > -1 )
	return card[--iCount];
}
void Deck::Randomize(void)
{
	if (!bPopulated )
		return;
	Card temp;
	int from, to;

	for (int c = 0; c < 200; c++)
	{
		from = rand() % (iCount -1);
		to = rand() % (iCount-1);
		//swap
		temp = card[to];
		card[to] = card[from];
		card[from] = temp;
	}
	return;
}


void Deck::PrintDeck(void)
{
	//if ( 

}
Deck::~Deck(void)
{
}
