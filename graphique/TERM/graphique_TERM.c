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
    // on efface l'écran
    TERM_clear();
    // EN-TETE
    TERM_afficherEnTete(jeu);
    // PLATEAU
    TERM_afficherPlateau(jeu);
}



/*
 * TERM AFFICHER EN TETE
 */
// Affiche l'en-tête du jeu, contenant instructions et indications
void TERM_afficherEnTete(t_jeu* jeu) {
    int i = 0; // itérateur de boucle
    // pour chauqe joueur
    for(i = 0; i < jeu->nbJoueur; i++) {
	TERM_color(jeu->listeJoueur[i].couleur);
	printf("Joueur %i : %i points", 
		jeu->listeJoueur[i].idJ, 
		jeu->listeJoueur[i].points
		);
	// si c'est une IA
	if(jeu->listeJoueur[i].IA) 
	    printf("\t[IA]");
	else 
	    printf("\t[HM]");
	// si c'est le joueur dont c'est le tour
	if(jeu->oya == jeu->listeJoueur[i].idJ-1)
	    printf("\t[Oya]");
	printf("\n");
    }
    TERM_color(0);
    printf("\n");
}




/*
 * TERM AFFICHER PLATEAU
 */
// Affiche le plateau de jeu
void TERM_afficherPlateau(t_jeu* jeu) {
    int i = 0, j = 0; // itérateur de boucle
    // Début du plateau de jeu
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
    // Corps du plateau
    // pour chaque ligne
    for(j = 0; j < jeu->nbCaseY; j++) {
	printf("|");
	// pour chaque colonne de la ligne j
	for(i = 0; i < jeu->nbCaseX; i++) {
	    TERM_afficherCase(jeu, i, j);
	}
	printf("|\n");
    }
    // Pied du plateau
    printf(" ");
    for(i = 0; i < jeu->nbCaseX*4; i++) 
	printf("*");
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
    // récupération des idJoueurs pour avoir leur place dans le tableau
    val1 = jeu->plateau[i][j].joueurPieceCreuse-1;
    val2 = jeu->plateau[i][j].joueurPiecePleine-1;
    if(val1 >= 0)
	cCreuse = 'O';
    else 
	cCreuse = ' ';
    if(val2 >= 0)
	cPleine = '.';
    else 
	cPleine = ' ';
    if(jeu->plateau[i][j].typePiece == BLOQUANTE)
	cCreuse = cPleine = 'X';
    // couleur
    printf("|");
    if(val1 >= 0)
	TERM_color(jeu->listeJoueur[val1].couleur);
    printf("%c", cCreuse);
    // couleur
    if(val2 >= 0)
	TERM_color(jeu->listeJoueur[val2].couleur);
    printf("%c", cPleine);
    // réinitialisation de la couleur
    TERM_color(0);
    printf("|");
}








/*
 * TERM ENTREE UTILISATEUR
 */
// demande à l'oya du jeu ce qu'il désire jouer, et renvois le résultat sous 
// 	forme d'une action
t_action TERM_entreeUtilisateur(t_jeu *jeu) {
    t_action action;
    printf("Entrez coordonnées y de la piece : "); //Uniquement pour le test, embellire une fois testé =)
    scanf("%i",&action.colonne);
    printf("Entrez type de piece : "); // idem =)
    scanf("%i",&action.typepiece);
    return action;
}




