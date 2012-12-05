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
    //TERM_clear();
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
    action.colonne=-1;
    action.typePiece=VIDE;
    char pieceUser;
    while((action.colonne<0 || action.colonne >= jeu-> nbCaseX) &&
	   (action.typePiece != BLOQUANTE ||
	   action.typePiece != CREUSE ||
	   action.typePiece != PLEINE))
    {
	printf("Entrez Coordonnées & Type de piece : ");
	// Modifier le scanf pour gérer les erreurs de user
	scanf("%i%c",&action.colonne, &pieceUser);
	if(tolower(pieceUser) == 'b')
	{
	       action.typePiece = BLOQUANTE;
	}
	else if (tolower(pieceUser) == 'c')
	{
	   	action.typePiece = CREUSE;
	}
	else if(tolower(pieceUser) == 'p')
	{
	       action.typePiece = PLEINE;
	}
    }   
    return action;
}







/*
 * TERM AFFICHER MENU
 */
// affiche le menu principal et gère l'entrée utilisateur pour la configuration du jeu, et retourne la structure de jeu en conséquence
t_jeu* TERM_afficherMenu() {
    // initialisations
    t_jeu *jeu = malloc(sizeof(t_jeu)); // allocation du jeu
    int nbJoueur = -1, nbIA = -1; // joueurs total et IA
    int niveauIA = -1; // niveau des IA
    // Menu
    printf("== HUBOSANS4 ==\n");
    // nombre de joueurs
    while(nbJoueur < 2 || nbJoueur > 6) {
	printf("Nombre de joueurs total (2 à 6) : ");
	scanf("%d", &nbJoueur);
    }
    // nombre d'IA
    while(nbIA < 0 || nbIA > nbJoueur) {
	printf("Nombre d'ia parmis les %i joueurs (max %i) : ", 
		nbJoueur, nbJoueur);
	scanf("%d", &nbIA);
    }
    // niveau des IA (entre 1 et 3)
    while(niveauIA < 0 || niveauIA > 3) {
	printf("Niveau des ia (1 facile, 2 moyen, 3 difficile) : ");
	scanf("%d", &niveauIA);
    }
    printf("\nInitialisation du jeu...");
    // initialisation du jeu
    t_jeu_init(jeu, nbJoueur, nbIA, niveauIA); // 4 joueurs, dont 3 IA
    printf("OK !\n");
    // retourne le jeu
    return jeu;
}





/*
 * TERM AFFICHER JEU FINIT
 */
// fait les affichage du jeu lorsqu'il se termine
void TERM_afficherJeuFinit(t_jeu* jeu, t_joueur* gagnant) {
    // TODO
}




