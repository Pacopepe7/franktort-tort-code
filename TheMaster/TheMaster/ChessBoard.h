/**********************************************
/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Definitions.h"
#include <string>
#pragma once



using namespace std;
/************************************************/
class ChessBoard 
{
private:
	

	int getIndex(Square s);
	int getIndex(Rank r, File f);

public:
	/**********************************************
	* constructors
	*/
	ChessBoard(void);

	/**********************************************
	* Functions
	*/
	void Set(Piece p, Color c, Square s);
	void Clear(Square s);
	
	File getFile( Square sq)				{ return (( sq ) & 7 ) ; } ;
	Rank getRank( Square sq)				{ return (( sq ) >> 4) ; } ;
	bool sameFile( Square sq1, Square sq2)	{ return ( getFile(sq1) == getFile(sq2))? 0:1; } ;
	bool sameRank( Square sq1, Square sq2)	{ return ( getRank(sq1) == getRank(sq2))? 0:1; } ;

	/***********************************************
	*
	*/


	bool isAttacked ( int sq, int side );

	int Evaluate( );

	//Helpers
	string getNotation(short r, short c);


};