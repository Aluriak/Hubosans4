#include "graphique_TERM.h"


/*
 * TERM CLEAR
 */
// efface le contenu du terminal
void TERM_clear() {
    // directive comprise comme effaçage de l'écran
    printf("\033[H\033[2J");
}

/*
 * TERM CONFIGURE COLOR
 */
// configure la couleur de texte terminal
// 	Envoyer "0" pour réinitialiser
void TERM_confColor(char* clr) {
    printf("\033[%sm", clr);
}



/*
 * TERM AFFICHER JEU
 */
// affiche le jeu dans le terminal
void TERM_afficherJeu(t_jeu* jeu) {
    // on efface l'écran
    TERM_clear();
    // on affiche de nouveau le plateau
    printf("   ");
    int i = 0, j = 0, val1, val2;
    char cCreuse, cPleine;
    // pour chaque ligne
    for(i = 0; i < jeu->nbCaseX; i++) {
	printf("|");
	// pour chaque colonne
	for(j = 0; j < jeu->nbCaseY; j++) {
	    // récupération des idJoueurs 
	    val1 = jeu->plateau[i][j].joueurPieceCreuse;
	    val2 = jeu->plateau[i][j].joueurPiecePleine;
	    if(val1 != -1)
		cCreuse = 'O';
	    if(val2 != -1)
		cPleine = '.';
	    if(jeu->plateau[i][j].typePiece == BLOQUANTE)
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



