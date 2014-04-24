/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "UCIInterface.h"
#include "Evaluate.h"


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
		cout << "uciok\n";
		cg.Init();
		cg.Fen(STARTPOS);
		return;
	}	
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
		cg.PrintBoard();
		return;
	}
	// UCInewgame
	if ( command == "ucinewgame" )
	{
		cg.Init();
		cg.Fen(STARTPOS);
		cg.Fen("8/7p/5k2/5p2/p1p2P2/Pr1pPK2/1P1R3P/8 b - - 0 0");
		//r1b2r1k/ppp1q2p/2nppp1Q/3n4/7B/2PB1N2/PPP2PPP/R4RK1 w - - 2 13 
		//cg.Fen("r1b2r1k/ppp1q2p/2nppp1Q/3n4/7B/2PB1N2/PPP2PPP/R4RK1 w - - 2 13");
		//cg.Fen("rnbqkb1r/pppp1ppp/8/4P3/6n1/7P/PPPNPPP1/R1BQKBNR b KQkq - 1 0");
		//cg.Fen("r2qkb1r/1ppb1ppp/p7/4p3/P1Q1P3/2P5/5PPP/R1B2KNR b kq - 1 0");
		//Command("position fen b2b1r1k/3R1ppp/4qP2/4p1PQ/4P3/5B2/4N1K1/8 w - - 0 1 moves g5g6 h7h6 h5h6 g7h6 g6g7 h8g8 g7f8q g8h7");
		//cg.Fen("1k1r4/pp3R2/6pp/4p3/2B3b1/4Q3/PPP2B2/2K5 b - - 0 1");
		//cg.Fen("1k1r4/pp1b1R2/3q2pp/4p3/2B5/4Q3/PPP2B2/2K5 b - - 0 0");
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
			cg.Fen(STARTPOS);
			if ( tokens.size() == 2 ){
				cout << endl; return;}
			// start making moves on the internal board until no more moves
			for ( int c = 3; c < tokens.size(); c++)
			{
				cg.MakeMoveFromString(tokens[c]);
			}
		}
		if ( tokens[1] == "fen")
		{
			cg.Fen(command.substr(13, 200));
			for ( int c = 0; c < tokens.size(); c++)
			{
				if ( tokens[c] == "moves" )
				{	
					for ( int cc = c + 1; cc < tokens.size(); cc++)
						cg.MakeMoveFromString(tokens[cc]);
				}
			}
			//cg.PrintBoard();
		}
	}
	if (tokens[0] == "go")
	{

		sec seconds;
		int value;
		boost::timer::auto_cpu_timer tt(6, "info search took %w seconds\n");
		
		switch (cg.searchmethod)
		{
		case NEGAMAX:
			value = cg.NegaMax( cg.depth );
			break;
		case ALPHABETA:
			value = cg.AlphaBetaDriver( );
				break;
		default:
			cout << "Search method Invalid!\n";
			break;
		}
		
		ChessMove cm = cg.chessresult[cg.ply].best;
		cout <<  "info depth " << cg.depth << " score cp " << cg.chessresult[cg.ply ].value<< "\nbestmove " <<  cg.MakeAlgebraicMove(cm) <<  "\n";
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
		for ( int i = 1; i < 4; i++)
#else
		for ( int i = 1; i < 5; i++)
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


/***********************************************************
* http://chessprogramming.wikispaces.com/Perft+Results#cite_note-4
*/
void UCIInterface::bist(void)
{
	boost::timer::auto_cpu_timer tt(6, "Built in Self Test took %w seconds\n");
	cout << "Checking Move Generator\n";
	cg.Fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	cg.PrintBoard();
	ASSERT (cg.perft(1) == 20);				cout << "Init perft(1) OK!\n";
	ASSERT (cg.perft(2) == 400);			cout << "Init perft(2) OK!\n";
	ASSERT (cg.perft(3) == 8902);			cout << "Init perft(3) OK!\n";
	ASSERT (cg.perft(4) == 197281);			cout << "Init perft(4) OK!\n";
	ASSERT (cg.perft(5) == 4865609);		cout << "Init perft(5) OK!\n";
	//ASSERT (cg.perft(6) == 119060324);		cout << "Init perft(6) OK!\n";
	cg.PrintBoard();
	cg.Fen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
	cg.PrintBoard();
	ASSERT (cg.perft(1) == 48);				cout << "Test pos 2 perft(1) OK!\n";
	ASSERT (cg.perft(2) == 2039);			cout << "Test pos 2 perft(2) OK!\n";
	ASSERT (cg.perft(3) == 97862);			cout << "Test pos 2 perft(3) OK!\n";
	ASSERT (cg.perft(4) == 4085603);		cout << "Test pos 2 perft(4) OK!\n";
	ASSERT (cg.perft(5) == 193690690);		cout << "Test pos 2 perft(5) OK!\n";
	cg.PrintBoard();
	cg.Fen("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
	cg.PrintBoard();
	ASSERT (cg.perft(1) == 14);				cout << "Test pos 3 perft(1) OK!\n";
	ASSERT (cg.perft(2) == 191);			cout << "Test pos 3 perft(2) OK!\n";
	ASSERT (cg.perft(3) == 2812);			cout << "Test pos 3 perft(3) OK!\n";
	ASSERT (cg.perft(4) == 43238);			cout << "Test pos 3 perft(4) OK!\n";
	ASSERT (cg.perft(5) == 674624);			cout << "Test pos 3 perft(5) OK!\n";
	cg.PrintBoard();
	cg.Fen("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
	cg.PrintBoard();
	ASSERT (cg.perft(1) == 6);				cout << "Test pos 4 perft(1) OK!\n";
	ASSERT (cg.perft(2) == 264);			cout << "Test pos 4 perft(2) OK!\n";
	ASSERT (cg.perft(3) == 9467);			cout << "Test pos 4 perft(3) OK!\n";
	ASSERT (cg.perft(4) == 422333);			cout << "Test pos 4 perft(4) OK!\n";
	ASSERT (cg.perft(5) == 15833292);		cout << "Test pos 4 perft(5) OK!\n";
	cg.PrintBoard();
	cg.Fen("rnbqkb1r/pp1p1ppp/2p5/4P3/2B5/8/PPP1NnPP/RNBQK2R w KQkq - 0 6");
	cg.PrintBoard();
	ASSERT (cg.perft(1) == 42);				cout << "Test pos 5 perft(1) OK!\n";
	ASSERT (cg.perft(2) == 1352);			cout << "Test pos 5 perft(2) OK!\n";
	ASSERT (cg.perft(3) == 53392);			cout << "Test pos 5 perft(3) OK!\n";
	cg.PrintBoard();
	cg.Fen("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
	cg.PrintBoard();
	ASSERT (cg.perft(1) == 46);				cout << "Test pos 6 perft(1) OK!\n";
	ASSERT (cg.perft(2) == 2079);			cout << "Test pos 6 perft(2) OK!\n";
	ASSERT (cg.perft(3) == 89890);			cout << "Test pos 6 perft(3) OK!\n";
	ASSERT (cg.perft(4) == 3894594);		cout << "Test pos 6 perft(4) OK!\n";
	ASSERT (cg.perft(5) == 164075551);		cout << "Test pos 6 perft(5) OK!\n";
	cg.PrintBoard();
	//ASSERT (cg.perft(6) == 6923051137);		cout << "Test pos 6 perft(6) OK!\n";

	cout << "Move Generator Checked fine\n";
}
//1rbq1rk1/p1b1nppp/1p2p3/8/1B1pN3/P2B4/1P3PPP/2RQ1R1K w - - 0 1
UCIInterface::~UCIInterface(void)
{
	cout << "UCI interface desrtucted" << endl;
}
