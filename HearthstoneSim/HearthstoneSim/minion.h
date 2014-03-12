
#include <string>
#include <iostream>
using namespace std;

class minion
{
public:

	int iHealth;
	int iAttack;
	int iManaCost;
	bool bStealth;
	bool bFrozen;
	bool bDamaged;
	bool bActive;
	bool bTaunt;
	bool bDivineShield;
	bool bHasAbility;
	string sName;
	

public:
	minion(void);
	bool HasAbility(void) { return bHasAbility; };
	minion(string n, int a, int h, bool s, bool f)
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
	void Print(void){
		int l = sName.length();
		int r = 32 - l;
		cout << "<" << iAttack << ">   " << sName;
		for ( l = 0; l < r; l++)
			cout << " ";
		cout <<  " <" << iHealth << ">" << endl;
	}
	~minion(void);
};

