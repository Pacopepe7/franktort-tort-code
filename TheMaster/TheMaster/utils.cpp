/***
* Francisco Tort
* Utility functions
* Jan 15, 2010
*
*/

#include "utils.h"

/*************************************************************
* Taken from: http://oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
* 
*/
void Tokenize(const string& str,
			  vector<string>& tokens,
			  const string& delimiters )
{
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos     = str.find_first_of(delimiters, lastPos);

	while (string::npos != pos || string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}

int MakeInt(string s)
{
	return atoi(s.c_str());
}
string MakeString(int i)
{
	stringstream ss;
	ss << i;
	string str = ss.str();
	return str;
}
