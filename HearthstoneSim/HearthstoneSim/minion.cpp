#include "minion.h"


minion::minion(void)
{
}

minion::minion(string n, int a, int h, bool s, bool f)
{ 
	sName = n;
	iHealth = h;
	iAttack = a;
	bStealth = s;
	bFrozen = f;
	bHasAbility = false;
	bTaunt = false;
	bDamaged = false;
}
void minion::Print(void){
	int l = sName.length();
	int r = 32 - l;
	cout << "<" << iAttack << ">   " << sName;
	for ( l = 0; l < r; l++)
		cout << " ";
	cout <<  " <" << iHealth << ">" << endl;
}
minion::~minion(void)
{
}
