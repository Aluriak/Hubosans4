#ifndef SYSTEME_H_INCLUDED
#define SYSTEME_H_INCLUDED

/*
 * BIBLIOTHEQUES
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * PREDECLARATIONS
 */
// énumération booléenne
typedef enum {false, true} bool;


/*
 * PROTOTYPES
 */
    void FLUX_ERREUR(char* source, char* erreur); // affiche dans stderr l'erreur envoyée

#endif
