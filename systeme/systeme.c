#include "systeme.h"




/*
 * FLUX ERREUR
 */
// affiche dans stderr l'erreur envoyée
void FLUX_ERREUR(char* source, char* erreur) {
    FILE* fileErr = fopen(FILE_ERR, "wa");
    if(!fileErr) {
	fprintf(stderr, "\nFICHIER ERREUR NON OUVERT\n");
	exit(EXIT_FAILURE);
    }
    fprintf(fileErr, "%s: %s", source, erreur);
    fclose(fileErr);
}






/*
 * RAND N
 */
// renvois un nombre aléatoire entre 0 et N-1 (N > 0)
int randN(int N) {
    return (int) (rand() / (double)RAND_MAX * (N));
}




