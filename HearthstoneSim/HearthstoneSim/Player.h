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
	Turn turn;
	HeroClasses heroclass;
	Card hand[10];


public:
	Player();
	Player(Turn turn, HeroClasses heroclass);
	string GetClass(); 
	int GetHealth();


	bool bIsAlive(void) { return (iHealth > 0); };
	int play( Board , Card );
	~Player(void);
};

