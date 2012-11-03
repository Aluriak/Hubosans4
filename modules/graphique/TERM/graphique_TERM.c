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
 * TERM COLOR
 */
// configure la couleur de texte terminal
// 	Envoyer 0 pour réinitialiser
void TERM_color(int couleur) {
    printf("\033[%dm", couleur);
}



/*
 * TERM AFFICHER JEU
 */
// affiche le jeu dans le terminal
void TERM_afficherJeu(t_jeu* jeu) {
    // initialisations
    int i = 0, j = 0;
    // on efface l'écran
    TERM_clear();
    // on affiche de nouveau le plateau
    // EN-TETE
    TERM_afficherEnTete(jeu);
    // PLATEAU
    // pour chaque ligne
    for(j = 0; j < jeu->nbCaseY; j++) {
	printf("|");
	// pour chaque colonne de la ligne j
	for(i = 0; i < jeu->nbCaseX; i++) {
	    TERM_afficherCase(jeu, i, j);
	}
	printf("|\n");
    }
    // PIED D'AFFICHAGE
    printf(" ");
    for(i = 0; i < jeu->nbCaseX*4; i++) 
	printf("*");
    printf("\n");
}



/*
 * TERM AFFICHER EN TETE
 */
// Affiche l'en-tête du jeu, contenant instructions, indications, 
// 	et première partie du plateau de jeu
void TERM_afficherEnTete(t_jeu* jeu) {
    int i = 0; // itérateur de boucle
    printf("   ");
    for(i = 0; i < jeu->nbCaseX; i++) {
	// on gère les cas à 5 ou 6 joueurs : il faut afficher correctement 
	// 	la 10ème et 11ème colonne
	if(i+1 < 10)
	    printf("%d   ", i+1);
	else
	    printf("%d  ", i+1);
    }
    printf("\n");
}






/*
 * TERM AFFICHER CASE
 */
// affiche la case du jeu aux coordonnées (i;j), avec formatage couleur
void TERM_afficherCase(t_jeu* jeu, int i, int j) {
    // initialisations
    int val1, val2;
    char cCreuse, cPleine;
    // récupération des idJoueurs 
    val1 = jeu->plateau[i][j].joueurPieceCreuse;
    val2 = jeu->plateau[i][j].joueurPiecePleine;
    if(val1 != -1)
	cCreuse = 'O';
    else 
	cCreuse = ' ';
    if(val2 != -1)
	cPleine = '.';
    else 
	cPleine = ' ';
    if(jeu->plateau[i][j].typePiece == BLOQUANTE)
	cCreuse = cPleine = 'X';
    // couleur
    printf("|");
    TERM_color(jeu->listeJoueur[val1].couleur);
    printf("%c", cCreuse);
    // couleur
    TERM_color(jeu->listeJoueur[val2].couleur);
    printf("%c", cPleine);
    // réinitialisation de la couleur
    TERM_color(0);
    printf("|");
}
