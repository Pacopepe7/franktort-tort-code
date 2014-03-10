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

int FTATOI(string input)
{
	if ( input.length() == 0 )
		return 0;
	return atoi(input.c_str());

}