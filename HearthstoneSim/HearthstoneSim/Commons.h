//
// Francisco Tort
// February 22, 2014
//
// Commons.h

#ifndef HS_CONSTS


#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef enum { PLAYER1, PLAYER2, MAXPLAYERS } Turn;
typedef enum { NOCLASS, DRUID, MAGE, PALADIN, PRIEST, ROGUE, SHAMAN, WARLOCK, WARRIOR, MAXCLASSES } HeroClasses;
typedef enum { NORARITY, BASIC, COMMON, RARE, EPIC, LEGENDARY, MAXRARITY } Rarity;
typedef enum { NOTYPE, MINION, SPELL, WEAPON, MAXTYPES } Type;
typedef enum { NORACE, BEAST, DEMON, DRAGON, MURLOC, PIRATE } Race;
typedef enum { NOBUGALL, DEBUGBASIC, DEBUGLEVEL2, DEBUGLEVEL3, DEBUGALL } debuglevel;
void FTDEBUG(string , debuglevel level );

#define MAXCARDSONHAND	10 
#define MAXMINIONSONBOARD	8
#define MAXCARDSONDECK		30


#endif 