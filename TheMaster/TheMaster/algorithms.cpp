/**********************************************
/*
  TheMaster, a UCI chess playing engine 
  Copyright (C)2014 Francisco Tort

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ChessGame.h"

/**************************************************************
* Alpha beta
*/
//int ChessGame::AlphaBeta( ChessBoard & currentnode, int currentdepth, int alpha, int beta ) 
//{
//
//	//if ( currentdepth <= 0 ) 
//	//return Quiet ( arg , depth - 1 );
//	//return currentnode.Evaluate (  );
//	//return QuietAlphaBeta( currentnode, currentdepth, alpha, beta );
//
//	//if ( drawcheck( currentnode ) ) 
//	// return ( 0 );
//
//	int legalmoves = 0;
//	int movestomate = 0;
//	bool foundmate = false;
//
//	ChessMove cm = ChessMove(1,2);
//	ChessMove extramove = ChessMove( 1,2);
//	cm.value = -30000;
//	currentnode.GenerateMoves();
//
//	while ( ! currentnode.chessmoves.empty() )
//	{
//		/*cm = currentnode.chessmoves.top();
//		currentnode.chessmoves.pop();*/
//		
//
//		//ChessBoard temp = new ChessBoard ( arg );
//		//temp[depth].copy(currentnode);
//		ChessBoard temp = ChessBoard(currentnode);
//		// for each move that is valid...
//		if (  temp.MakeMove( cm ) )
//		{
//			// found at least one valid move
//			legalmoves++;
//			// set the value of the current move very low so it gets replaced immediately
//			cm.value = -30000;
//			// return the negative of evaluate because we are interested in the best score for this side.
//			//System.out.println("Searching ply : " + currentnode.ply);
//			if ( cm.capture && currentdepth < 1 )
//				cm.value = -AlphaBeta( temp, currentdepth , -beta, -alpha);
//			else
//				cm.value = -AlphaBeta( temp, currentdepth - 1, -beta, -alpha);
//
//			//System.out.println("Move " + cm.out() + " value is : " + cm.value);
//
//
//			//if this move value > than current best.value, swap moves (update king of the hill)
//			if ( legalmoves != 0 )
//			{
//				if ( legalmoves == 1) // special case for only move
//				{
//					currentnode.BestSoFar = cm;
//					//System.out.println("Only so far = " + cm.out());
//				}
//				else // best so far exists, update if necessary
//				{
//					if ( cm.value >= beta)
//					{
//						//return beta;
//						//currentnode.bestsofar = cm;
//						while ( ! currentnode.chessmoves.empty() )
//							extramove = currentnode.chessmoves.top();
//						//break; // pump all the moves from stack?
//						return beta;
//					}       
//					if ( cm.value > alpha )
//					{
//						currentnode.BestSoFar = cm;
//						alpha = cm.value;
//						//System.out.println("Best so far = " + cm.out());
//					}
//				}
//			} // end if legal moves != 0
//		} // end validate move
//	} // end while chessmoves.empty()
//
//	//All the moves have been evaluated
//
//	//return appropiate value if no moves found.
//	// 
//	if ( legalmoves == 0 ) 
//	{
//		if ( currentnode.sidetomove == WHITE )
//		{
//			if ( currentnode.IsAttacked( currentnode.whitekingposition, BLACK ) > 0) // white to move and white is attacked. Mate!
//			{
//				//gameover = true;
//				return ( -32000 + currentnode.ply );
//			}
//			else
//			{
//				//gameover = true;
//				return ( 0 +  currentnode.ply);
//			}
//		}
//		else // cb.tomove == BLACK
//		{
//			if ( currentnode.IsAttacked( currentnode.blackkingposition, WHITE ) > 0) // black to move and black is attacked. Mate!
//			{
//				//gameover = true;
//				return ( -32000  +  currentnode.ply );
//			}
//			else
//			{
//				//gameover = true;
//				return ( 0 +  currentnode.ply);
//			}
//		} // endif
//	}
//	else
//	{
//		//System.out.println("Returning best so far: " + arg.bestsofar.out());
//		//arg.bestsofar = cm;
//		return currentnode.BestSoFar.value;
//	}
//}

/**************************************************************
* Negamax
* 
*/
//int ChessGame::NegaMax( ChessBoard & currentBoard, int currentsearchdepth ) 
//{
//	if ( currentsearchdepth < 0 ) 
//		return currentBoard.Evaluate(  );
//
//	int legalmoves = 0;
//	int movestomate = 0;
//	ChessMove movebeingevaluated;
//	ChessBoard temp = currentBoard;
//	ChessBoard moveGenBoard = currentBoard;
//
//	moveGenBoard.GenerateMoves();
//	currentBoard.BestSoFar.value = -30000;
//
//	while ( ! moveGenBoard.chessmoves.empty() )
//	{
//		movebeingevaluated = moveGenBoard.chessmoves.top();
//		moveGenBoard.chessmoves.pop();
//
//		temp =  ChessBoard(currentBoard);
//		if ( temp.MakeMove( movebeingevaluated ) )
//		{
//			legalmoves++;
//			//if ( movebeingevaluated.capture  )
//			//	movebeingevaluated.value = -NegaMax( temp, currentsearchdepth);
//			//else
//				movebeingevaluated.value = -NegaMax( temp, currentsearchdepth - 1);
//			if ( movebeingevaluated.value >= currentBoard.BestSoFar.value )
//			{
//				currentBoard.BestSoFar = movebeingevaluated;
//				currentBoard.BestSoFar.value = movebeingevaluated.value;
//			}
//		}
//	}
//	return currentBoard.BestSoFar.value;
//} 
/**************************************************************
* Negamax
* 
*/
int ChessGame::NegaMax( ChessBoard & currentBoard, int currentsearchdepth ) 
{
	if ( currentsearchdepth < 0 ) 
		return currentBoard.Evaluate(  );

	int legalmoves = 0;
	int movestomate = 0;
	int value;
	unsigned int movebeingevaluated;
	ChessBoard temp = currentBoard;
	ChessBoard moveGenBoard = currentBoard;

	moveGenBoard.GenerateIntMoves();
	currentBoard.BestSoFar.value = -30000;

	while ( ! moveGenBoard.CMEMPTY() )
	{
		movebeingevaluated = moveGenBoard.CMPOP();
		
		temp =  ChessBoard(currentBoard);
		if ( temp.MakeIntMove( movebeingevaluated ) )
		{
			legalmoves++;
			//if ( movebeingevaluated.capture  )
			//	movebeingevaluated.value = -NegaMax( temp, currentsearchdepth);
			//else
				value = -NegaMax( temp, currentsearchdepth - 1);
			if ( value >= currentBoard.BestSoFar.value )
			{
				currentBoard.BestIntSoFar = movebeingevaluated;
				currentBoard.bestValueSoFar= value;
			}
		}
	}
	return currentBoard.bestValueSoFar;
} 


/**************************************************************
* Negamax, very ineficient, but simple
* Drops out after depth 3.
*
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
if ( quiet2.MakeMove( cm ) )
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
//int ChessGame::Quiet( ChessBoard currentnode, int currentdepth , int alpha, int beta) 
//{
//	//if ( drawcheck( currentnode ) ) 
//	// return ( 0 );
//	ChessBoard quiet;
//	int legalmoves = 0;
//	int movestomate = 0;
//	bool foundmate = false;
//
//	ChessMove cm = ChessMove(1,2);
//	currentnode.BestSoFar.value = -40000;
//
//	currentnode.GenerateMoves();
//	while ( ! currentnode.chessmoves.empty() && currentnode.BestSoFar.value < beta )
//	{
//		/*cm = currentnode.chessmoves.top();
//		currentnode.chessmoves.pop();*/
//		//ChessBoard temp = new ChessBoard ( arg );
//		//temp[depth].copy(currentnode);
//		quiet = ChessBoard(currentnode);
//		// for each move that is valid...
//		if ( /*ValidateMove( cm.out() ) &&*/ quiet.MakeMove( cm ) )
//		{
//			// found at least one valid move
//			legalmoves++;
//			if ( ! cm.capture ) 
//				break; // if the move is not a capture, ignore it!
//
//			// return the negative of evaluate because we are interested in the best score for this side.
//			cm.value = -Quiet( quiet, currentdepth + 1, -beta, -alpha);
//			//System.out.println("Move " + cm.out() + " value is : " + cm.value);
//
//			//if this move value > than current best.value, swap moves (update king of the hill)
//			if ( legalmoves != 0 )
//			{
//				if ( legalmoves == 1) // special case for first move
//				{
//					currentnode.BestSoFar = cm;
//					//System.out.println("Only so far = " + cm.out());
//				}
//				else // best so far exists, update if necessary
//				{
//					if ( cm.value > currentnode.BestSoFar.value )
//					{
//						currentnode.BestSoFar = cm;
//						//currentnode.bestsofar.value = cm.val;
//						//System.out.println("Best so far = " + cm.out());
//					}
//
//				}
//			} // end if legal moves != 0
//		} // end validate move
//	} // end while chessmoves.empty()
//
//	//All the moves have been evaluated
//
//	//return appropiate value if no moves found.
//	// 
//	if ( legalmoves == 0 ) 
//	{
//		if ( currentnode.sidetomove == WHITE )
//		{
//			if ( currentnode.IsAttacked( currentnode.whitekingposition, BLACK ) > 0) // white to move and white is attacked. Mate!
//			{
//				//gameover = true;
//				return ( -32000 + currentnode.ply );
//			}
//			else
//			{
//				//gameover = true;
//				return ( 0 +  currentnode.ply);
//			}
//		}
//		else // cb.tomove == BLACK
//		{
//			if ( currentnode.IsAttacked( currentnode.blackkingposition, WHITE ) > 0) // black to move and black is attacked. Mate!
//			{
//				//gameover = true;
//				return ( -32000  +  currentnode.ply );
//			}
//			else
//			{
//				//gameover = true;
//				return ( 0 +  currentnode.ply);
//			}
//		} // endif
//	}
//	else
//	{
//		//System.out.println("Returning best so far: " + arg.bestsofar.out());
//		//arg.bestsofar = cm;
//		return currentnode.Evaluate(  );
//	}
//}

/**
* The Master Constructor
*/

/*********************************************************************
* Quiet with alpha beta cutoff
* WOW!
*/
//int ChessGame::QuietAlphaBeta( ChessBoard currentnode, int currentdepth,   int alpha, int beta ) 
//{
//
//	ChessMove cm = ChessMove(1,2);
//	ChessMove extramove = ChessMove (1,2);
//	ChessBoard quiet;
//	//  if ( drawcheck( currentnode ) ) 
//	//  return ( 0 );
//
//	cm.value = currentnode.Evaluate (  );
//
//	if ( cm.value >= beta)
//	{
//		//currentnode.bestsofar = cm;
//		return beta;
//	}       
//	if ( cm.value > alpha )
//	{
//		//currentnode.bestsofar = cm;
//		alpha = cm.value;
//		//System.out.println("Best so far = " + cm.out());
//	}
//
//	int legalmoves = 0;
//	int movestomate = 0;
//	bool foundmate = false;
//
//
//	currentnode.GenerateMoves();
//	while ( ! currentnode.chessmoves.empty() )
//	{
//		cm = currentnode.chessmoves.top();
//		currentnode.chessmoves.pop();
//		if ( ! cm.capture ) 
//			break;
//		//ChessBoard temp = new ChessBoard ( arg );
//		//temp[depth].copy(currentnode);
//		quiet = ChessBoard(currentnode);
//		// for each move that is valid...
//		if ( /*ValidateMove( cm.out() ) &&*/ quiet.MakeMove( cm ) )
//		{
//			// found at least one valid move
//			legalmoves++;
//			// set the value of the current move very low so it gets replaced immediately
//			cm.value = -30000;
//			// return the negative of evaluate because we are interested in the best score for this side.
//			cm.value = -QuietAlphaBeta( quiet, currentdepth + 1, -beta, -alpha);
//			//System.out.println("Move " + cm.out() + " value is : " + cm.value);
//
//
//			//if this move value > than current best.value, swap moves (update king of the hill)
//			if ( legalmoves != 0 )
//			{
//				if ( legalmoves == 1) // special case for only move
//				{
//					currentnode.BestSoFar = cm;
//					//System.out.println("Only so far = " + cm.out());
//				}
//				else // best so far exists, update if necessary
//				{
//					if ( cm.value >= beta)
//					{
//						//currentnode.bestsofar = cm;
//						//while ( ! currentnode.chessmoves.empty() )
//						// extramove = currentnode.chessmoves.pop();
//						//break; // pump all the moves from stack?
//						return beta;
//					}       
//					if ( cm.value > alpha )
//					{
//						currentnode.BestSoFar = cm;
//						alpha = cm.value;
//						//System.out.println("Best so far = " + cm.out());
//					}
//				}
//			} // end if legal moves != 0
//		} // end validate move
//	} // end while chessmoves.empty()
//
//	//All the moves have been evaluated
//
//	//return appropiate value if no moves found.
//	// 
//	if ( legalmoves == 0 ) 
//	{
//		if ( currentnode.sidetomove == WHITE )
//		{
//			if ( currentnode.IsAttacked( currentnode.whitekingposition, BLACK ) > 0) // white to move and white is attacked. Mate!
//			{
//				//gameover = true;
//				return ( -32000 + currentnode.ply );
//			}
//			else
//			{
//				//gameover = true;
//				return ( 0 +  currentnode.ply);
//			}
//		}
//		else // cb.tomove == BLACK
//		{
//			if ( currentnode.IsAttacked( currentnode.blackkingposition, WHITE ) > 0) // black to move and black is attacked. Mate!
//			{
//				//gameover = true;
//				return ( -32000  +  currentnode.ply );
//			}
//			else
//			{
//				//gameover = true;
//				return ( 0 +  currentnode.ply);
//			}
//		} // endif
//	}
//	else
//	{
//		//System.out.println("Returning best so far: " + arg.bestsofar.out());
//		//arg.bestsofar = cm;
//		return currentnode.BestSoFar.value;
//	}
//}
