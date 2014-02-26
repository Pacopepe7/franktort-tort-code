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
	char chinput[50];

	do
	{
		cin.getline(chinput,50, '\n');
		
		input = chinput;
		ofile << input << endl;

		output =  TheMasterDriver.ProcessCommand(input);
		ofile << "\t" << output;

		cout <<  output;

	}while ( input != "quit" );

	ofile.close();
	return;
}