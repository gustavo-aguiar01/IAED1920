/* 
 *
 * File: allfunctions.h
 * Author: Gustavo Almeida Aguiar (95587)
 * Description: A header file that contains preprocessor definitions and
 * function prototypes that were used in allfunctions.c
 * 
*/

/*================================= ALL FUNCTIONS =================================*/

#ifndef ALLFUNCTIONS_H_
#define ALLFUNCTIONS_H_

/*=================================================================================*/

#include "game.h"
#include "team.h"

/*=================================================================================*/

/* Hashtable initial size */
#define INITSIZE 769 
/* Max buffer length */
#define BUFSIZE 1024

/*=================================================================================*/

/* Team functions */
void addTeam(HashTeam * table, int NL);
void searchTeam(HashTeam table, int NL);

/* Game functions */
void addGame(HashGame * gTable, GameLink * gList, HashTeam tTable, int NL);
void searchGame(HashGame table, int NL);
void deleteGame(HashGame table, GameLink * list, int NL);
void listGames(GameLink list, int NL);
void changeScore(HashGame table, int NL);
void winningTeams(HashTeam table, int NL);

/* Aux Game functions */
int getMaxWins(HashTeam table, int * max, int * qty);
int myCompare(const void* a, const void* b);
void sortAndPrint(Team * unsorted, int qty, int NL);

#endif
