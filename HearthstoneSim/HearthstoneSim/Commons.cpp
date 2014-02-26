//
// Francisco Tort
// February 22, 2014
//
// Commons.cpp

#include "Commons.h"

void FTDEBUG(string line, debuglevel level )
{
	if ( level > DEBUGALL )
	cout << line << endl;
}