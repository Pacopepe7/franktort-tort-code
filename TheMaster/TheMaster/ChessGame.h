/**********************************************
* ChessGame.h
* Class header for a chess playing engine.
* Francisco Tort
* Dec 30, 2009
*/

#include "Definitions.h"
#include "ChessBoard.h"
#include "utils.h"
class ChessGame 
{

public:
	bool checkmate;
	bool checkmated;
	bool gameover;
	int depth ;
	int evaldepth;
	enum mode { UCI, ICC, CONSOLE } MODE;
	ChessBoard cb, temp[30];

	//Functions
	ChessGame ( ); 
	void Init(void);
	string ProcessCommand( string command );
	string ProcessUCICommand( string command );
	string ProcessICCCommand( string command );
	bool ValidateMove ( string command );
	ChessMove ReturnValidatedMove( string command );



	int getIndex( string s);
	string getResponce( void );
	int AlphaBeta( ChessBoard, int depth, int alpha, int beta );
	int NegaMax( ChessBoard currentnode, int currentdepth );
	int NegaMax2( ChessBoard currentnode, int currentdepth );
	int Quiet( ChessBoard currentnode, int currentdepth , int alpha, int beta);
	int QuietAlphaBeta( ChessBoard currentnode, int currentdepth,   int alpha, int beta );

}; // end class "ChessGame"
