/*
  TheMaster, a UCI chess playing engine 
  Copyright (C)2014 Francisco Tort

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
	ChessBoard cb; 

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
	int AlphaBeta( ChessBoard &, int depth, int alpha, int beta );
	int NegaMax( ChessBoard & currentnode, int currentdepth );
	int NegaMax2( ChessBoard currentnode, int currentdepth );
	int Quiet( ChessBoard currentnode, int currentdepth , int alpha, int beta);
	int QuietAlphaBeta( ChessBoard currentnode, int currentdepth,   int alpha, int beta );
	/****************************************
	* Testing funcs
	****************************************/
	int perft(ChessBoard & cb, int depth);
}; // end class "ChessGame"
