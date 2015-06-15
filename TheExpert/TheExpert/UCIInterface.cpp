/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "UCIInterface.h"
#include "utils.h"
#include "stdlib.h"
#include "stdio.h"
#include "windows.h"

#include <boost/timer/timer.hpp>
#include <boost/chrono/include.hpp>

using namespace boost;
typedef boost::timer::auto_cpu_timer btimer;
typedef boost::chrono::duration<double> sec;

//#include "Evaluate.h"

UCIInterface::UCIInterface(void)
{
	cout << "UCI interface initialized" << endl;
	chessPosition = (ChessPosition *)malloc(sizeof(ChessPosition));
	cout << "Allocated memory for ChessPosition" << endl;
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
		InitializeBoard(chessPosition);
		SetFen(chessPosition, STARTPOS);
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
		PrintBoard(chessPosition);
		return;
	}
	// UCInewgame
	if ( command == "ucinewgame" )
	{
		SetFen(chessPosition, STARTPOS);
		//SetFen(chessPosition, "7k/p7/1R5K/6r1/6p1/6P1/8/8 w - - 0 1 ");
		//cg.Fen("r4q1k/p2bR1rp/2p2Q1N/5p2/5p2/2P5/PP3PPP/R5K1 w - - 0 0");
		//cg.Fen("8/7p/5k2/5p2/p1p2P2/Pr1pPK2/1P1R3P/8 b - - 0 0");
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
		SetFen(chessPosition, STARTPOS);
		// this position starts from the initial position
		if ( tokens[1] == "startpos" )
		{
			
			if ( tokens.size() == 2 ){
				cout << endl; return;}
			// start making moves on the internal board until no more moves
			for ( int c = 3; c < tokens.size(); c++)
			{
				MakeMove(chessPosition,	MakeMoveFromString(chessPosition, tokens[c]));
			}
		}
		if ( tokens[1] == "fen")
		{
			SetFen(chessPosition, command.substr(13, 200));
			for ( int c = 0; c < tokens.size(); c++)
			{
				if ( tokens[c] == "moves" )
				{	
					for ( int cc = c + 1; cc < tokens.size(); cc++)
						MakeMove(chessPosition, MakeMoveFromString(chessPosition, tokens[cc]));
				}
			}
		}
	}
	//// go depth 6 wtime 180000 btime 100000 binc 1000 winc 1000 movetime 1000 movestogo 40

	if (tokens[0] == "go")
	{
		S_SEARCHINFO info;
		int i = 0;
		int depth = -1, movestogo = 30, movetime = -1;
		int time = -1, inc = 0;
		info.timeset = FALSE;
		do{
			if (tokens[i] == "infinite"){
				movetime = 14500;
				time = 14500;
				movestogo = 1;
				//cout << "info depth: " << info.depth;
			}
			if (tokens[i] == "depth"){
				info.depth = atoi(tokens[i + 1].c_str());
				depth = info.depth;
				//cout << "info depth: " << info.depth;
			}

			if (tokens[i] == "movestogo"){
				info.movestogo = atoi(tokens[i + 1].c_str());
				//cout << "info movestogo: " << info.movestogo;
			}

			if ((tokens[i] == "wtime") && (chessPosition->sideToMove == WHITE)) {
				time = atoi(tokens[i + 1].c_str());
				//cout << "info time: " << time;
			}
			if ((tokens[i] == "btime") && (chessPosition->sideToMove == BLACK)) {
				time = atoi(tokens[i + 1].c_str());
				//cout << "info time: " << time;
			}

			if (tokens[i] == "movetime") 
				movetime = atoi(tokens[i + 1].c_str());
			
		} while (++i < tokens.size());

		info.starttime = GetTickCount();
		info.depth = depth;
		cout << "info starttime: " << info.starttime;
		if (time != -1) {
			info.timeset = TRUE;
			time /= movestogo;
			time -= 50;
			info.stoptime = info.starttime + time + inc;
		}
		if (movetime != -1) {
			info.timeset = TRUE;
			info.stoptime = info.starttime + movetime + inc;
		}
		if (depth == -1) {
			info.depth = 15;
		}
		cout << " info depth: " << info.depth;
		cout << " movestogo: " << movestogo;
		cout << " starttime: " << info.starttime;
		cout << " stoptime: " << info.stoptime << endl;
		AlphaBetaDriver(chessPosition, &info);
		
	}
	if (tokens[0] == "debug")
	{
		//if (tokens[1] == "on")
		//	cg.debug = true;
		//if (tokens[1] == "off")
		//	cg.debug = false;
	}
	if (tokens[0] == "pb")
	{
		PrintBoard(chessPosition);
	}

	if (tokens[0] == "depth")
	{
		//cg.depth = atoi(tokens[1].c_str());
	}
	if (tokens[0] == "test"){
		//cg.Fen("8/7p/3k4/8/p4P2/P3PK2/2Rp3P/8 b - - 0 12 ");
		SetFen(chessPosition, "3r1k2/1p4p1/pRB2p2/P1P1p2p/4P3/2P1BbPP/5P1K/2Rr4 b - - 0 1");
	}
	if (tokens[0] == "search")
	{
		//if (tokens[1] == "n")
		//	cg.searchmethod = NEGAMAX;
		//if (tokens[1] == "ab")
		//	cg.searchmethod = ALPHABETA;
	}
	if (tokens[0] == "perft")
	{
		sec 	seconds;
		sec last(0);
		boost::timer::cpu_timer timer;
#ifdef _DEBUG
		for ( int i = 1; i < 7; i++)
#else
		for ( int i = 1; i <= 6; i++)
#endif
		{
			
			cout << "Starting perft " << i << endl;
			
			InitializeBoard(chessPosition);
			SetFen(chessPosition, STARTPOS);
			cout << "perft for depth " << (i) << " is  " << perft(chessPosition, i) << "\n";
			seconds = boost::chrono::nanoseconds(timer.elapsed().user) - last; last = seconds;
			cout << "Perft completed on : " << seconds.count() << endl;
		}
		//PrintBoard(chessPosition);
		return ;
	}
}


/***********************************************************
* http://chessprogramming.wikispaces.com/Perft+Results#cite_note-4
*/
void UCIInterface::bist(void)
{
	//boost::timer::auto_cpu_timer tt(6, "Built in Self Test took %w seconds\n");
	cout << "Checking Move Generator\n";
	
	//SetFen(chessPosition, STARTPOS);
	SetFen(chessPosition, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	//cg.PrintBoard();
	ASSERT(perft(chessPosition, 1) == 20);
		cout << "Init perft(1) OK!\n";

		ASSERT(perft(chessPosition, 2) == 400);
	cout << "Init perft(2) OK!\n"; 
	ASSERT(perft(chessPosition, 3) == 8902);
		cout << "Init perft(3) OK!\n";
		ASSERT(perft(chessPosition, 4) == 197281);
		cout << "Init perft(4) OK!\n";
		ASSERT(perft(chessPosition, 5) == 4865609);
		cout << "Init perft(5) OK!\n";
		ASSERT(perft(chessPosition, 6) == 119060324);
		cout << "Init perft(6) OK!\n";
	//cg.PrintBoard();
	SetFen(chessPosition, "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
	////cg.PrintBoard();
	ASSERT(perft(chessPosition, 1) == 48);
		cout << "Test pos 2 perft(1) OK!\n";
		ASSERT(perft(chessPosition, 2) == 2039);
		cout << "Test pos 2 perft(2) OK!\n";
		ASSERT(perft(chessPosition, 3) == 97862);
		cout << "Test pos 2 perft(3) OK!\n";
		ASSERT(perft(chessPosition, 4) == 4085603);
		cout << "Test pos 2 perft(4) OK!\n";
		ASSERT(perft(chessPosition, 5) == 193690690);
		cout << "Test pos 2 perft(5) OK!\n";
	////cg.PrintBoard();
	SetFen(chessPosition, "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
	////cg.PrintBoard();
	ASSERT(perft(chessPosition, 1) == 14);
		cout << "Test pos 3 perft(1) OK!\n";
		ASSERT(perft(chessPosition, 2) == 191);
		cout << "Test pos 3 perft(2) OK!\n";
		ASSERT(perft(chessPosition, 3) == 2812);
		cout << "Test pos 3 perft(3) OK!\n";
		ASSERT(perft(chessPosition, 4) == 43238);
		cout << "Test pos 3 perft(4) OK!\n";
		ASSERT(perft(chessPosition, 5) == 674624);
		cout << "Test pos 3 perft(5) OK!\n";
	//cg.PrintBoard();
	SetFen(chessPosition, "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
	//cg.PrintBoard();
	ASSERT(perft(chessPosition, 1) == 6);
		cout << "Test pos 4 perft(1) OK!\n";
		ASSERT(perft(chessPosition, 2) == 264);
		cout << "Test pos 4 perft(2) OK!\n";
		ASSERT(perft(chessPosition, 3) == 9467);
		cout << "Test pos 4 perft(3) OK!\n";
		ASSERT(perft(chessPosition, 4) == 422333);
		cout << "Test pos 4 perft(4) OK!\n";
		ASSERT(perft(chessPosition, 5) == 15833292);
		cout << "Test pos 4 perft(5) OK!\n";
	//cg.PrintBoard();
	SetFen(chessPosition, "rnbqkb1r/pp1p1ppp/2p5/4P3/2B5/8/PPP1NnPP/RNBQK2R w KQkq - 0 6");
	//cg.PrintBoard();
	ASSERT(perft(chessPosition, 1) == 42);
		cout << "Test pos 5 perft(1) OK!\n";
		ASSERT(perft(chessPosition, 2) == 1352);
		cout << "Test pos 5 perft(2) OK!\n";
		ASSERT(perft(chessPosition, 3) == 53392);
		cout << "Test pos 5 perft(3) OK!\n";
	//cg.PrintBoard();
	SetFen(chessPosition, "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
	//cg.PrintBoard();
	ASSERT(perft(chessPosition, 1) == 46);
		cout << "Test pos 6 perft(1) OK!\n";
		ASSERT(perft(chessPosition, 2) == 2079);
		cout << "Test pos 6 perft(2) OK!\n";
		ASSERT(perft(chessPosition, 3) == 89890);
		cout << "Test pos 6 perft(3) OK!\n";
		ASSERT(perft(chessPosition, 4) == 3894594);
		cout << "Test pos 6 perft(4) OK!\n";
		ASSERT(perft(chessPosition, 5) == 164075551);
		cout << "Test pos 6 perft(5) OK!\n";
	//cg.PrintBoard();
	SetFen(chessPosition, "8/3K4/2p5/p2b2r1/5k2/8/8/1q6 b - - 1 67");
	ASSERT(perft(chessPosition, 1) == 50);
		cout << "Test pos 7 perft(1) OK!\n";
		ASSERT(perft(chessPosition, 2) == 279);
		cout << "Test pos 7 perft(2) OK!\n";
	
	SetFen(chessPosition, "8/7p/p5pb/4k3/P1pPn3/8/P5PP/1rB2RK1 b - d3 0 28");
	ASSERT(perft(chessPosition, 6) == 38633283);
		cout << "Test pos 8 perft(6) OK!\n";
	
	SetFen(chessPosition, "rnbqkb1r/ppppp1pp/7n/4Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");
	ASSERT(perft(chessPosition, 5) == 11139762);
		cout << "Test pos 9 perft(5) OK!\n";
	
	SetFen(chessPosition, "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
	ASSERT(perft(chessPosition, 6) == 11030083);
		cout << "Test pos 10 perft(6) OK!\n";
		ASSERT(perft(chessPosition, 7) == 178633661);
		cout << "Test pos 10 perft(7) OK!\n";
	
	cout << "Move Generator Checked fine\n";
}
//1rbq1rk1/p1b1nppp/1p2p3/8/1B1pN3/P2B4/1P3PPP/2RQ1R1K w - - 0 1
UCIInterface::~UCIInterface(void)
{
	cout << "UCI interface desrtucted" << endl;
}
