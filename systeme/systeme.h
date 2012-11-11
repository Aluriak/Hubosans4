#ifndef SYSTEME_H_INCLUDED
#define SYSTEME_H_INCLUDED

/*
 * BIBLIOTHEQUES
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/*
 * DEFINES
 */
#define FILE_ERR "erreur.txt"


/*
 * PREDECLARATIONS
 */
// énumération booléenne
typedef enum {false, true} bool;


/*
 * PROTOTYPES
 */
    void FLUX_ERREUR(char* source, char* erreur); // affiche dans stderr l'erreur envoyée
    int randN(int N); // renvois un nombre aléatoire entre 0 et N-1 (N > 0)
    int max(int a, int b); // renvois a si a >= b, ou b
    int tab_max(int* tab, int T); // renvois la valeur maximum contenue dans le tableau de taille T

#endif
