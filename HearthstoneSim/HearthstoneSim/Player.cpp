//
// Francisco Tort
// February 18, 2014
//

#include "Player.h"
#include "Board.h"


Player::Player(void)
{
}

Player::Player(Turn _turn, HeroClasses _heroclass)
{
	turn = _turn;
	heroclass = _heroclass;
	iHealth = 30;

}
string Player::GetClass( void ) 
{
	switch ( heroclass )
	{
	case MAGE:
		return "MAGE";
	case WARRIOR:
		return "WARRIOR";
	default:
		return "UNDEFINED";
	}

}
int Player::play(Board board, Card card)
{
	cout << "Player " << turn + 1 << " is Playing...\n";
	cout << "Player " << turn + 1 << " took 1 damage\n";
	iHealth--;
	cout << "<" << card.GetManaCost() << " ," << card.GetDamage() << ", " << card.GetHealth() << ">\n";
	return 0;
}


Player::~Player(void)
{
}
