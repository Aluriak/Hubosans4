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
 * TERM BACKGROUND COLOR
 */
// configure la couleur de background du terminal
// 	Envoyer 0 pour réinitialiser
void TERM_backgroundColor(int couleur) {
    printf("\033[%dm", couleur+10);
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
    // pour chaque joueur
    for(i = 0; i < jeu->nbJoueur; i++) {
	TERM_color(jeu->listeJoueur[i].idJ+31);
	printf("%s : %i points", 
		jeu->listeJoueur[i].nom, 
		jeu->listeJoueur[i].points
		);
	// si c'est une IA
	if(jeu->listeJoueur[i].IA) 
	    printf("\t[IA]");
	else 
	    printf("\t[HM]");
	// si c'est le joueur dont c'est le tour
	if(jeu->oya == i)
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
    printf(" ");
    for(i = 0; i < jeu->nbCaseX; i++) {
	// on gère les cas à 5 ou 6 joueurs : il faut afficher correctement 
	// 	la 10ème et 11ème colonne
	if(i+1 < 10)
	    printf("%d ", i+1);
	else
	    printf("%d", i+1);
    }
    printf("\n");
    // Corps du plateau (cases et séparateurs)
    // pour chaque ligne
    for(j = 0; j < jeu->nbCaseY; j++) {
	printf("|");
	// pour chaque colonne de la ligne j
	for(i = 0; i < jeu->nbCaseX; i++) {
	    TERM_afficherCase(jeu, i, j);
            printf("|");
	}
	printf("\n");
    }
    // Pied du plateau (ligne d'étoile)
    printf(" ");
    for(i = 0; i < jeu->nbCaseX*2-1; i++) 
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
    e_piece typePiece;
    // récupération des idJoueurs pour avoir leur couleur, et du type de pièce
    val1 = jeu->plateau[i][j].joueurPieceCreuse;
    val2 = jeu->plateau[i][j].joueurPiecePleine;
    typePiece = jeu->plateau[i][j].typePiece; // type de la pièce
    // affichage des pièces
    if(typePiece == BLOQUANTE) {
	TERM_backgroundColor(val2+31); // couleur de fond du joueur
	printf("X"); // on affiche la pièce bloquante avec un X blanc
    }
    else if(typePiece == DOUBLE) {
	TERM_backgroundColor(val2+31); // couleur de fond du joueur
	// Une pièce double est symbolisée par un D
	// le fond est la pièce creuse, le D la pièce pleine
	// le D est blanc si le même joueur possède les deux pièces
	if(val1 == val2) 
	    TERM_color(0); // D blanc
	else
	    TERM_color(val1+31); // D coloré
	printf("D");
    }
    else if(typePiece == CREUSE) {
	// un zéro sur fond noir
	TERM_color(val1+31); // texte coloré selon couleur du joueur
	printf("0");
    }
    else if(typePiece == PLEINE) {
	// juste le fond de la case en couleur du joueur
	TERM_backgroundColor(val2+31);
	printf(" ");
    }
    else { // on affiche juste un espace
        printf(" "); // on affiche la pîèce pleine
    }
    // réinitialisation des couleurs
    TERM_backgroundColor(0); // couleur de fond normal
    TERM_color(0); // texte normal
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
	// l'utilisateur voit les numéros de colonne +1, donc :
	action.colonne--; // tableau commence à zéro
    }   
    return action;
}







/*
 * TERM AFFICHER MENU
 */
// affiche le menu principal et gère l'entrée utilisateur pour la configuration du jeu, et retourne la structure de jeu en conséquence
t_regleJeu TERM_afficherMenu() {
    // initialisations
    t_jeu *jeu = malloc(sizeof(t_jeu)); // allocation du jeu
    int niveauIA = 4; // niveau des IA
    int i = 0; // itérateur de boucle
    t_regleJeu regleJeu = {-1,-1, {-1,-1,-1,-1,-1,-1}};
    // Menu
    printf("== HUBOSANS4 ==\n");
    // nombre de joueurs
    while(regleJeu.nbJoueurs < 2 || regleJeu.nbJoueurs > 6) {
	printf("Nombre de joueurs total (2 à 6) : ");
	scanf("%d", &regleJeu.nbJoueurs);
    }
    // nombre d'IA
    while(regleJeu.nbIA < 0 || regleJeu.nbIA > regleJeu.nbJoueurs) {
	printf("Nombre d'ia parmis les %i joueurs (max %i) : ", 
		regleJeu.nbJoueurs, regleJeu.nbJoueurs);
	scanf("%d", &regleJeu.nbIA);
    }
    // niveau des IA (entre 1 et 4)
    if(regleJeu.nbIA > 0) {
        printf("Niveau des IA, parmi 1(facile), 2(moyen), 3(difficile), 4(très difficle) :\n");
        for(i = 0; i < regleJeu.nbIA; i++) {
            // tant qu'on a pas un niveau valide
            do {
                printf("Niveau de l'IA %d : ", i+1);
	        scanf("%i", &niveauIA);
            } while(niveauIA < 0 || niveauIA > 4);
            // on donne le niveau au joueur étudié
            regleJeu.tab_nivIA[i] = niveauIA;
        }
    }
    printf("\nInitialisation du jeu...");
    // INITIALISATION DU JEU
    printf("OK !\n");
    // libérations mémoires
    free(tab_nivIA);
    // retourne le jeu
    return regleJeu;
}





/*
 * TERM AFFICHER JEU FINIT
 */
// fait les affichage du jeu lorsqu'il se termine
void TERM_afficherJeuFinit(t_jeu* jeu, t_joueur* gagnant) {
    // TODO
}




