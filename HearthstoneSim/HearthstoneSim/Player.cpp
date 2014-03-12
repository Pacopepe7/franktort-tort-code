//
// Francisco Tort
// February 18, 2014
//

#include "Board.h"
#include "Player.h"



Player::Player(void)
{
}

Player::Player(Turn _turn, HeroClasses _heroclass)
{
	turn = _turn;
	heroclass = _heroclass;
	iHealth = 30;
	iArmor = 0;

}
string Player::GetClass( void ) 
{
return heroclass;

}
int Player::play(Board board, Card card)
{
	cout << "Player " << turn + 1 << " is Playing...\n";
	cout << "Player " << turn + 1 << " took 1 damage\n";
	iHealth--;
	cout << "<" << card.GetManaCost() << " ," << card.GetDamage() << ", " << card.GetHealth() << ">\n";
	return 0;
}
void Player::ReceiveAttack(int a)
{
	//todo, armor, secrets....etc...
	iHealth -=a;
}

Player::~Player(void)
{
}
