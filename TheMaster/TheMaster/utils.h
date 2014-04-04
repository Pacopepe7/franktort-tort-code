/***
* Francisco Tort
* Utility function headers
* Jan 15, 2010
*
*/

#include <vector>
#include <string>
#include <sstream>
using namespace std;


void Tokenize(const string& str,
			  vector<string>& tokens,
			  const string& delimiters );

int MakeInt(string s);
string MakeString(int i);
//void Assert(bool condition);
