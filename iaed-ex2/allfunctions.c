/* 
 *
 * File: allfunctions.c
 * Author: Gustavo Almeida Aguiar (95587)
 * Description: A file that contains all functions used by the file main.c
 * 
*/

/*================================== MAIN FUNCTIONS ==================================*/

#include "allfunctions.h"

/*====================================================================================*/


/*================================== TEAM FUNCTIONS ==================================*/

/* Adds a team to the team hashtable */
void addTeam(HashTeam * table, int NL) {
    char buffer[BUFSIZE];
    Team team;
    scanf(" %[^:\n]", buffer);

    team = tHashSearch(*table, buffer);

    if (team) {
        printf("%d Equipa existente.\n", NL);
    } else {
        * table = tHashInsert(table, newTeam(buffer));
    }
}

/* Searches a team in the team hashtable */
void searchTeam(HashTeam table, int NL) {
    char buffer[BUFSIZE];
    Team team;
    scanf(" %[^:\n]", buffer);

    team = tHashSearch(table, buffer);

    if (!team) {
        printf("%d Equipa inexistente.\n", NL);
    } else {
        printf("%d ", NL);
        printTeam(team);
    }
}

/*================================== GAME FUNCTIONS ==================================*/

/* Adds a game to the game hashtable and doubly linked list */
void addGame(HashGame * gTable, GameLink * gList, HashTeam tTable, int NL) {
    int score1, score2;
    char name[BUFSIZE], team1[BUFSIZE], team2[BUFSIZE];

    Game game;
    Team t1, t2;

    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, team1, team2, &score1, &score2);
    game = gHashSearch(* gTable, name);
    t1 = tHashSearch(tTable, team1);
    t2 = tHashSearch(tTable, team2);

    /* If team1 or team2 is NULL, that team isn't in the system */
    /* If game != NULL, that game is already in the system */
    if (game) {
        printf("%d Jogo existente.\n", NL);
    }

    else if (!t1 || !t2) {
        printf("%d Equipa inexistente.\n", NL);
    }

    else {
        /* Give winning team their respective win */
        if (score1 > score2) {
            t1->wins++;
        }
        else if (score2 > score1) {
            t2->wins++;
        }
        /* Put new game in hashtable and dllist */
        game = newGame(name, t1, t2, score1, score2);
        * gTable = gHashInsert(gTable, game);
        * gList = insertGameList(* gList, game);
    }
}

/* Searches a game in the game hashtable */
void searchGame(HashGame table, int NL) {
    char buffer[BUFSIZE];
    Game game;
    scanf(" %[^:\n]", buffer);

    game = gHashSearch(table, buffer);

    if (game) {
        printf("%d ", NL);
        printGame(game);
    } else {
        printf("%u Jogo inexistente.\n", NL);
    }
}

/* Deletes a game from the game hashtable and from the
doubly linked list */
void deleteGame(HashGame table, GameLink * list, int NL) {
    char buffer[BUFSIZE];
    Game game;
    scanf(" %[^:\n]", buffer);

    game = gHashSearch(table, buffer);

    if (!game) {
        printf("%d Jogo inexistente.\n", NL);
    } else {
        /* Fix scores */
        if (score1(game) > score2(game)) {
            game->team1->wins--;
        }
        else if (score1(game) < score2(game)) {
            game->team2->wins--;
        }
        /* Delete game from hashtable and dllist */
        gHashDelete(table, buffer);
        * list = removeGameList(* list, buffer);
    }
}

/* Lists all games in the system by input order */
void listGames(GameLink list, int NL) {
    GameLink aux;
    if (list) {
        aux = list->prev;
        /* Do while loop to at least run one 
        time bc it's circular */
        do {
            printf("%d ", NL);
            printGame(aux->game);
            aux = aux->prev;     
        } while (aux != list->prev);
    }
}

/* Changes a match's score */
void changeScore(HashGame table, int NL) {
    char buffer[BUFSIZE];
    int oldS1, oldS2;
    int score1, score2;
    Game game;

    scanf(" %[^:\n]:%d:%d", buffer, &score1, &score2);

    game = gHashSearch(table, buffer);

    if (!game) {
        printf("%d Jogo inexistente.\n", NL);
    } else {
        /* Save previous scores to further compare and
        update game's new scores */
        oldS1 = score1(game);
        oldS2 = score2(game);
        score1(game) = score1;
        score2(game) = score2;

        /* Old game tie */
        if (oldS1 == oldS2) {
            if (score1 > score2) {
                game->team1->wins++;
            } 
            else if (score2 > score1) {
                game->team2->wins++;
            }
        }

        /* Old game team1 won */
        if (oldS1 > oldS2) {
            if (score1 == score2) {
                game->team1->wins--;
            } 
            else if (score2 > score1) {
                game->team1->wins--;
                game->team2->wins++;
            }
        }

        /* Old game team2 won */
        if (oldS2 > oldS1) {
            if (score2 == score1) {
                game->team2->wins--;
            } 
            else if (score1 > score2) {
                game->team2->wins--;
                game->team1->wins++;
            }
        }
    }
}

/* Prints winning teams */
void winningTeams(HashTeam table, int NL) {

    int i, j = 0;
    int max, qty;
    Team * unsorted;
    Team aux; 

    getMaxWins(table, &max, &qty);

    /* If max remained -1 no winners */
    if (max != -1) {
        unsorted = (Team *) malloc(qty * sizeof(struct team));

        printf("%d Melhores %d\n", NL, max);

        for (i = 0; i < max(table); i++) {
            if (table->teams[i]) {
                aux = table->teams[i];
                if (aux->wins == max) {
                    *(unsorted + j) = aux;
                    j++;
                }
            }
        }
        sortAndPrint(unsorted, j, NL);
        free(unsorted);
    }
}

/* Returns the most amount of wins and how teams have that amt of wins */
int getMaxWins(HashTeam table, int * max, int * qty) {
    int tempmax = -1;
    int tempqty = 0;
    int i;
    for (i = 0; i < max(table); i++) {
        if (table->teams[i]) {
            if (table->teams[i]->wins > tempmax) {
                tempqty = 0;
                tempmax = table->teams[i]->wins;
            }
            if (table->teams[i]->wins == tempmax) {
                tempqty++;
            }
        }
    }
    * max = tempmax;
    * qty = tempqty;
    return 0;
}

/* Aux function to qsort */
int myCompare(const void* a, const void* b) { 
    return strcmp((*((Team*)(a)))->name, (*((Team*)(b)))->name); 
} 

/* Sorts an array of team names and prints them sorted */
void sortAndPrint(Team * unsorted, int qty, int NL) {
    int i;
    qsort(unsorted, qty, sizeof(Team), myCompare); 
    for (i = 0; i < qty; ++i) {
        printf("%d * %s\n", NL, unsorted[i]->name);
    }
}
