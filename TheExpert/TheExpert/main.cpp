/**
Francisco Tort
Apr 27, 2015

*/
#include "ChessGame.h"
#include "UCIInterface.h"
#include <iostream>
#include <string>


void main(void)
{

	
	//cout << "Entering main" << endl;
	string input, output;

	//cout << "Instantiating Engine" << endl;
	UCIInterface TheExpertUCI;
	//TheExpertUCI.Command("test");
	TheExpertUCI.Command("perft");
	//return;
	do
	{
		//cout << "Waiting for input" << endl;
		getline(cin, input);
		TheExpertUCI.Command(input);
		cout << output;
	} while (input != "quit");
	
}
