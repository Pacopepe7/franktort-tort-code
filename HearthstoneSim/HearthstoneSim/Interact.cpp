/****************************************************
* 
*
*/
#include "CardGame.h"

void CardGame::Interact(int a, int v)
{
	/********************************************************************
	* Frozen rule
	*/
	if ( minions[turn][a].bFrozen )
	{
		cout << "Attacker is Frozen" << endl;
		return;
	}
	/********************************************************************
	* victim is a hero
	*/
	if (  v == -1 )
	{
		if ( bHasTaunt(opponent()))
		{
			cout << "Victim is hero, opponent has taunt minions" << endl;
			return;
		}
		cout << " Attacking Hero" << 
			"\n with " << minions[turn][a].sName  << endl;
		player[opponent()].ReceiveAttack(minions[turn][a].iAttack);
		return;
	}
	/********************************************************************
	* Taunt Rule
	*/
	if ( bHasTaunt(opponent()) )
	{
		if ( !minions[opponent()][v].bTaunt )
		{
			cout << "Victim does not have taunt, opponent has taunt minions" << endl;
			return;
		}
	}

	
	//special case where none of the actors have a special ability
	if ( !minions[turn][a].HasAbility() && !minions[opponent()][v].HasAbility())
	{
		cout << " Attacking " << minions[opponent()][v].sName << 
			"\n with " << minions[turn][a].sName  << endl;
		minions[turn][a].iHealth -= minions[opponent()][v].iAttack;
		minions[opponent()][v].iHealth -= minions[turn][a].iAttack;
		if( minions[turn][a].iHealth < 1 ){
			cout << minions[turn][a].sName << " Died" << endl;
			minions[turn].erase(minions[turn].begin() + a);
		}
		if( minions[opponent()][v].iHealth < 1 ){
			cout << minions[opponent()][v].sName << " Died" << endl;
			minions[opponent()].erase(minions[opponent()].begin() + v);
		}
		
		return;
	}

}

