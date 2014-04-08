/*
  TheMaster, a UCI chess playing engine 
  Copyright (C)2014 Francisco Tort

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ChessGame.h"
#include <iostream>
#include <boost/timer/timer.hpp>
#include <boost/chrono/include.hpp>
using namespace boost;

#pragma once

typedef boost::chrono::duration<double> sec;

class UCIInterface
{
	ChessGame cg;
	
public:
	UCIInterface(void);
	void ClearSearchData(void);
	void PrintSearchData( sec);
	void bist(void);
	void Command(string);
	~UCIInterface(void);
};

