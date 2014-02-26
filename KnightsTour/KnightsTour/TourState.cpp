#include "TourState.h"

bool myfunction (move_t i, move_t j) { return (i.value < j.value); }

int knight[8]   = 
{
	NORTH + NORTHWEST, NORTH + NORTHEAST, SOUTH + SOUTHWEST, SOUTH + SOUTHEAST, 
	WEST + NORTHWEST, EAST + NORTHEAST, WEST + SOUTHWEST, EAST + SOUTHEAST
};

char * notation[MAXNOTATION] = 
{
	" X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X",
	" X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X",
	" X", " X",	"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", " X", " X",
	" X", " X",	"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", " X", " X",
	" X", " X",	"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", " X", " X",
	" X", " X",	"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", " X", " X",
	" X", " X",	"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", " X", " X",
	" X", " X",	"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", " X", " X",
	" X", " X",	"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", " X", " X",
	" X", " X",	"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", " X", " X",
	" X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X",
	" X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X", " X"
};

contents startingposition[MAXNOTATION] = 
{ 
	USED, 	USED,	 USED, 	USED, 	USED, 	USED,	 USED,	 USED,	 USED,	 USED,	 USED, 	USED,
	USED, 	USED,	 USED, 	USED, 	USED, 	USED, 	USED,	 USED,	 USED,	 USED,	 USED, 	USED,
	USED, 	USED,EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,	 USED, 	USED,
	USED,	USED, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,	EMPTY,EMPTY,EMPTY,	 USED, 	USED,
	USED, 	USED,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, 	USED,	 USED,
	USED,	 USED,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, 	USED,	 USED,
	USED,	 USED,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY, 	USED,	 USED,
	USED,	 USED,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,	 USED,	 USED,
	USED, 	USED,EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,EMPTY,EMPTY,EMPTY,	 USED, 	USED,
	USED,	USED, EMPTY, EMPTY, EMPTY, EMPTY,EMPTY,	EMPTY,EMPTY,EMPTY,	 USED, 	USED,
	USED,	 USED, 	USED,	 USED,	 USED,	 USED,	 USED,	 USED,	 USED,	 USED,	 USED,	 USED,
	USED,	 USED, 	USED,	 USED,	 USED,	 USED,	 USED,	 USED,	 USED,	 USED,	 USED,	 USED
};

//////////////////////////////////////////////////////////
// Public Functions

TourState::TourState(void)
{
}
void TourState::run(void)
{
	//printPath();
	if ( IsTourComplete() )
	{

		printPath(); 
		return;
	}
	moves.erase(moves.begin(), moves.end());

	for ( int dir = 0; dir < 8; dir++)
	{
		move_t temp;
		temp.index =  dir;
		temp.value = ValidSquaresFrom(iCurrentSquare + knight[dir]);
		if ( temp.value > 0 )
			moves.push_back(temp);
	}
	sort (moves.begin(), moves.end(), myfunction); 

	for ( int i = 0; i < (int)moves.size(); i++)
	{
		TourState temp(*this);
		if ( temp.IsValid(moves[i].index) )
			temp.run();

	}
}
TourState::~TourState(void)
{
}
/////////////////////////////////////////////////////////
// Private Functions

int TourState::ValidSquaresFrom(int from)
{

	if ( currentposition[from] == USED )
		return -1;
	int count= 1;
	for ( int dir = 0; dir < 8; dir++)
	{
		if ( currentposition[from + knight[dir]] == EMPTY )
			count ++;
	}
	return count;
}
void TourState::printPath(void)
{
	//path[step++] = iCurrentSquare;
	static int pathcount = 1;
	ofstream file("KnightsTour.txt", ios::app );

	cout << "Path # " << pathcount << endl;
	for ( int c = 0; c <= step  ; c++)
		cout << GetSquareName(path[c]) << ", ";
	cout << endl << endl;

		file << "Path # " << pathcount << endl;
	for ( int c = 0; c < step ; c++)
		file << GetSquareName(path[c]) << ", ";
	file << endl << endl;
	file.close();
	cout << "Thinking...." << endl;
	pathcount ++;
}
bool TourState::IsValid(int dir)
{
	if ( currentposition[iCurrentSquare + knight[dir]] == USED )
		return false;
	//the square is not used
	iCurrentSquare += knight[dir];
	currentposition[iCurrentSquare] = USED;
	path[step++] = iCurrentSquare;
	if ( IsTourComplete() )
	{
		printPath(); 
		return false;
	}
	return true;
}
bool TourState::IsTourComplete(void)
{
	if ( step == 63 )
		return true;
	return false;
}
int TourState::GetSquareNumber(string sq)
{
	for( int x = 0; x < MAXNOTATION; x++)
	{
		if ( sq==notation[x])
			return x;
	}
	return -1;
}
string TourState::GetSquareName(int index)
{
	return notation[index];
}
void TourState::Init(void)
{
	for (int c = 0; c < 64; c++)
	{
		bUsedSquares[c] = false;
		path[c] = 0;
	}
	step = 0;
	
	for (int c = 0; c < MAXNOTATION; c++)
		currentposition[c] = startingposition[c];
	iCurrentSquare = iStartingSquare = GetSquareNumber("a1");
	currentposition[iCurrentSquare] = USED;
	path[step++] = iCurrentSquare;

}

