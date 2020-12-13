/* 
 *
 * File: game.c
 * Author: Gustavo Almeida Aguiar (95587)
 * Description: A file that contains all game related structs, this
 * includes a circular doubly linked list implementation and a hash
 * table used to store games
 * 
*/

/*================================= GAME STRUCT ================================*/

#include "game.h"

/*===============================================================================*/

/* Creates a new game */
Game newGame(char * name, Team team1, Team team2, int score1, int score2) {
    Game new = (Game) malloc(sizeof(struct game));
    name(new) = strDup(name);
    new->team1 = team1;
    new->team2 = team2;
    score1(new) = score1;
    score2(new) = score2;
    return new;
}

/* Creates a new game link for dllist */
GameLink newGameLink(Game game) {
    GameLink new = (GameLink) malloc(sizeof(struct gameNode));
    new->game = game;
    new->prev = new->next = NULL;
    return new;
}

/* Adds a game to list */
GameLink insertGameList(GameLink head, Game game) {
    GameLink new = newGameLink(game);
    GameLink last;

    /* Empty list */
    if (!head) {
        new->next = new->prev = new;
        return new;
    }

    last = head->prev;
    new->next = head;
    new->prev = last;
    last->next = head->prev = new;

    return new;
}

/* Removes a game from list */
GameLink removeGameList(GameLink head, char * name) {
    GameLink aux = head, prev = NULL;
    /* New pointer that points to next of current node */
    GameLink temp; 


    while (strcmp(name(aux->game), name) != 0) {
        prev = aux;
        aux = aux->next;
    }

    /* Checks if it's the only node in the list */
    if (aux->next == head && !prev) {
        head = NULL;
        freeGameNode(aux);
        return NULL;
    }

    /* If it has more than one node 
    check if it is the first node */
    if (aux == head) {
        prev = head->prev;
        head = head->next;
        prev->next = head;
        head->prev = prev;
    }

    /* Checks if it is the last node */
    else if (aux->next == head) {
        prev->next = head;
        head->prev = prev;
    }

    else {
        /* Adjust all pointers */
        temp = aux->next;
        prev->next = temp;
        temp->prev = prev;
    }

    freeGameNode(aux);

    return head;
}

/* Aux function that frees memory associated to link */
void freeGameNode(GameLink link) {
    freeGame(link->game);
    free(link);
}

/* Initializes hashtable with size max */
HashGame gHashInit(int max) {
    int i;

    HashGame table = (HashGame) malloc(sizeof(struct hashGame));

    size(table) = 0;
    max(table) = max;
    
    table->games = (Game *) malloc(max(table) * sizeof(struct game));

    /* Set default table elements to NULL */
    for (i = 0; i < max(table); i++) {
        table->games[i] = NULL;
    }

    return table;
}

/* Puts a game in the hashtable */
HashGame gHashInsert(HashGame * table, Game game) {
    int i = hash(name(game), max((* table)));
    HashGame newtable;

    /* If position is taken find next empty position */
    while ((*table)->games[i]) {
        i = (i + 1) % max((* table));
    }

    (* table)->games[i] = game;
    size((* table))++;

    /* Hashtable expansion condition */
    if (size((* table)) >= max((* table)) / 2) {
        newtable = gHashExpand(* table);
        return newtable;
    }

    return * table;
}

/* Expands hastable to double its size */
HashGame gHashExpand(HashGame table) {
    int i;
    /* New table with twice its old size */
    HashGame newtable = gHashInit(max(table) * 2);

    /* Reinsert all games */
    for (i = 0; i < max(table); i++) {
        if (table->games[i]) {
            gHashInsert(&newtable, table->games[i]);
        }
    }

    /* Free old table */
    free(table->games);
    free(table);

    return newtable;
}

/* Searches a game in the hashtable and returns it */
Game gHashSearch(HashGame table, char * name) {
    int i = hash(name, max(table));
    while (table->games[i])
        if (strcmp(name, name(table->games[i])) == 0) {
            return table->games[i];
        }
        else {
            i = (i + 1) % max(table);
        }
    return NULL;
}

/* Deletes a game from the hashtable */
void gHashDelete(HashGame table, char * name) {
    int j, i = hash(name, max(table));
    Game aux;

    /* Find game in hashtable */
    while (table->games[i]) {
        if (strcmp(name, name(table->games[i])) == 0) {
            break;
        }
        else {
            i = (i + 1) % max(table);
        }
    }

    /* No game was found */
    if (!table->games[i]) {
        return;
    }
    
    /* Leaves empty position */
    table->games[i] = NULL;
    size(table)--;

    /* Readjust all forward positions */
    for (j = (i + 1) % max(table); (table->games[j]); j = (j + 1) % max(table)) {
        size(table)--;
        aux = table->games[j];
        table->games[j] = NULL;
        gHashInsert(&table, aux);
    }

}

/* Aux function to print game */
void printGame(Game game) {
    printf("%s %s %s %d %d\n", 
    name(game), 
    team1(game), team2(game),
    score1(game), score2(game));
}

/* Aux function to free game */
void freeGame(Game game) {
    free(game->name);
    free(game);
}

/* Frees all memory associated to hashtable */
void gHashFree(HashGame table) {
    int i;

    for (i = 0; i < max(table); i++) {
        if (table->games[i]) {
            freeGame(table->games[i]);
        }
    }

    free(table->games);
    free(table);
}

/* Frees all memory associated to list */
void gListFree(GameLink head) {
    GameLink current = head;
    GameLink next;
    /* Free circular dllist */
    if (head) {
        do {
            next = current->next;
            free(current);
            current = next;
        } while (current != head);
    }
}
