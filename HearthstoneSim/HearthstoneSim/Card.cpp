//
// Francisco Tort
// February 19, 2014
//
//


#include "Card.h"
#include "utilities.h"


Card::Card(void)
{
	iHealth = delimitedRand( 2, 4);
	iAttack = delimitedRand( 2, 4);
	iManaCost = delimitedRand( 2, 4);
	sName = "RandomCard";
	sDesc = "Random!!!";
}
Card::Card ( int health, int attack, int manacost, string name, string desc)
{ 
	iHealth = health;
	iAttack = attack;
	iManaCost = manacost;
	sName = name;
	sDesc = desc;
};
Card::Card ( string name,
	string hc,
	string rar,
	string t,
	string rac,
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
/**************************************
* Name,Class,Rarity,Type,Race,Cost,Attack,Health,Description
* Abomination,All,Rare,Minion,,5,4,4,Taunt. Deathrattle: Deal 2 damage to ALL characters.
*/
Card::Card(string line)
{
	//FTDEBUG("Reading card: " + line, DEBUGALL);
	vector<string> tokens;
	int length = line.length();
	int iterator = 0;
	Tokenize(line, tokens,  ",");
	if (tokens.size() == 8 ){
		FTDEBUG("ERROR", DEBUGALL);
		FTDEBUG(line, DEBUGALL);
	}
	sName = tokens[0];
	hcclass = tokens[1];
	rarRarity = tokens[2];
	tType = tokens[3];
	//racRace = tokens[4];
	iManaCost = FTATOI(tokens[5].c_str());
	iAttack = FTATOI(tokens[6].c_str());
	iHealth = FTATOI(tokens[7].c_str());
	if ( tokens.size() == 9)
		sDesc = tokens[8];
	else
		sDesc = "";
	//FTDEBUG(sDesc, DEBUGALL);
}
int Card::delimitedRand(int floor, int ceiling)
{
	int range = (ceiling - floor) + 1;
	int c = rand()% range;
	return c + floor;
}
void Card::Print(void)
{
	int l = sName.length();
	int r = 28 - l;
	cout << "<" << iAttack << "> <" << iManaCost << ">   " << sName;
	for ( l = 0; l < r; l++)
		cout << " ";
	cout <<  " <" << iHealth << ">" << endl;
}
Card::~Card(void)
{
}
