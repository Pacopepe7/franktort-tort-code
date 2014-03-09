/*
  TheMaster, a UCI chess playing engine 
  Copyright (C)2014 Francisco Tort

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <fstream>
#include <string>
#include "ChessGame.h"



using namespace std;

void main ( void )
{
	ChessGame TheMasterDriver;
	
	//Start a log file for commands
	//fstream ofile;
	//ofile.open("logfile.txt",ios::app);

	string input, output;

	do
	{
		getline(cin, input);
		
		input = input;
		//ofile << input << endl;

		output =  TheMasterDriver.ProcessCommand(input);
		//ofile << output;

		cout <<  output;

	}while ( input != "quit" );

	//ofile.close();
	return;
}