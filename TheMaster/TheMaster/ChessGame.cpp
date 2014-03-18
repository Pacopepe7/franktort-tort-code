/*
  TheMaster, a UCI chess playing engine 
  Copyright (C)2014 Francisco Tort

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
/**********************************************
* ChessGame.cpp
* Class implementing a chess playing engine.
* Francisco Tort
* Dec 30, 2009
*
*/
#include "ChessGame.h"

/**
* Chess Gane Constructor
*/
ChessGame::ChessGame ( ) 
{
	Init();
}
/**
* Init ()
* Sets the state of the internal chess engine to the starting position and resets all the flags
*/
void ChessGame::Init ( void ) 
{
	checkmate		= false;
	checkmated		= false;
	gameover		= false;
	depth			= 3;
	evaldepth		= 3;
	MODE			= CONSOLE;
	cb.Init();
}

/*********************************************
* Process UCI command 
* This function receives a string from the host
* and attempts to perform some action on the board/game
*/ 
string ChessGame::ProcessUCICommand( string command )
{
	long long value;
	string sValue = "";
	 vector<string> tokens;
	// QUIT
	if ( command == "quit" )
	{
		return "ok\n";
	}
	//ISREADY
	if ( command == "isready" )
	{
		return "readyok\n";
	}	
	//Stop
	if ( command == "stop" )
	{
		return "readyok\n";
	}	

	//PrintBoard
	if ( command == "pb" )
	{
		return cb.PrintBoard();
	}
	// UCInewgame
	if ( command == "ucinewgame" )
	{
		cb.Init();
		return "ok\n";
	}

	// check for positions
	Tokenize(command, tokens, " " );
	if (tokens[0] == "position" && tokens.size() > 1)
	{
		// this position starts from the initial position
		if ( tokens[1] == "startpos" )
		{
			cb.Init();
			if ( tokens.size() == 2 )
				return "\n";
			// start making moves on the internal board until no more moves
			for ( int c = 3; c < tokens.size(); c++)
			{
				//if (ValidateMove (  tokens[c] ) )
					//cb.MakeMove( ChessMove( tokens[c])) ;

			}
			return "";
		}
		// this position is encoded in FEN
		//not implemented
		return "Fen not implemented\n";
	}
	if (tokens[0] == "go")
	{
		value = NegaMax(cb, 4);
		sValue = std::to_string(value);
		return "info depth 4 score cp " + sValue + "\nbestmove " + cb.BestSoFar.ToString() + "\n";
	}
	if (tokens[0] == "perft")
	{
		long long depth = atoi(tokens[1].c_str());
		value = perft(cb,int( depth));
		sValue = std::to_string(value);
		return "perft for depth " + std::to_string(depth) + " is  " + sValue + "\n";
	}
	return "Not implemented\n";

} // end process command


/**
* GetIndex calls the GetIndex method on the board object
*  This is to get indexes for castling etc...
*/
int ChessGame::getIndex( string s)
{
	return cb.getIndex( s );
}

/*******************************************
* ValidateMove
* This function takes a string and returns if this move can acutally be made in the
* context of a chess game. It will attempt to make this move on a real chess board
* So that hidden discoveries are detected. It uses the copy constructor
*/
bool ChessGame::ValidateMove ( string command )
{
	return true;
	////make sure there is always a good copy of chessboard, make all operations on backup, do not
	//// alter cb until actually making the move
	//ChessBoard backup = ChessBoard ( cb );
	//backup.GenerateMoves();
	//ChessMove cm, goodchessmove;
	////check if the move is in the move stack
	//while ( ! backup.chessmoves.empty())
	//{
	//	cm = backup.chessmoves.top();
	//	backup.chessmoves.pop();


	//	if ( cm.ToString() == ( command ) )
	//	{
	//		// the move is in the stack, but can it actually be made on the board?
	//		if ( backup.MakeMove ( cm ) )
	//		{
	//			// success!
	//			//System.out.println("Move " + command + " is valid! ( ValidateMove )");
	//			return true;
	//		}
	//	} // end if
	//} // end while
	////System.out.println("Move " + command + " is invalid ( ValidateMove )");
	//return (false);
} 
/*******************************************
* ReturnValidatedMove( command )
* takes a string and returns the chess move corresponding to the command
*/
ChessMove ChessGame::ReturnValidatedMove( string command )
{
	//cb.GenerateMoves();
	//ChessMove cm;
	//while ( ! cb.chessmoves.empty())
	//{
	//	cm = (ChessMove) cb.chessmoves.top();
	//	cb.chessmoves.pop();

	//	if ( cm.ToString() == ( command ) )
	//	{
	//		//System.out.println("Success, move " + command + " was found to be legal on this position! (ReturnValidatedMove)");

	//		return cm;
	//	} // end if
	//} // end while
	////System.out.println("Error, move " + command + " was found not to be legal on this position! (ReturnValidatedMove)");

	//return ( cb.nullmove );
}
/*********************************************
* Process command 
* This function receives a string from the host and attempts to perform some action on the board/game
* valid commands right now:
* new
* valid chess moves from the current position
*/ 
string ChessGame::ProcessCommand( string command )
{
	/*long long sq = getIndex(command);
	std::string s = to_string(sq);
	return "Square is " + s ;*/

	if ( MODE == UCI )
		return ProcessUCICommand(command);
	//if ( MODE == ICC )
	//	ProcessICCCommand(command);

	string responce;
	//  UCI
	if ( command == "uci" )
	{
		MODE = UCI;
		responce += "id name TheMaster\n";
		responce += "id author Francisco Tort\n";
		//responce += "option\n";
		responce += "uciok\n";
		//responce += "option name ky value";
		return responce;
	}
	// QUIT
	if ( command == "quit" )
	{
		return "ok\n";
	}

	return "";
} // end process command

/***
* getResponce ( ) 
* returns a string that corresponds to the computer move in computer algebraic
* This is the function that calls the search function and interprets the results
*
string ChessGame::getResponce( void ) 
{

	int legalmoves = 0;
	int movestomate = 0;
	bool foundmate = false;

	ChessMove cm = ChessMove( "a2a4");
	cb.GenerateMoves();
	while ( ! cb.chessmoves.empty() )
	{
		cm = cb.chessmoves.top();
		cb.chessmoves.pop();

		//ChessBoard temp = new ChessBoard ( cb );
		temp[depth] = ChessBoard( cb );
		// for each move that is valid...
		if (  temp[depth].MakeMove( cm ) )
		{
			// found at least one valid move
			legalmoves++;
			cm.value = -30000;
			// set the parent so we know which move is best so far
			//temp.parent = cb;
			// return the negative of evaluate because we are interested in the best score for this side.
			//cm.value = temp.evaluate();
			//if ( drawcheck( temp[depth] ) ) 
			// cm.value = 0;
			//else
			cm.value = -NegaMax( temp[depth] , depth - 1);
			//cm.value = -AlphaBeta( temp[depth] , depth - 1, -40000, 40000);
			//System.out.println("Move " + cm.out() + " value is : " + cm.value);


			//if this move value > than current best.value, swap moves (update king of the hill)
			if ( legalmoves != 0 )
			{
				if ( legalmoves == 1) // special case for first move
				{
					cb.BestSoFar = cm;
					//System.out.println("Only so far = " + cm.out());
				}
				else // best so far exists, update if necessary
				{
					if ( cb.BestSoFar.value <= cm.value )
					{
						cb.BestSoFar = cm;
						//System.out.println("Best so far = " + cm.out());
					}
				}
			} // end if legal moves != 0
		} // end validate move
	} // end while chessmoves.empty()

	//All the moves have been evaluated

	//return appropiate value if no moves found, this does not need to return a value because there is
	// no where to return it to.
	if ( legalmoves == 0 ) 
	{
		if ( cb.sidetomove == WHITE )
		{
			if ( cb.IsAttacked( cb.whitekingposition, BLACK ) > 0) // white to move and white is attacked. Mate!
			{
				//System.out.println("Its mate!");
				gameover = true;

			}
			else
			{
				//System.out.println("Stalemate!");
				gameover = true;

			}
		}
		else // cb.tomove == BLACK
		{
			if ( cb.IsAttacked( cb.blackkingposition, WHITE ) > 0) // black to move and black is attacked. Mate!
			{
				//System.out.println("Its mate!");
				gameover = true;

			}
			else
			{
				//System.out.println("Stalemate!");
				gameover = true;

			}
		} // endif
	}

	if (legalmoves > 0 )
	{
		//System.out.println("Returning best so far: " + cb.bestsofar.out() + " score: " + cb.bestsofar.value );
		return cb.BestSoFar.ToString();
	}
	else
		return "Game is over";
}

*/

int ChessGame::perft(ChessBoard & currentBoard, int depth)
{
	unsigned int legalmoves = 0;
	unsigned int movebeingevaluated;
	if ( depth == -1)
	{
		legalmoves = 0;
		return 0;
	}
	if ( depth == 0 ) 
		return 1;
	while ( ! currentBoard.CMEMPTY() )
		currentBoard.CMPOP();
	ChessBoard moveGenBoard = currentBoard;
	ChessBoard temp = currentBoard;
	ChessBoard recursive = currentBoard;

	moveGenBoard.GenerateIntMoves();
	
	while ( ! moveGenBoard.CMEMPTY() )
	{
		movebeingevaluated = moveGenBoard.CMPOP();
		temp = currentBoard;
		recursive = currentBoard;
		if (temp.MakeIntMove( movebeingevaluated ) )
		{
			recursive.MakeIntMove(movebeingevaluated);
			legalmoves += perft( recursive, depth - 1);
		}
	}
	return legalmoves;
} 

