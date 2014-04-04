/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "UCIInterface.h"
#include "Evaluate.h"
#include <boost/timer/timer.hpp>

UCIInterface::UCIInterface(void)
{
	cout << "UCI interface initialized" << endl;
}

void UCIInterface::Command(string command )
{
	if (command.length() == 0 ) 
		return;
	vector <string> tokens;

	//cout << "received " << command << " from user\n";
	// QUIT
	if ( command == "uci" )
	{
		cout << "id name TheMaster\n";
		cout << "id author Francisco Tort\n";
		return;
	}	if ( command == "quit" )
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
		cg.PrintBoard();
		return;
	}
	// UCInewgame
	if ( command == "ucinewgame" )
	{
		cg.Init();
		cout << "ok\n";
		return ;
	}
	// selftest
	if ( command == "bist" )
	{
		cout << "Running Built In Self Test\n";
		bist();		
		cout << "Built In Self Test Completed\n";
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
				cg.MakeMoveFromString(tokens[c]);
			}
		}
	}
	if (tokens[0] == "go")
	{
		int value;
		if ( cg.debug )	boost::timer::auto_cpu_timer tt(6, "info search took %w seconds\n");
		ClearSearchData();
		switch (cg.searchmethod)
		{
		case NEGAMAX:
			value = cg.NegaMax( cg.depth );
			break;
		case ALPHABETA:
			value = cg.AlphaBeta( cg.depth, -INFINITY, INFINITY);
			break;
		}
		PrintSearchData();
		ChessMove cm = cg.chessresult[cg.ply].best;
		cout <<  "info depth " << cg.depth << " score cp " << cg.chessresult[cg.ply + 1].value<< "\nbestmove " <<  cg.MakeAlgebraicMove(cm) <<  "\n";
	}
	if (tokens[0] == "debug")
	{
		if (tokens[1] == "on")
			cg.debug = true;
		if (tokens[1] == "off")
			cg.debug = false;
	}
	if (tokens[0] == "depth")
	{
		cg.depth = atoi(tokens[1].c_str());
	}
	if (tokens[0] == "search")
	{
		if (tokens[1] == "n")
			cg.searchmethod = NEGAMAX;
		if (tokens[1] == "ab")
			cg.searchmethod = ALPHABETA;
	}
	if (tokens[0] == "perft")
	{
#ifdef _DEBUG
		for ( int i = 1; i < 6; i++)
#else
		for ( int i = 1; i < 6; i++)
#endif
		{
			cg.Init();
			cg.Fen(STARTPOS);
			boost::timer::auto_cpu_timer tt(6, "Perf ran on %w seconds\n");
			cout << "perft for depth " << ( i ) << " is  " << cg.perft(i) << "\n";
		}
		return ;
	}
}
void UCIInterface::ClearSearchData(void)
{
	if ( cg.debug){
		cg.searchdata.maxdepth = 0;
		cg.searchdata.nodes = 0;
		cg.searchdata.legalnodes = 0;
		cg.searchdata.evaluates = 0;
		cg.searchdata.quietnodes = 0;
		cg.searchdata.regularnodes = 0;}
}
void UCIInterface::PrintSearchData(void)
{
	if (cg.debug){
		cout << "info MaxDepth = " << cg.searchdata.maxdepth;
		cout << " nodes = " << cg.searchdata.nodes << endl;
		cout << "info legalnodes = " << cg.searchdata.legalnodes;
		cout << " evaluates = " << cg.searchdata.evaluates << endl;
		cout << "info regular nodes = " << cg.searchdata.regularnodes << endl;
		cout << "info quietnodes = " << cg.searchdata.quietnodes << endl;}
}
/***********************************************************
* http://chessprogramming.wikispaces.com/Perft+Results#cite_note-4
*/
void UCIInterface::bist(void)
{
	cout << "Checking Move Generator\n";
	cg.Fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

	ASSERT (cg.perft(1) == 20);
	ASSERT (cg.perft(2) == 400);
	ASSERT (cg.perft(3) == 8902);
	ASSERT (cg.perft(4) == 197281);
	ASSERT (cg.perft(5) == 4865609);
	//ASSERT (cg.perft(6) == 119060324);

	cg.Fen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
	ASSERT (cg.perft(1) == 48);
	ASSERT (cg.perft(2) == 2039);
	ASSERT (cg.perft(3) == 97862);
	ASSERT (cg.perft(4) == 4085603);
	ASSERT (cg.perft(5) == 193690690);

	cg.Fen("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
	ASSERT (cg.perft(1) == 14);
	ASSERT (cg.perft(2) == 191);
	ASSERT (cg.perft(3) == 2812);
	ASSERT (cg.perft(4) == 43238);
	ASSERT (cg.perft(5) == 674624);
	cout << "Move Generator CHecked fine\n";
}
UCIInterface::~UCIInterface(void)
{
	cout << "UCI interface desrtucted" << endl;
}
