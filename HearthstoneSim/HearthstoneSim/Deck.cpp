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
Deck::Deck(HeroClasses heroclass)
{
	for ( int c = 0; c < MAXCARDSONDECK; c++)
		card[iCount++] = Card();

}
Card Deck::draw( void )
{
	//if ( iCount > 0 )
	//return card[iCount--];
	return Card();
}
void Deck::Randomize(void)
{
	if (!bPopulated )
		return;
	Card temp;
	int from, to;

	for (int c = 0; c < 200; c++)
	{
		from = rand() * iCount;
		to = rand() * iCount;
		//swap
		temp = card[to];
		card[to] = card[from];
		card[from] = temp;
	}
	return;
}
void Deck::ReadDeck(string path)
{
      ifstream myfile (path);
	  string line;
      if (myfile.is_open())
      {
      while ( getline (myfile,line) )
      {
      cout << line << '\n';
    }
    myfile.close();
  }

bPopulated = true;
}
void Deck::PrintDeck(void)
{
	//if ( 

}
Deck::~Deck(void)
{
}
