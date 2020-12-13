/* 
 *
 * File: games.h
 * Author: Gustavo Almeida Aguiar (95587)
 * Description: A header file that contains game function prototypes defined
 * in game.c
 * 
*/

/*================================= GAME STRUCT ================================*/

#ifndef GAME_H_
#define GAME_H_

/*===============================================================================*/

#include <stdio.h>

#include "auxfunctions.h"
#include "team.h"

/*===============================================================================*/

/* Game struct */
typedef struct game {
    char * name;
    Team team1;
    Team team2;
    int score1, score2;
} * Game;

/* Node from circular dllist struct */
typedef struct gameNode {
    Game game;
    struct gameNode * next, * prev;
} * GameLink;

/* Game hashtable struct */
typedef struct hashGame {
    int N, M;
    Game * games;
} * HashGame;

/*===============================================================================*/

/* Abstraction implementation */
#define team1(game) (game->team1->name)
#define team2(game) (game->team2->name)
#define score1(game) (game->score1)
#define score2(game) (game->score2)

/*===============================================================================*/

/* Initializers */
Game newGame(char *name, Team team1, Team team2, int score1, int score2);
GameLink newGameLink(Game game);
HashGame gHashInit(int max);

/* Selectors */
Game gHashSearch(HashGame table, char * name);

/* Modifiers */
GameLink insertGameList(GameLink head, Game game);
GameLink removeGameList(GameLink head, char * name);
HashGame gHashExpand(HashGame table);
HashGame gHashInsert(HashGame * table, Game game);
void gHashDelete(HashGame table, char * name);

/* Aux functions */
void printGame(Game game);
void freeGame(Game game);
void freeGameNode(GameLink link);
void gHashFree(HashGame table);
void gListFree(GameLink head);

#endif
