//
// Francisco Tort
// February 18, 2014
//

#pragma once

#include <string>
#include <iostream>
#include "Board.h"
#include "Card.h"


class Player
{
private:
	int iHealth;
	int iArmor;
	int iMinions;
	Turn turn;
	string heroclass;
	vector <Card> hand;


public:
	Player();
	void Print(void);
	void PrintHand(void);
	Player(Turn turn, HeroClasses heroclass);
	string GetClass(); 
	int GetHealth()						{ return iHealth; };
	void SetHealth(int h)				{ iHealth = h;};
	void SetMinions(int m)				{ iMinions = m; } ;
	void SetClass(string c)				{ heroclass = c; };
	int GetMinions(void)				{ return iMinions;};
	int GetArmor(void)					{ return iArmor; };

	bool bIsAlive(void)					{ return (iHealth > 0); };
	void ReceiveAttack(int a);
	void ReceiveCard(Card card)			{ hand.push_back(card);};	
	Card RemoveCard(int i);
	bool bHasCards(void)				{ return (hand.size() > 0);};
	int iCardCount(void)				{ return hand.size() ;};
	int iGetManaCost(int i)				{ return hand[i].GetManaCost();};
	int play( Board , Card );
	~Player(void);
};

