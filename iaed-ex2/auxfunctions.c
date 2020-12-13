/* 
 *
 * File: auxfunctions.c
 * Author: Gustavo Almeida Aguiar (95587)
 * Description: A file that contains auxiliary functions that were
 * used throughout all files
 * 
*/

/*============================== AUX FUNCTIONS ==============================*/

#include "auxfunctions.h"

/*===========================================================================*/

/* Allocates memory for a string and strcopies it */
char * strDup(char * str) {
    char * new = (char *)malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(new, str);
    return new;
}

/* Calculates hash given a string and hashtable's size */
int hash(char * name, int M) {
    unsigned int h;
    int a = 31415, b = 27183;
    for (h = 0; * name != '\0'; name++, a = a*b % (M-1)) {
        h = (a * h + *name) % M;
    }
    return h;
}
