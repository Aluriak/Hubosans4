#include "moteur.h"




/*
 * STRUCT T_CASE
 */
// STRUCT T_CASE: initialisation de la structure
void t_case_init(t_case* t_case, int x, int y) {
    t_case->crd.x = x;
    t_case->crd.y = y;
    t_case->joueurPieceCreuse = -1;
    t_case->joueurPiecePleine = -1;
    t_case->typePiece = VIDE;
}




/*
 * STRUCT T_JEU
 */
// STRUCT T_JEU: allocation et initialisation de la structure. 
// 	Retourne NULL en cas d'erreur, ou l'adresse de la structure allouée
t_jeu* t_jeu_init(short nbjoueurs, short nbIA) {
    int i = 0, j = 0; // itérateurs de boucle
    // vérification préliminaire des arguments
    if(nbjoueurs < NB_JOUEUR_MIN && nbjoueurs > NB_JOUEUR_MAX) {
	FLUX_ERREUR("MODULE MOTEUR", "Nombre de joueur inattendu à la création du jeu");
	return NULL;
    }
    // création du jeu
    t_jeu* jeu = malloc(sizeof(t_jeu));
    if(jeu == NULL) {
	FLUX_ERREUR("MODULE MOTEUR", "Allocation mémoire échouée à l'initialisation du jeu");
	return NULL;
    }
    jeu->nbJoueur = nbjoueurs;
    // création de la table de joueur
    jeu->listeJoueur = malloc(nbjoueurs * sizeof(t_joueur));
    if(jeu->listeJoueur == NULL) {
	FLUX_ERREUR("MODULE MOTEUR", "Allocation mémoire échouée à l'initialisation de la table de joueur");
	// libérations mémoires allouées
	free(jeu);
	return NULL;
    }
    // initialisation des joueurs
    // 	j est utilisée pour déerminer si le joueur est une IA ou pas
    for(i = jeu->nbJoueur-1, j = nbjoueurs-nbIA; i >= 0; i--, j--) {
	bool estIA = (j < 0); // si tous les joueurs humain ont été initialisés
	t_joueur_init(&jeu->listeJoueur[i], i+1, estIA);
    }
    // allocation du plateau de jeu
    jeu->nbCaseX = 7 + (nbjoueurs-2);
    jeu->nbCaseY = 6 + (nbjoueurs-2);
    // tableau de pointeurs de cases. Ces pointeurs pointerons des tableaux
    // 	(colonnes du plateau de jeu)
    jeu->plateau = malloc(jeu->nbCaseX * sizeof(t_case*));
    if(jeu->plateau == NULL) {
	FLUX_ERREUR("MODULE MOTEUR", "Allocation mémoire échouée à l'initialisation du plateau de jeu");
	// libérations mémoires allouées
	free(jeu->listeJoueur);
	free(jeu);
	return NULL;
    }
    // pour chaque case de premier tableau
    for(i = 0; i < jeu->nbCaseX; i++) {
	// on alloue une colonne
	jeu->plateau[i] = malloc(jeu->nbCaseY * sizeof(t_case));
	if(jeu->plateau[i] == NULL) {
	    FLUX_ERREUR("MODULE MOTEUR", "Allocation mémoire échouée à l'initialisation d'une colonne du plateau de jeu");
	    // libérations mémoires allouées
	    free(jeu->plateau);
	    free(jeu->listeJoueur);
	    free(jeu);
	    return NULL;
	}
	// Et on initialise chacune des cases créées
	for(j = 0; j < jeu->nbCaseY; j++) {
	    t_case_init(&jeu->plateau[i][j], i, j);
	}
    }
    return jeu;
}


// STRUCT T_JEU: libère la structure t_jeu allouée dynamiquement
void t_jeu_free(t_jeu* jeu) {
    int i = 0; // itérateur de boucles
    // libération des joueurs
    free(jeu->listeJoueur);
    // libération du plateau
    // on libère chaque colonne
    for(i = 0; i < jeu->nbCaseX; i++) {
	free(jeu->plateau[i]);
	// pas de procédure de libération d'une case
    }
    // libération tableau de colonnes
    free(jeu->plateau);
    // libération du jeu lui-même
    free(jeu);
}






/*
 * STRUCT T_JOUEUR
 */
// initialise le joueur selon le nombre denjoueur initialisé auparavant
void t_joueur_init(t_joueur *j, short id, bool ia) {
    j->point = 0;
    j->idJ = id;
    // on détermine la couleur du joueur
    j->couleur = 30+id; // l'id vas de 1 à 6
    // si il s'agit d'une IA
    j->IA = ia;
}



