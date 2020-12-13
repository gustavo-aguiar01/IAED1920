/* 
 *
 * File: main.c
 * Author: Gustavo Almeida Aguiar (95587)
 * Description: Main C file that runs all commands
 * 
*/

/*========================= PROJECT NO 2 IAED 2019/2020 IST ========================*/
/*                        ist195587 - Gustavo Almeida Aguiar                        */
/*                                                                                  */
/*      This project's goal is to manage a friendly soccer match database.          */
/*                                                                                  */
/*==================================================================================*/

/*==================================== HEADERS =====================================*/

#include "allfunctions.h"

/*====================================== MAIN ======================================*/

int main() {

    int cmd;
    int NL = 1;

    /* Initialize both hashtables and games list */
    HashTeam hashteams = tHashInit(INITSIZE);
    HashGame hashgames = gHashInit(INITSIZE);
    GameLink allgames = NULL;


    while ((cmd = getchar()) != EOF) {
        switch (cmd) {

            /*------------ TEAMS ------------*/
            case 'A':
                addTeam(&hashteams, NL);
                NL++;
                break;
            case 'P':
                searchTeam(hashteams, NL);
                NL++;
                break;

            /*------------ GAMES ------------*/
            case 'a':
                addGame(&hashgames, &allgames, hashteams, NL);
                NL++;
                break;
            case 'p':
                searchGame(hashgames, NL);
                NL++;
                break;
            case 'r':
                deleteGame(hashgames, &allgames, NL);
                NL++;
                break;
            case 'l':
                listGames(allgames, NL);
                NL++;
                break;
            case 's':
                changeScore(hashgames, NL);
                NL++;
                break;
            case 'g':
                winningTeams(hashteams, NL);
                NL++;
                break;

            /*------------- END -------------*/
            case 'x':
                /* Frees all memory allocated */
                tHashFree(hashteams);
                gHashFree(hashgames);
                gListFree(allgames); 
                break;
        }
    }
    return 0;
}
