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
				return "";
			// start making moves on the internal board until no more moves
			for ( int c = 2; c < tokens.size(); c++)
			{
				if (ValidateMove (  tokens[c] ) )
					cb.MakeMove( ReturnValidatedMove( tokens[c] )) + "\n";

			}
			return "";
		}
		// this position is encoded in FEN
		//not implemented
		return "";
	}
	if (tokens[0] == "go")// && tokens.size() > 1)
	{
		int value = NegaMax(cb, depth);
	}
	return temp[cb.ply+1].BestSoFar.ToString();

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
	//make sure there is always a good copy of chessboard, make all operations on backup, do not
	// alter cb until actually making the move
	ChessBoard backup = ChessBoard ( cb );
	backup.GenerateMoves();
	ChessMove cm, goodchessmove;
	//check if the move is in the move stack
	while ( ! backup.chessmoves.empty())
	{
		cm = backup.chessmoves.top();
		backup.chessmoves.pop();


		if ( cm.ToString() == ( command ) )
		{
			// the move is in the stack, but can it actually be made on the board?
			if ( backup.MakeMove ( cm ) )
			{
				// success!
				//System.out.println("Move " + command + " is valid! ( ValidateMove )");
				return true;
			}
		} // end if
	} // end while
	//System.out.println("Move " + command + " is invalid ( ValidateMove )");
	return (false);
} 
/*******************************************
* ReturnValidatedMove( command )
* takes a string and returns the chess move corresponding to the command
*/
ChessMove ChessGame::ReturnValidatedMove( string command )
{
	cb.GenerateMoves();
	ChessMove cm;
	while ( ! cb.chessmoves.empty())
	{
		cm = (ChessMove) cb.chessmoves.top();
		cb.chessmoves.pop();

		if ( cm.ToString() == ( command ) )
		{
			//System.out.println("Success, move " + command + " was found to be legal on this position! (ReturnValidatedMove)");

			return cm;
		} // end if
	} // end while
	//System.out.println("Error, move " + command + " was found not to be legal on this position! (ReturnValidatedMove)");

	return ( cb.nullmove );
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

	//Convert input to lower case...


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
		responce += "\tid author Francisco Tort\n";
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

/**************************************************************
* Alpha beta
*
int ChessGame::AlphaBeta( ChessBoard currentnode, int currentdepth, int alpha, int beta ) 
{

	if ( currentdepth <= 0 ) 
		//return Quiet ( arg , depth - 1 );
		//return currentnode.Evaluate (  );
	//return QuietAlphaBeta( currentnode, currentdepth, alpha, beta );

	//if ( drawcheck( currentnode ) ) 
	// return ( 0 );

	int legalmoves = 0;
	int movestomate = 0;
	bool foundmate = false;

	ChessMove cm = ChessMove("a2a4");
	ChessMove extramove = ChessMove ("a2a4");
	cm.value = -30000;

	currentnode.GenerateMoves();
	while ( ! currentnode.chessmoves.empty() )
	{
		cm = currentnode.chessmoves.top();
		currentnode.chessmoves.pop();

		//ChessBoard temp = new ChessBoard ( arg );
		//temp[depth].copy(currentnode);
		temp[currentnode.ply] = ChessBoard(currentnode);
		// for each move that is valid...
		if (  temp[currentnode.ply].MakeMove( cm ) )
		{
			// found at least one valid move
			legalmoves++;
			// set the value of the current move very low so it gets replaced immediately
			cm.value = -30000;
			// return the negative of evaluate because we are interested in the best score for this side.
			//System.out.println("Searching ply : " + currentnode.ply);
			//if ( cm.capture && currentdepth == 1 )
			// cm.value = -AlphaBeta( temp[currentnode.ply], currentdepth , -beta, -alpha);
			//else
			cm.value = -AlphaBeta( temp[currentnode.ply], currentdepth - 1, -beta, -alpha);

			//System.out.println("Move " + cm.out() + " value is : " + cm.value);


			//if this move value > than current best.value, swap moves (update king of the hill)
			if ( legalmoves != 0 )
			{
				if ( legalmoves == 1) // special case for only move
				{
					currentnode.BestSoFar = cm;
					//System.out.println("Only so far = " + cm.out());
				}
				else // best so far exists, update if necessary
				{
					if ( cm.value >= beta)
					{
						//return beta;
						//currentnode.bestsofar = cm;
						while ( ! currentnode.chessmoves.empty() )
							extramove = currentnode.chessmoves.top();
						//break; // pump all the moves from stack?
						return beta;
					}       
					if ( cm.value > alpha )
					{
						currentnode.BestSoFar = cm;
						alpha = cm.value;
						//System.out.println("Best so far = " + cm.out());
					}
				}
			} // end if legal moves != 0
		} // end validate move
	} // end while chessmoves.empty()

	//All the moves have been evaluated

	//return appropiate value if no moves found.
	// 
	if ( legalmoves == 0 ) 
	{
		if ( currentnode.sidetomove == WHITE )
		{
			if ( currentnode.IsAttacked( currentnode.whitekingposition, BLACK ) > 0) // white to move and white is attacked. Mate!
			{
				//gameover = true;
				return ( -32000 + currentnode.ply );
			}
			else
			{
				//gameover = true;
				return ( 0 +  currentnode.ply);
			}
		}
		else // cb.tomove == BLACK
		{
			if ( currentnode.IsAttacked( currentnode.blackkingposition, WHITE ) > 0) // black to move and black is attacked. Mate!
			{
				//gameover = true;
				return ( -32000  +  currentnode.ply );
			}
			else
			{
				//gameover = true;
				return ( 0 +  currentnode.ply);
			}
		} // endif
	}
	else
	{
		//System.out.println("Returning best so far: " + arg.bestsofar.out());
		//arg.bestsofar = cm;
		return currentnode.BestSoFar.value;
	}
}
*/
/**************************************************************
* Negamax, very ineficient, but simple
* Drops out after depth 3.
*/
int ChessGame::NegaMax( ChessBoard currentnode, int currentdepth ) 
{

	if ( currentdepth <= 0 ) 
		return currentnode.Evaluate(  );
	if ( currentnode.ply > (cb.ply + 3))
		return currentnode.Evaluate(  );

	//return QuietAlphaBeta( currentnode , currentdepth + 1, -35000, 35000 );
	//return QuietAlphaBeta ( currentnode , depth + 1, -40000, 40000 );
	//return currentnode.evaluate ( this );

	//if ( drawcheck( currentnode ) ) 
	// return ( 0 );

	int legalmoves = 0;
	int movestomate = 0;
	bool foundmate = false;

	ChessMove cm = ChessMove( "a2a4");
	cm.value = -30000;

	currentnode.GenerateMoves();
	while ( ! currentnode.chessmoves.empty() )
	{
		cm = currentnode.chessmoves.top();
		currentnode.chessmoves.pop();

		//ChessBoard temp = new ChessBoard ( arg );
		//temp[depth].copy(currentnode);
		temp[currentnode.ply] =  ChessBoard(currentnode);
		// for each move that is valid...
		if ( temp[currentnode.ply].MakeMove( cm ) )
		{
			// found at least one valid move
			legalmoves++;
			// set the value of the current move very low so it gets replaced immediately
			cm.value = -30000;

			// return the negative of evaluate because we are interested in the best score for this side.
			if ( (currentdepth == 1) && ( cm.capture ) )
			{
				cm.value = -NegaMax( temp[currentnode.ply], currentdepth );
			}
			else
				cm.value = -NegaMax( temp[currentnode.ply], currentdepth - 1);
			//System.out.println("Move " + cm.out() + " value is : " + cm.value);
			//System.out.println("Searching ply : " + currentnode.ply);


			//if this move value > than current best.value, swap moves (update king of the hill)
			if ( legalmoves != 0 )
			{
				if ( legalmoves == 1) // special case for first move
				{
					currentnode.BestSoFar = cm;
					temp[currentnode.ply].BestSoFar = cm;
					//System.out.println("Only so far = " + cm.out());
				}
				else // best so far exists, update if necessary
				{
					if ( cm.value >= currentnode.BestSoFar.value )
					{
						currentnode.BestSoFar = cm;
						temp[currentnode.ply].BestSoFar = cm;
						//System.out.println("Best so far = " + cm.out());
					}
				}
			} // end if legal moves != 0
		} // end validate move
	} // end while chessmoves.empty()

	//All the moves have been evaluated

	//return appropiate value if no moves found.
	// 
	if ( legalmoves == 0 ) 
	{
		if ( currentnode.sidetomove == WHITE )
		{
			if ( currentnode.IsAttacked( currentnode.whitekingposition, BLACK ) > 0) // white to move and white is attacked. Mate!
			{
				//gameover = true;
				return ( -32000 + currentnode.ply );
			}
			else
			{
				//gameover = true;
				return ( 0 +  currentnode.ply);
			}
		}
		else // cb.tomove == BLACK
		{
			if ( currentnode.IsAttacked( currentnode.blackkingposition, WHITE ) > 0) // black to move and black is attacked. Mate!
			{
				//gameover = true;
				return ( -32000  +  currentnode.ply );
			}
			else
			{
				//gameover = true;
				return ( 0 +  currentnode.ply);
			}
		} // endif
	}
	else
	{
		//System.out.println("Returning best so far: " + arg.bestsofar.out());
		//arg.bestsofar = cm;
		return currentnode.BestSoFar.value;
	}
}

/**************************************************************
* Negamax, very ineficient, but simple
* Drops out after depth 3.
*/
int ChessGame::NegaMax2( ChessBoard currentnode, int currentdepth ) 
{
	bool useeval = false;

	//if ( currentdepth <= 0 )
	// useeval = true;
	//return currentnode.evaluate( this );
	//return QuietAlphaBeta( currentnode , currentdepth + 1, -35000, 35000 );
	//return QuietAlphaBeta ( currentnode , depth + 1, -40000, 40000 );
	//return currentnode.evaluate ( this );

	//if ( drawcheck( currentnode ) ) 
	// return ( 0 );

	int legalmoves = 0;
	int movestomate = 0;
	bool foundmate = false;

	ChessMove cm = ChessMove( "a2a4");
	cm.value = -30000;

	currentnode.GenerateMoves();
	while ( ! currentnode.chessmoves.empty() )
	{
		cm = currentnode.chessmoves.top();
		currentnode.chessmoves.pop();
		//ChessBoard temp = new ChessBoard ( arg );
		//temp[depth].copy(currentnode);

		ChessBoard quiet2 = ChessBoard(currentnode);
		// for each move that is valid...
		if ( /*ValidateMove( cm.out() ) &&*/ quiet2.MakeMove( cm ) )
		{
			// found at least one valid move
			legalmoves++;
			if ( useeval && ! cm.capture )
				return cm.value = currentnode.Evaluate(  );
			else
				// set the value of the current move very low so it gets replaced immediately
				//cm.value = -30000;
				// return the negative of evaluate because we are interested in the best score for this side.
				cm.value = -NegaMax2(  quiet2, currentdepth - 1);
			//System.out.println("Move " + cm.out() + " value is : " + cm.value);


			//if this move value > than current best.value, swap moves (update king of the hill)
			if ( legalmoves != 0 )
			{
				if ( legalmoves == 1) // special case for first move
				{
					currentnode.BestSoFar = cm;
					//System.out.println("Only so far = " + cm.out());
				}
				else // best so far exists, update if necessary
				{
					if ( cm.value >= currentnode.BestSoFar.value )
					{
						currentnode.BestSoFar = cm;
						//System.out.println("Best so far = " + cm.out());
					}
				}
			} // end if legal moves != 0
		} // end validate move
	} // end while chessmoves.empty()

	//All the moves have been evaluated

	//return appropiate value if no moves found.
	// 
	if ( legalmoves == 0 ) 
	{
		if ( currentnode.sidetomove == WHITE )
		{
			if ( currentnode.IsAttacked( currentnode.whitekingposition, BLACK ) > 0) // white to move and white is attacked. Mate!
			{
				//gameover = true;
				return  -32000; //"game over - white is checkmated" ;
			}
			else
			{
				//gameover = true;
				return 0; //"game over - white is in stalemate";
			}
		}
		else // cb.tomove == BLACK
		{
			if ( currentnode.IsAttacked( currentnode.blackkingposition, WHITE ) > 0) // black to move and black is attacked. Mate!
			{
				//gameover = true;
				return -32000;// "game over - black is checkmated";
			}
			else
			{
				//gameover = true;
				return 0;//"game over - black is in stalemate";
			}
		} // endif
	}
	else
	{
		//System.out.println("Returning best so far: " + arg.bestsofar.out());
		//arg.bestsofar = cm;
		return currentnode.BestSoFar.value;
	}
}

/*****************************************************************
* Quiet search searches the positon and extends only checks captures and threats
* Implementation (todo)...
*/
int ChessGame::Quiet( ChessBoard currentnode, int currentdepth , int alpha, int beta) 
{
	//if ( drawcheck( currentnode ) ) 
	// return ( 0 );
	ChessBoard quiet;
	int legalmoves = 0;
	int movestomate = 0;
	bool foundmate = false;

	ChessMove cm = ChessMove( "a2a4");
	currentnode.BestSoFar.value = -40000;

	currentnode.GenerateMoves();
	while ( ! currentnode.chessmoves.empty() && currentnode.BestSoFar.value < beta )
	{
		cm = currentnode.chessmoves.top();
		currentnode.chessmoves.pop();
		//ChessBoard temp = new ChessBoard ( arg );
		//temp[depth].copy(currentnode);
		quiet = ChessBoard(currentnode);
		// for each move that is valid...
		if ( /*ValidateMove( cm.out() ) &&*/ quiet.MakeMove( cm ) )
		{
			// found at least one valid move
			legalmoves++;
			if ( ! cm.capture ) 
				break; // if the move is not a capture, ignore it!

			// return the negative of evaluate because we are interested in the best score for this side.
			cm.value = -Quiet( quiet, currentdepth + 1, -beta, -alpha);
			//System.out.println("Move " + cm.out() + " value is : " + cm.value);

			//if this move value > than current best.value, swap moves (update king of the hill)
			if ( legalmoves != 0 )
			{
				if ( legalmoves == 1) // special case for first move
				{
					currentnode.BestSoFar = cm;
					//System.out.println("Only so far = " + cm.out());
				}
				else // best so far exists, update if necessary
				{
					if ( cm.value > currentnode.BestSoFar.value )
					{
						currentnode.BestSoFar = cm;
						//currentnode.bestsofar.value = cm.val;
						//System.out.println("Best so far = " + cm.out());
					}

				}
			} // end if legal moves != 0
		} // end validate move
	} // end while chessmoves.empty()

	//All the moves have been evaluated

	//return appropiate value if no moves found.
	// 
	if ( legalmoves == 0 ) 
	{
		if ( currentnode.sidetomove == WHITE )
		{
			if ( currentnode.IsAttacked( currentnode.whitekingposition, BLACK ) > 0) // white to move and white is attacked. Mate!
			{
				//gameover = true;
				return ( -32000 + currentnode.ply );
			}
			else
			{
				//gameover = true;
				return ( 0 +  currentnode.ply);
			}
		}
		else // cb.tomove == BLACK
		{
			if ( currentnode.IsAttacked( currentnode.blackkingposition, WHITE ) > 0) // black to move and black is attacked. Mate!
			{
				//gameover = true;
				return ( -32000  +  currentnode.ply );
			}
			else
			{
				//gameover = true;
				return ( 0 +  currentnode.ply);
			}
		} // endif
	}
	else
	{
		//System.out.println("Returning best so far: " + arg.bestsofar.out());
		//arg.bestsofar = cm;
		return currentnode.Evaluate(  );
	}
}

/**
* The Master Constructor
*/

/*********************************************************************
* Quiet with alpha beta cutoff
* WOW!
*/
int ChessGame::QuietAlphaBeta( ChessBoard currentnode, int currentdepth,   int alpha, int beta ) 
{

	ChessMove cm = ChessMove("a2a4");
	ChessMove extramove = ChessMove ("a2a4");
	ChessBoard quiet;
	//  if ( drawcheck( currentnode ) ) 
	//  return ( 0 );

	cm.value = currentnode.Evaluate (  );

	if ( cm.value >= beta)
	{
		//currentnode.bestsofar = cm;
		return beta;
	}       
	if ( cm.value > alpha )
	{
		//currentnode.bestsofar = cm;
		alpha = cm.value;
		//System.out.println("Best so far = " + cm.out());
	}

	int legalmoves = 0;
	int movestomate = 0;
	bool foundmate = false;


	currentnode.GenerateMoves();
	while ( ! currentnode.chessmoves.empty() )
	{
		cm = currentnode.chessmoves.top();
		currentnode.chessmoves.pop();
		if ( ! cm.capture ) 
			break;
		//ChessBoard temp = new ChessBoard ( arg );
		//temp[depth].copy(currentnode);
		quiet = ChessBoard(currentnode);
		// for each move that is valid...
		if ( /*ValidateMove( cm.out() ) &&*/ quiet.MakeMove( cm ) )
		{
			// found at least one valid move
			legalmoves++;
			// set the value of the current move very low so it gets replaced immediately
			cm.value = -30000;
			// return the negative of evaluate because we are interested in the best score for this side.
			cm.value = -QuietAlphaBeta( quiet, currentdepth + 1, -beta, -alpha);
			//System.out.println("Move " + cm.out() + " value is : " + cm.value);


			//if this move value > than current best.value, swap moves (update king of the hill)
			if ( legalmoves != 0 )
			{
				if ( legalmoves == 1) // special case for only move
				{
					currentnode.BestSoFar = cm;
					//System.out.println("Only so far = " + cm.out());
				}
				else // best so far exists, update if necessary
				{
					if ( cm.value >= beta)
					{
						//currentnode.bestsofar = cm;
						//while ( ! currentnode.chessmoves.empty() )
						// extramove = currentnode.chessmoves.pop();
						//break; // pump all the moves from stack?
						return beta;
					}       
					if ( cm.value > alpha )
					{
						currentnode.BestSoFar = cm;
						alpha = cm.value;
						//System.out.println("Best so far = " + cm.out());
					}
				}
			} // end if legal moves != 0
		} // end validate move
	} // end while chessmoves.empty()

	//All the moves have been evaluated

	//return appropiate value if no moves found.
	// 
	if ( legalmoves == 0 ) 
	{
		if ( currentnode.sidetomove == WHITE )
		{
			if ( currentnode.IsAttacked( currentnode.whitekingposition, BLACK ) > 0) // white to move and white is attacked. Mate!
			{
				//gameover = true;
				return ( -32000 + currentnode.ply );
			}
			else
			{
				//gameover = true;
				return ( 0 +  currentnode.ply);
			}
		}
		else // cb.tomove == BLACK
		{
			if ( currentnode.IsAttacked( currentnode.blackkingposition, WHITE ) > 0) // black to move and black is attacked. Mate!
			{
				//gameover = true;
				return ( -32000  +  currentnode.ply );
			}
			else
			{
				//gameover = true;
				return ( 0 +  currentnode.ply);
			}
		} // endif
	}
	else
	{
		//System.out.println("Returning best so far: " + arg.bestsofar.out());
		//arg.bestsofar = cm;
		return currentnode.BestSoFar.value;
	}
}
