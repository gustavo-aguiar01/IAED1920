/* 
 *
 * File: team.c
 * Author: Gustavo Almeida Aguiar (95587)
 * Description: A file that contains all team related structs, which
 * in this case represents a linear probing collision resolving hashtable
 * to store all teams
 * 
*/

/*================================= TEAM STRUCT ================================*/

#include "team.h"

/*===============================================================================*/

/* Creates new team */
Team newTeam(char * name) {
    Team new = (Team) malloc(sizeof(struct team));
    name(new) = strDup(name);
    wins(new) = 0;
    return new;
}

/* Initializes team hashtable with max size */
HashTeam tHashInit(int max) {
    int i;

    HashTeam table = (HashTeam) malloc(sizeof(struct teamHash));

    size(table) = 0;
    max(table) = max;

    /* Set default table elements to NULL */
    table->teams = (Team *) malloc(max(table) * sizeof(Team));
    for (i = 0; i < max(table); i++) {
        table->teams[i] = NULL;
    }
    return table;
}

/* Puts a team in the hashtable */
HashTeam tHashInsert(HashTeam * table, Team team){    
    int i = hash(name(team), max( (* table) ));
    HashTeam newtable;

    /* If position is taken find next empty position */
    while ((* table)->teams[i]) {
        i = (i + 1) % max((* table));
    }

    (* table)->teams[i] = team;
    size((* table))++;

    /* Hashtable expansion condition */
    if (size((* table)) >= max((* table)) / 2) {
        newtable = tHashExpand(* table);
        return newtable;
    }
    return * table;
}

/* Expands hastable to double its size */
HashTeam tHashExpand(HashTeam table) {
    int i;
    HashTeam newtable = tHashInit(max(table) * 2);

    /* Reinsert all teams */
    for (i = 0; i < max(table); i++) {
        if (table->teams[i]) {
            tHashInsert(&newtable, table->teams[i]);
        }
    }

    /* Free old table */
    free(table->teams);
    free(table);
    return newtable;
}

/* Searches a team in the hashtable and returns it */
Team tHashSearch(HashTeam table, char * name) {
    int i = hash(name, max(table));
    while (table->teams[i]) {
        if (strcmp(name, name(table->teams[i])) == 0) {
            return table->teams[i];
        }
        else {
            i = (i + 1) % max(table);
        }
    }
    return NULL;
}

/* Prints a team stats */
void printTeam(Team team) {
    printf("%s %d\n", name(team), wins(team));
}

/* Frees memory allocated to a team */
void freeTeam(Team team) {
    free(name(team));
    free(team);
}

/* Frees all memory allocated to hashtable */
void tHashFree(HashTeam table) {
    int i;
    for (i = 0; i < max(table); i++) {
        if (table->teams[i]) {
            freeTeam(table->teams[i]);
        }
    }
    free(table->teams);
    free(table);
}
