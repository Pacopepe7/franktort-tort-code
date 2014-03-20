/**********************************************
/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



/************************************************/
template <class T>
class Cstack
{
private: 
	T arr[256];
	short index;
public:
	Cstack() 
	{ 
		index = 0;
	};
	T pop(void)			
	{ 
		if ( ! empty() )
			return arr[index--]; 
		return (0); 
	} ;
	void push(T cm)		
	{
		arr[++index] = cm; 
	} ;
	bool empty (void)				
	{ 
		if ( index < 0 )	
			return true;
		return false; 
	};
};