#pragma once

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

typedef enum { OUT, USED, EMPTY } contents;
 static const int  NORTH=	-12;
 static const int  SOUTH=	12;
 static const int  EAST=	1;
 static const int  WEST=	-1;
 static const int  NORTHEAST =	( NORTH + EAST );
 static const int  NORTHWEST =	( NORTH + WEST );
 static const int  SOUTHEAST =	( SOUTH + EAST );
 static const int  SOUTHWEST =	( SOUTH + WEST );

 static const int MAXNOTATION = 144;
 //static const int 

#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

 struct move_t
 {
	 int index;
	 int value;
 };

using namespace std;

class TourState
{
private:
	bool bUsedSquares[64];
	contents currentposition[MAXNOTATION];
	int path[65];
	int step;
	int iCurrentSquare;
	int iStartingSquare;
	vector <move_t> moves;

	bool IsTourComplete(void);
	int GetSquareNumber(string);
	string GetSquareName(int);
	contents GetSquareContents(string);
	contents GetSquareContents(int);
	bool IsValid(int);
	void printPath(void);
	int ValidSquaresFrom(int);
public:
	void Init(void);
	void run(void);
	TourState(void);
	~TourState(void);
};

