/*
  TheMaster, a UCI chess playing engine 
  Copyright (C)2014 Francisco Tort

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <string>
#include "UCIInterface.h"

using namespace std;

void main ( void )
{	
	string input, output;
	
	UCIInterface TheMasterUCI;
	TheMasterUCI.Command("perft");
	do
	{
		getline(cin, input);
		TheMasterUCI.Command(input);
		cout <<  output;
	}while ( input != "quit" );

	return;
}