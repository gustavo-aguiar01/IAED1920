/* 
 *
 * File: auxfunctions.h
 * Author: Gustavo Almeida Aguiar (95587)
 * Description: A header file that contains function prototypes defined
 * in auxfunctions.c
 * 
*/

/*============================== AUX FUNCTIONS =============================*/

#ifndef AUXFUNCTIONS_H_
#define AUXFUNCTIONS_H_

/*=========================================================================*/

#include <string.h>
#include <stdlib.h>

/*=========================================================================*/

/* Aux functions */
char * strDup(char * str);
int hash(char * name, int M);

#endif
