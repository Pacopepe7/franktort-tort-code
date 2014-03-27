/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "UCIInterface.h"

UCIInterface::UCIInterface(void)
{
	cout << "UCI interface initialized" << endl;
}

void UCIInterface::Command(string command )
{
	if (command.length() == 0 ) 
		return;
	vector <string> tokens;

	cout << "received " << command << " from user\n";
	// QUIT
	if ( command == "quit" )
	{
		cout << "ok\n";
		return;
	}
	//ISREADY
	if ( command == "isready" )
	{
		cout << "readyok\n";
		return;
	}	
	//Stop
	if ( command == "stop" )
	{
		cout << "readyok\n";
		return;
	}	

	//PrintBoard
	if ( command == "pb" )
	{
		//cout << cg.PrintBoard();
		return;
	}
	// UCInewgame
	if ( command == "ucinewgame" )
	{
		cg.Init();
		cout << "ok\n";
		return ;
	}
	// check for positions
	Tokenize(command, tokens, " " );
	if (tokens[0] == "position" && tokens.size() > 1)
	{
		// this position starts from the initial position
		if ( tokens[1] == "startpos" )
		{
			cg.Init();
			if ( tokens.size() == 2 ){
				cout << endl; return;}
			// start making moves on the internal board until no more moves
			for ( int c = 3; c < tokens.size(); c++)
			{
				cg.MakeMove(tokens[c]);
			}
		}
	}
	if (tokens[0] == "go")
	{
		//depth = 5;
		//value = NegaMax(cb, (int)depth);
		//sValue = std::to_string(value);
		//sDepth = std::to_string(depth);
		//return "info depth " + sDepth + " score cp " + sValue + "\nbestmove " + cb.MakeString(cb.m_boardState.m_BestSoFar) + "\n";
	}

	if (tokens[0] == "perft")
	{


		for ( int i = 0; i < 2; i++)
		{


			cout << "perft for depth " << (i + 1) << " is  " << cg.perft(i) << "\n";
			return ;
		}
	}


}
UCIInterface::~UCIInterface(void)
{
	cout << "UCI interface desrtucted" << endl;
}
