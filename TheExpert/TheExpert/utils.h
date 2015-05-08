#pragma once


#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <assert.h>

#include "chess.h"

using namespace std;

void Tokenize(const string& str,
	vector<string>& tokens,
	const string& delimiters);

int MakeInt(string s);

string MakeString(int i);



