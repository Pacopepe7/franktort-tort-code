/*
TheMaster, a UCI chess playing engine 
Copyright (C)2014 Francisco Tort

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ChessGame.h"
#include <iostream>

/**************************************************************
* PrintBoard ()
*/

void ChessGame::PrintBoard ( void ) 
{
	bool newrow = false;
	cout << "----------------------" << endl;
	if ( ctm ) cout << "   BLACK to move   " << endl;
	else cout << "   WHITE to move   " << endl;


	for ( int i = 0; i < 128; i++)
	{
		if ( ! isSquare(i) )
		{
			newrow = true;
			continue;
		}
		if ( newrow )
		{
			newrow = false; 
			cout << endl;
		}
		if ( Ox88Board[i] == NULL)
		{
			cout << " ";
			continue;
		}
		switch ( Ox88Board[i]->piece)
		{
		case PAWN:
			if (  Ox88Board[i]->color == WHITE ) //White is 0
				cout << "P";
			if (  Ox88Board[i]->color == BLACK )
				cout << "p";
			break;
		case KNIGHT:
			if (  ! Ox88Board[i]->color ) //WHite is 0
				cout << "N";
			else
				cout << "n";
			break;
		case BISHOP:
			if (  ! Ox88Board[i]->color ) //WHite is 0
				cout << "B";
			else
				cout << "b";
			break;
		case ROOK:
			if (  ! Ox88Board[i]->color ) //WHite is 0
				cout << "R";
			else
				cout << "r";
			break;
		case QUEEN:
			if (  ! Ox88Board[i]->color ) //WHite is 0
				cout << "Q";
			else
				cout << "q";
			break;		
		case KING:
			if (  ! Ox88Board[i]->color ) //WHite is 0
				cout << "K";
			else
				cout << "k";
			break;
		}
	}
	cout << endl;
	cout << "White king at : " << not(state[ply].king[WHITE]) << endl;
	cout << "Black king at : " << not(state[ply].king[BLACK]) << endl;
	cout << "Material for White: " << materialCount[WHITE] << endl;
	cout << "Material for Black: " << materialCount[BLACK] << endl;
	cout << "PSQT for White: " << psqtCount[WHITE] << endl;
	cout << "PSQT for Black: " << psqtCount[BLACK] << endl;
	cout << "Eval = " << Evaluate() << endl;
	//print, to move pieces...
	/*for ( int c = 0; c < maxpieces[ state.ctm]; c++)
		cout << "c: " << c << ", P: " << (int)pieces[c][state.ctm].piece << " I: " <<  (int)pieces[c][state.ctm].square << endl;
	for ( int c = 0; c < maxpieces[ ColorNotOnMove()]; c++)
		cout << "c: " << c << ", P: " << (int)pieces[c][ColorNotOnMove()].piece << " I: " <<  (int)pieces[c][ColorNotOnMove()].square << endl;
	Square from = getFromSquare(state.m_LastMove);
	Square to = getToSquare(state.m_LastMove);
	Square data =  getDataSquare(state.m_LastMove);
	MoveType mt = getMoveType(state.m_LastMove);
	cout << (int) state.m_LastMove << "f: " << (int)from << " t: " << (int)to << " data: " << (int)data << " MT: " << (int) mt << endl;*/

}
void  ChessGame::PrintDebugMove(ChessMove cm)
{
	Square from = getFromSquare(cm);
	Square to = getToSquare(cm);
	Square data =  getDataSquare(cm);
	MoveType mt = getMoveType(cm);
	cout << "DEBUG:" << (int) cm << "f: " << (int)from << " t: " << (int)to << " data: " << (int)data << " MT: " << (int) mt << endl;
}

void ChessGame::ClearSearchData(void)
{

	searchdata.maxdepth = 0;
	searchdata.nodes = 0;
	searchdata.legalnodes = 0;
	searchdata.evaluates = 0;
	searchdata.quietnodes = 0;
	searchdata.regularnodes = 0;
}

void ChessGame::PrintSearchData( sec d)
{
	cout << "info Depth " << depth;
	cout << " seldepth " << searchdata.maxdepth;

	cout << " score cp " << chessresult[ply ].value;
	cout << " nodes " <<   searchdata.legalnodes;
	
  std::cout.precision(3);
	if ( d.count())
		cout << " nps " <<  (int)(searchdata.legalnodes / d.count()) ;
	else 
		cout << " nps " <<  (searchdata.legalnodes ) ;
	std::cout.unsetf ( std::ios::floatfield );                // floatfield not set
	cout << " time " << d.count();
	cout << " pv " <<  MakeAlgebraicMove(chessresult[ply ].best) <<endl;
	///////////////////////////////////////////////////////////////////////////
	cout << "info QuietNodes " << searchdata.quietnodes << " RegularNodes " 
		<< searchdata.regularnodes << " Evaluates " << searchdata.evaluates << endl;
	std::cout.precision(3);
	cout << "info Quiet/Normal " << (float)(((float)searchdata.quietnodes/(float)searchdata.regularnodes)* 100) << "%" << endl;
	std::cout.unsetf ( std::ios::floatfield );
	ClearSearchData();
}