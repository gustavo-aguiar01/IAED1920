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
void _addTeam_(HashTeam * table, int NL);
void _searchTeam_(HashTeam table, int NL);

/* Game functions */
void _addGame_(HashGame * gTable, GameLink * gList, HashTeam tTable, int NL);
void _searchGame_(HashGame table, int NL);
void _deleteGame_(HashGame table, GameLink * list, int NL);
void _listGames_(GameLink list, int NL);
void _changeScore_(HashGame table, int NL);
void _winningTeams_(HashTeam table, int NL);

/* Aux Game functions */
int getMaxWins(HashTeam table, int * max, int * qty);
int myCompare(const void* a, const void* b);
void sortAndPrint(Team * unsorted, int qty, int NL);

#endif
