#include "Board.h"


Board::Board(void)
{
	minions[PLAYER1].clear();
	minions[PLAYER2].clear();
	cardsonhand[PLAYER1].clear();
	cardsonhand[PLAYER2].clear();
}
void Board::Print(Turn player)
{
	if ( minions[player].empty() )
		cout << "XXX           EMPTY BOARD              XXX" << endl;
	else
	{
		cout << "Attack XXXXXXXXXXXXXXXXXXXXXXXXXXXX Health" << endl;
		for (int i = 0; i < (int)minions[player].size(); i++)
		minions[player][i].Print(); 
	}
}
void Board::play(Card card, Turn turn, int target /*no target*/)
{
	minions[turn].push_back(minion(card));
	//TODO: interact with board...
}
void Board::ResolveAttack(Turn stm, Attacker attacker, Turn opp, Target target)
{
		minions[stm][attacker].iHealth -= minions[opp][target].iAttack;
		minions[opp][target].iHealth -= minions[stm][attacker].iAttack;

		if( minions[stm][attacker].iHealth < 1 ){
			cout << minions[stm][attacker].sName << " Died" << endl;
			minions[stm].erase(minions[stm].begin() + attacker);
		}
		if( minions[opp][target].iHealth < 1 ){
			cout << minions[opp][target].sName << " Died" << endl;
			minions[opp].erase(minions[opp].begin() + target);
		}

}
bool Board::isFrozen(Turn turn, Target target)
{
	//ASSERTS
	if ( minions[turn].size() < target - 1)
		return minions[turn][target - 1].bFrozen;
	//assert...
	return false;
}
Board::~Board(void)
{

}
