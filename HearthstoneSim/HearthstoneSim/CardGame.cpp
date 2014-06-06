//
// Francisco Tort
// February 19, 2014
//
//

#include "CardGame.h"
#include "Board.h"
#include "utilities.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

CardGame::CardGame(void)
{
	Init();
}
void CardGame::Init(void)
{
	FTDEBUG("Initializing CardGame", DEBUGALL);
	stm = PLAYER1;
	mana = 1;
	manaused = 0;
	manaleft = mana;
	player[0] = Player(PLAYER1, WARRIOR);
	player[1] = Player(PLAYER2, WARRIOR);
	FTDEBUG("CardGame initialized", DEBUGALL);
	ReadAllCards();

}
bool CardGame::GameOver ( void )
{
	// TODO: fix for ties/both die at the same time
	if (! player[PLAYER1].bIsAlive() )
		return true;
	if (! player[PLAYER2].bIsAlive() )
		return true;
	return false;
}
void CardGame::run(void)
{
	//player[turn].play(board, deck[turn].draw());
	//turn = (turn==PLAYER1?PLAYER2:PLAYER1); 
}
void CardGame::ReadAllCards(void)
{
	FTDEBUG("Reading cards", DEBUGALL);
	maxcards = 0;
	string line;
	ifstream myfile ("C:\\Users\\Paquito\\Google Drive\\programming\\temp\\Hearthstone Sortable List.csv");
	if (myfile.is_open())
	{
		getline (myfile,line);				//Throw away first column, should be column name	
		while ( getline (myfile,line) )
		{
			//FTDEBUG(line, DEBUGALL);
			allcards[maxcards++] = Card(line);
		}
	}
	FTDEBUG("Done reading Cards", DEBUGALL);
	FTDEBUG("Cards read ", DEBUGALL);
	FTDEBUGi(maxcards, DEBUGALL);

	myfile.close();
}
/****************************************
* Reads a position including health, cards and minions
*/
void CardGame::LoadPosition(string path)
{
	FTDEBUG("Reading position " + path, DEBUGALL);
	string line;
	vector<string> tokens;

	ifstream myfile (path);
	if (myfile.is_open()) 
	{
		getline (myfile,line);	 // throw away description line
		getline (myfile,line);
		Tokenize(line, tokens, ",");
		//GameState: Hero1, Hero2, Turn (0,1), Health p1, Health p2,
		//Minions P1, Minions p2
		player[0].SetClass(tokens[0].c_str());
		player[1].SetClass(tokens[1].c_str());
		stm = (Turn)FTATOI(tokens[2].c_str());
		player[0].SetHealth(FTATOI(tokens[3].c_str()));
		player[1].SetHealth(FTATOI(tokens[4].c_str()));
		player[0].SetMinions(FTATOI(tokens[5].c_str()));
		player[1].SetMinions(FTATOI(tokens[6].c_str()));
		////For Minions: Name, Attack, Health, stealth (0,1), frozen (0,1)
		getline (myfile,line);	 // throw away description line
		FTDEBUG("Reading P1 minions" , DEBUGALL);
		for ( int i = 0; i < player[0].GetMinions(); i++){
			getline (myfile,line);
			tokens.clear();Tokenize(line, tokens, ",");

			//minions[0].push_back(minion( tokens[0], 
			//	FTATOI(tokens[1].c_str()),
			//	FTATOI(tokens[2].c_str()),
			//	FTATOB(tokens[3].c_str()),
			//	FTATOB(tokens[4].c_str())));
		}
		FTDEBUG("Reading P2 minions", DEBUGALL);
		for ( int i = 0; i < player[1].GetMinions(); i++){
			getline (myfile,line);
			tokens.clear();Tokenize(line, tokens, ",");

			//minions[1].push_back(minion( tokens[0], 
			//	FTATOI(tokens[1].c_str()),
			//	FTATOI(tokens[2].c_str()),
			//	FTATOB(tokens[3].c_str()),
			//	FTATOB(tokens[4].c_str())));
		}


		FTDEBUG("Done Reading " + path, DEBUGALL);
	}
	else
		FTDEBUG("Failed to open file " + path, DEBUGALL);

	myfile.close();
}
/****************************************
* Finds a card by Name
*/
Card CardGame::FindCard(string name)
{
	for ( int i = 0; i < maxcards; i++)
	{
		if ( name == allcards[i].GetName() )
			return allcards[i];
	}
	FTDEBUG( "Card " + name  + " not found!", DEBUGALL);
	return (Card());
}
/****************************************
* Reads a deck
*/
void CardGame::LoadDeck(string path, int pl)
{
	ifstream myfile (path);
	string line;
	vector<string> tokens;
	FTDEBUG("Reading deck " + path, DEBUGALL);

	if (myfile.is_open())
	{
		getline (myfile,line);
		Tokenize(line, tokens, ",");
		player[pl].SetClass(tokens[1].c_str());
		while ( getline (myfile,line) )
		{
			//FTDEBUG(line, DEBUGALL);
			if (line.length() < 5)
				continue;
			Tokenize(line, tokens, ",");
			deck[pl].Add(FindCard(tokens[0]));
			if ( tokens.size() > 1)
			{
				deck[pl].Add(FindCard(tokens[0]));
			}
		}
		myfile.close();
	}
	FTDEBUG("Read deck " + path, DEBUGALL);
	FTDEBUG("Deck contains " , DEBUGALL);
	FTDEBUGi( deck[pl].size()  , DEBUGALL);
	deck[pl].Shuffle();
}
void CardGame::PrintBoard(void)
{
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
	player[opponent()].Print();
	cout << "X----------------------------------------X" << endl;
	player[opponent()].PrintHand();
	cout << "X----------------------------------------X" << endl;
	board.Print(opponent());
	cout << "X----------------------------------------X" << endl;
	board.Print(stm);
	cout << "X----------------------------------------X" << endl;
	player[stm].PrintHand();
	cout << "X----------------------------------------X" << endl;
	player[stm].Print();
	cout << "X----------------------------------------X" << endl;
	/********************************************************************
	* Print Mana left
	********************************************************************/
		cout << "XXX         " ;
	for(int i = 0; i < manaleft; i++)
		cout << " O";
	for(int i = 0; i <(mana -  manaleft); i++)
		cout << " X";
	for ( int i = 20; i > (mana * 2); i--)
		cout << " ";
	cout << "       XXX" << endl;
	         
	cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;

}

void CardGame::Play(string move)
{
	int indexOfActor;
	int indexOfVictim;
	int indexOfCard;
	

	/*************************************************************
	* End Turn
	*************************************************************/
	if ( move == "END" || move == "End" || move == "end" )
	{
		manaused = 0;
		stm = opponent();
		//Activate all current minions (they can still be frozen)
		board.UnFreeze(stm);

		if ( stm == PLAYER1 )
		{
			mana ++;
			if ( mana == 11) 
				mana = 10;
		}
		manaleft = mana;
		manaused = 0;
		player[stm].ReceiveCard(  deck[stm].draw());
		return;
	}
	vector<string> tokens;
	tokens.clear();Tokenize(move, tokens, " ");
	/******************************************************
	* One argument means that this card is being played from the hand
	* and does not need a victim or target
	*******************************************************/
	if ( tokens.size() == 1 ) //deploy a minion from our hand
	{
		indexOfCard = FTATOI(tokens[0].c_str()) -1 ;
		if ( !player[stm].bHasCards() ) {
			cout << "No cards left\n";
			return;
		}
		if ( indexOfCard >= player[stm].iCardCount()){
			cout << "No card on that spot!\n";
			return;
		}
		
		if ( manaleft < player[stm].iGetManaCost(indexOfCard) ){
			cout << "Card costs more than mana available!\n";
			return;
		}
		manaleft -= player[stm].iGetManaCost(indexOfCard);
		manaused += player[stm].iGetManaCost(indexOfCard);
		board.play(player[stm].RemoveCard(indexOfCard), stm);
		
		return;
	}

	if ( tokens.size() == 2)
	{cout << "Invalid move" << endl; return;}

	/******************************************************
	* two argument means that this card is being played
	* from the board and needs a victim or target
	*******************************************************/
	//the first index is the minions attacking (0 for hero)
	indexOfActor = FTATOI(tokens[0].c_str()) -1;
	//the second token is the "act upon" symbol : >
	indexOfVictim = FTATOI(tokens[2].c_str()) -1;
	int turnminions = board.GetMinionCount(stm) - 1;
	int opponentminions = board.GetMinionCount(opponent()) - 1;
	if ( indexOfActor > turnminions ||
		indexOfVictim > opponentminions)
	{	cout << "Invalid index" << endl; return;}
	//Interact!
	Interact( indexOfActor , indexOfVictim);
}
void CardGame::LoadHands(void)
{
	player[PLAYER1].ReceiveCard(  deck[PLAYER1].draw());
	player[PLAYER1].ReceiveCard(  deck[PLAYER1].draw());
	player[PLAYER1].ReceiveCard(  deck[PLAYER1].draw());	
	player[PLAYER1].ReceiveCard(  deck[PLAYER1].draw());

	player[PLAYER2].ReceiveCard(  deck[PLAYER2].draw());
	player[PLAYER2].ReceiveCard(  deck[PLAYER2].draw());
	player[PLAYER2].ReceiveCard(  deck[PLAYER2].draw());
	player[PLAYER2].ReceiveCard(  deck[PLAYER2].draw());
}
CardGame::~CardGame(void)
{
}
