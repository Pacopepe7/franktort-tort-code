//
// Francisco Tort
// February 18, 2014
//
//

#pragma once

#include "Card.h"
#include "Deck.h"
#include "minion.h"

class Board
{
private:
	vector <minion> minions[MAXPLAYERS];
	vector <Deck> cardsonhand[MAXPLAYERS];

	int iCount[MAXPLAYERS];

public:
	Board(void) ;
	void Print(Turn stm);
	void play ( Card, Turn turn, Target target = 0);
	void ResolveAttack(Turn stm, Attacker attacker, Turn opp, Target target);
	string GetName(Turn turn, Target target)		{ return minions[turn][target].sName; };
	int GetMinionCount ( Turn turn)					{ return minions[turn].size();};
	void UnFreeze(Turn stm)							{ for ( int c = 0; c < (int)minions[stm].size(); c++) minions[stm][c].bFrozen = false;};
	bool isFrozen(Turn, Target);
	~Board(void);

};

