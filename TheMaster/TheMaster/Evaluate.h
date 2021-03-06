/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Definitions.h"
#include "utils.h"

#undef INFINITY
#define INFINITY				20000
#define MATE					15000
#define ONLYMOVE				25000

#define PAWN_WEIGHT				100
#define KNIGHT_WEIGHT			320
#define BISHOP_WEIGHT			330
#define ROOK_WEIGHT				550
#define QUEEN_WEIGHT			1100;