//
// Francisco Tort
// February 22, 2014
//
// Commons.cpp

#include "Commons.h"

void FTDEBUG(string line, debuglevel level )
{
	if ( level > NODEBUGALL )
	cout << line << endl;
}
void FTDEBUGi(int i, debuglevel level )
{
	if ( level > NODEBUGALL )
	cout << i << endl;
}

int FTATOI(string input)
{
	if ( input.length() == 0 )
		return 0;
	return atoi(input.c_str());

}
bool FTATOB(string input)
{
	if ( input.length() == 0 )
		return 0;
	if ( atoi(input.c_str()))
		return true;
	else
		return false;
}

