// 
// Francisco Tort
// February 18, 2014
// hearthstone card header file
//
//

#include <string>
#include <stdio.h>

#include "Commons.h"

#pragma once

using namespace std;

class Card
{
	//Name,Class,Rarity,Type,Race,
	//Cost,Attack,Health,Description
public:
	//Card * next;
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
	Card ( int health, int attack, int manacost, string name, string desc)
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
			string desc);
	~Card(void);
};

