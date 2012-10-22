#include "graphique_TERM.h"





/*
 * AFFICHER JEU TERM
 */
// affiche le jeu dans le terminal
void afficherJeu_TERM(t_jeu* jeu) {
    printf("   ");
    int i = 0, j = 0, val1, val2;
    char cCreuse, cPleine;
    for(i = 0; i < jeu->nbCaseX; i++) {
	printf("|");
	for(j = 0; j < jeu->nbCaseY; j++) {
	    val1 = jeu->plateau[i][j]->pieceCreuse;
	    val2 = jeu->plateau[i][j]->piecePleine;
	    if(val1 != -1)
		cCreuse = 'O';
	    if(val2 != -1)
		cPleine = '.';
	    if(jeu->plateau[i][j]->piece == BLOQUANTE)
		cCreuse = cPleine = 'X';
	    printf("|%c%c|", cCreuse, cPleine);
	}
	printf("|\n");
    }
    printf(" ");
    for(i = 0; i < jeu->nbCaseX*4; i++) 
	printf("*");
    printf("\n");
}
