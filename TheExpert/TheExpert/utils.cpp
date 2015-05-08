/***
* Francisco Tort
* Utility functions
* April 27, 2015
*
*/

#include "utils.h"



/*************************************************************
* Taken from: http://oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
*
*/
void Tokenize(const string& str,
	vector<string>& tokens,
	const string& delimiters)
{
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos = str.find_first_of(delimiters, lastPos);

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
string notation0x88[128] = {
	"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "X", "X", "X", "X", "X", "X", "X", "X",
	"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "X", "X", "X", "X", "X", "X", "X", "X",
	"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "X", "X", "X", "X", "X", "X", "X", "X",
	"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "X", "X", "X", "X", "X", "X", "X", "X",
	"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "X", "X", "X", "X", "X", "X", "X", "X",
	"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", "X", "X", "X", "X", "X", "X", "X", "X",
	"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "X", "X", "X", "X", "X", "X", "X", "X",
	"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "X", "X", "X", "X", "X", "X", "X", "X"
};

string MakeNotation0x88(int i)
{
	ASSERT(i >= 0);
	ASSERT(i <= 128);
	return "X";
	//return notation0x88[i];
}


