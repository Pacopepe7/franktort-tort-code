
//
// Francisco Tort
// February 18, 2014
//
//

#ifndef MINIONS_H
#define MINIONS_H

#include <string>
#include <iostream>
#include "Card.h"

using namespace std;

class minion
{
public:

	int iHealth;
	int iAttack;
	int iManaCost;
	bool bHasAbility;
	bool bWindfury;
	bool bStealth;
	bool bFrozen;
	bool bDamaged;
	bool bActive;
	bool bTaunt;
	bool bDivineShield;
	string sName;
	

public:
	minion(void);
	minion(Card);
	bool HasAbility(void) { return bHasAbility; };
	minion(string n, int a, int h, bool s, bool f);
	void Print(void);
	~minion(void);
};

#endif