//
// Francisco Tort
// February 19, 2014
//
//

#include "utilities.h"
#include "Deck.h"


using namespace std;

Deck::Deck(void)
{
	iCount = 0;
	bPopulated = false;
}
Deck::~Deck(void)
{
}
//Deck::Deck(HeroClasses heroclass)
//{
//	for ( int c = 0; c < MAXCARDSONDECK; c++)
//		card[iCount++] = Card();
//
//}
void Deck::Add(Card c)
{
	ASSERT(! isFull());
	card[iCount++] = c;
	if ( isFull())
		bPopulated = true;
}
Card Deck::draw( void )
{
	ASSERT(! isEmpty() );
	return card[--iCount];
}
void Deck::Shuffle(void)
{
	ASSERT( isFull());
	
	Card temp;
	int from, to;

	for (int c = 0; c < rand() % 500; c++)
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
	//

}

