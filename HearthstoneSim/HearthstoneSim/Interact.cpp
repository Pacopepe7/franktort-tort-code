/****************************************************
* 
*
*/
#include "CardGame.h"

void CardGame::Interact(Attacker attacker, Target target)
{
	/********************************************************************
	* Frozen rule
	*/
	if ( board.isFrozen(stm,attacker) )
	{
		std::cout << "Attacker is Frozen" << endl;
		return;
	}
	/********************************************************************
	* victim is a hero
	*/
	//if (  v == -1 )
	//{
	//	if ( bHasTaunt(opponent()))
	//	{
	//		cout << "Victim is hero, opponent has taunt minions" << endl;
	//		return;
	//	}
	//	cout << " Attacking Hero" << 
	//		"\n with " << minions[turn][a].sName  << endl;
	//	player[opponent()].ReceiveAttack(minions[turn][a].iAttack);
	//	return;
	//}
	/********************************************************************
	* Taunt Rule
	*/
	//if ( bHasTaunt(opponent()) )
	//{
	//	if ( !minions[opponent()][v].bTaunt )
	//	{
	//		cout << "Victim does not have taunt, opponent has taunt minions" << endl;
	//		return;
	//	}
	//}

	
	//special case where none of the actors have a special ability
	//if ( !minions[turn][a].HasAbility() && !minions[opponent()][v].HasAbility())
	//{
		std::cout << " Attacking " << board.GetName(opponent(), target) << 
			"\n with " << board.GetName(stm, attacker)  << endl;
		board.ResolveAttack(stm, attacker, opponent(), target);
		
		return;
	//}

}

