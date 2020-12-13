/* 
 *
 * File: team.h
 * Author: Gustavo Almeida Aguiar (95587)
 * Description: A header file that contains function prototypes defined
 * in team.c
 * 
*/

/*================================= TEAM STRUCT ================================*/

#ifndef TEAMS_H_
#define TEAMS_H_

/*===============================================================================*/

#include <stdio.h>
#include "auxfunctions.h"

/*===============================================================================*/

/* Team struct */
typedef struct team {
    int wins;
    char * name;
} * Team;

/* Team hashtable struct */
typedef struct teamHash {
    int N, M;
    Team * teams;
} * HashTeam;

/*===============================================================================*/

/* Abstaction implementation */
#define name(a) (a->name)
#define wins(team) (team->wins)
#define max(x) (x->M)
#define size(x) (x->N)

/*===============================================================================*/

/* Initializers */
Team newTeam(char * name);
HashTeam tHashInit(int max);

/* Modifiers */
HashTeam tHashInsert(HashTeam * table, Team team);
HashTeam tHashExpand(HashTeam table);
Team tHashSearch(HashTeam table, char * name);

/* Auxiliary functions */
void printTeam(Team team);
void freeTeam(Team team);
void tHashFree(HashTeam table);

#endif
