/*
  TheMaster, a UCI chess playing engine 
  Copyright (C)2014 Francisco Tort

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "ChessPosition.h"
#include <iostream>
#include <vector>

//#include <boost/timer/timer.hpp>
//#include <boost/chrono/include.hpp>
//using namespace boost;



//typedef boost::chrono::duration<double> sec;

class UCIInterface
{
public:
	ChessPosition * chessPosition;
	

	
	UCIInterface(void);
	void bist(void);
	void Command(string);
	~UCIInterface(void);
};

