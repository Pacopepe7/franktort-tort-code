/***
* Francisco Tort
* Utility function headers
* Jan 15, 2010
*
*/

#include <vector>
#include <string>
using namespace std;


void Tokenize(const string& str,
			  vector<string>& tokens,
			  const string& delimiters );
void Profiler(int);
void ProfilerEnd(int);
void ProfilerPrint(void);


//
//stringstream ss;
//ss << a;
//string str = ss.str();


