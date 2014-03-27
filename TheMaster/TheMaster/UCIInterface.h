/*
  TheMaster, a UCI chess playing engine 
  Copyright (C)2014 Francisco Tort

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ChessGame.h"
#include <iostream>
#pragma once

class UCIInterface
{
	ChessGame cg;
public:
	UCIInterface(void);
	void Command(string);
	~UCIInterface(void);
};

