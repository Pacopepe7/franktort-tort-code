//
// Francisco Tort
// February 18, 2014
//

#include "Board.h"
#include "Player.h"



Player::Player(void)
{
}
void Player::Print(void)
{
	cout << "Player: " << turn << endl;
	cout << "Health: " << iHealth << endl;
	cout << "Class: " << GetClass() << endl;
	cout << "Armor: " << GetArmor() << endl;
}
void Player::PrintHand(void)
{
	if ( !hand.size() )
		return;
	cout << "Atk Cost  XXXXXXXXXXXXXXXXXXXXXXXXXXX   H " << endl;
	for ( int c = 0; c < hand.size(); c++)
		hand[c].Print();
	return;
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
Card Player::RemoveCard(int i)
{
	Card temp;
	std::vector<Card>::iterator it;
	it = hand.begin();
	it += (i );
	temp = hand[i];
	hand.erase(it);
	return temp;
}

Player::~Player(void)
{
}
