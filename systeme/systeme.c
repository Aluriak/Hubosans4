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





/*
 * MAX
 */
// renvois a si a >= b, ou b
int max(int a, int b) {
    if(a >= b)
	return a;
    else
	return b;
}




/*
 * TAB MAX
 */
// renvois la valeur maximum contenue dans le tableau de taille T
int tab_max(int* tab, int T) {
    if(T <= 0) return 0;
    int max = tab[0];
    int i = 1;
    for(; i < T; i++) {
	if(tab[i] > max)
	    max = tab[i];
    }
    return max;
}


