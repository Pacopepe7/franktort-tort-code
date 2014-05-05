
//
// Francisco Tort
// February 18, 2014
//
//

#ifndef MINIONS_H
#define MINIONS_H

#include <string>
#include <iostream>
using namespace std;

class minion
{
public:

	int iHealth;
	int iAttack;
	int iManaCost;
	bool bStealth;
	bool bFrozen;
	bool bDamaged;
	bool bActive;
	bool bTaunt;
	bool bDivineShield;
	bool bHasAbility;
	string sName;
	

public:
	minion(void);
	bool HasAbility(void) { return bHasAbility; };
	minion(string n, int a, int h, bool s, bool f);
	void Print(void);
	~minion(void);
};

#endif