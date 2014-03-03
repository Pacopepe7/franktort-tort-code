/***************************************************************
* Francisco Tort
* Jan 2, 2009
* Revised May 2013
***************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "ChessGame.h"



using namespace std;

void main ( void )
{
	ChessGame TheMasterDriver;
	
	//Start a log file for commands
	fstream ofile;
	ofile.open("logfile.txt",ios::app);

	string input, output;

	do
	{
		getline(cin, input);
		
		input = input;
		ofile << input << endl;

		output =  TheMasterDriver.ProcessCommand(input);
		ofile << output;

		cout <<  output;

	}while ( input != "quit" );

	ofile.close();
	return;
}