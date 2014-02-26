//
// Francisco Tort
// February 19, 2014
//
//


#include "Card.h"
#include <boost/tokenizer.hpp>

Card::Card(void)
{
	iHealth = delimitedRand( 2, 4);
	iAttack = delimitedRand( 2, 4);
	iManaCost = delimitedRand( 2, 4);
	sName = "RandomCard";
	sDesc = "Random!!!";
}
Card::Card ( string name,
			HeroClasses hc,
			Rarity rar,
			Type t,
			Race rac,
			int cost, 
			int attack,
			int health,
			string desc)
{ 
	sName = name;
	hcclass = hc;
	rarRarity = rar;
	tType = t;
	racRace = rac;
	iManaCost = cost;
	iAttack = attack;
	iHealth = health;
	sDesc = desc;
};
Card::Card(string line)
{
	int length = line.length();
	int iterator = 0;
	//if (line.



}
int Card::delimitedRand(int floor, int ceiling)
{
	int range = (ceiling - floor) + 1;
	int c = rand()% range;
	return c + floor;
}
string Card::print(void)
{
	return "-";
}

Card::~Card(void)
{
}
