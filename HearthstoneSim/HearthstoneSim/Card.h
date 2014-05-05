// 
// Francisco Tort
// February 18, 2014
// hearthstone card header file
//
//
#ifndef CARDS_H
#define CARDS_H

#include <string>
#include <stdio.h>
#include "Commons.h"

using namespace std;



class Card
{

private:
	string sName;
	string hcclass;
	string rarRarity;
	string tType;
	string racRace;
	int iManaCost;
	int iAttack;
	int iHealth;
	string sDesc;

	int delimitedRand(int, int);

public:
	int GetHealth()		{ return iHealth; };
	int GetDamage()		{ return iAttack; };
	int GetManaCost()	{ return iManaCost; };
	string GetName()	{ return sName; };
	string GetDesc()	{ return sDesc; };
	void Print(void);
	

	Card(void);
	Card(string);
	Card ( int health, int attack, int manacost, string name, string desc);
		Card::Card ( string name,string hc,	string rar,	string t, string rac, int cost, int attack,	int health,	string desc);
	~Card(void);
};

#endif