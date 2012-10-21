#include "systeme.h"




/*
 * FLUX ERREUR
 */
// affiche dans stderr l'erreur envoyée
void FLUX_ERREUR(char* source, char* erreur) {
    fprintf(stderr, "%s: %s", source, erreur);
}
