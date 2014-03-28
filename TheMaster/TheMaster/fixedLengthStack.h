/**********************************************
/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define MAXSTACK 250

/************************************************/
template <class T>
class Cstack
{
private: 
	T arr[MAXSTACK];
	short index;
public:
	Cstack() 
	{ 
		index = -1;
	};
	T pop(void)			
	{ 
		if ( ! empty() )
			return arr[index--]; 
		return (0); 
	} ;
	void push(T cm)		
	{
		if ( index > MAXSTACK )
			return;
		arr[++index] = cm; 
	} ;
	int size(void){
		return index + 1;}
	void DumpStack(void)
	{
		index = -1;
		return;
	}
	bool empty (void)				
	{ 
		if ( index < 0 )	
			return true;
		return false; 
	};
};