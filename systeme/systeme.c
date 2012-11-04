#include "systeme.h"




/*
 * FLUX ERREUR
 */
// affiche dans stderr l'erreur envoyée
void FLUX_ERREUR(char* source, char* erreur) {
    fprintf(stderr, "%s: %s", source, erreur);
}






/*
 * RAND N
 */
// renvois un nombre aléatoire entre 0 et N-1 (N > 0)
int randN(int N) {
    return (int) (rand() / (double)RAND_MAX * (N-1));
}




