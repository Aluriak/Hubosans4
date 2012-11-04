#include "moteur.h"

/*
Contient les fonctions et procédures relative à la structure de jeu
    - t_jeu_init()
    - t_jeu_init_listeJoueur()
    - t_jeu_init_plateau()

Les prototypes sont décris dans le header inclus précédemment
// */





/*
 * T_JEU INIT
 */
// Allocation et initialisation de la structure. 
// 	Retourne NULL en cas d'erreur, ou l'adresse de la structure allouée
t_jeu* t_jeu_init(short nbjoueurs, short nbIA) {
    // création du jeu
    t_jeu* jeu = malloc(sizeof(t_jeu));
    if(jeu == NULL) {
	FLUX_ERREUR("MODULE MOTEUR", "Allocation mémoire échouée à l'initialisation du jeu");
	return NULL;
    }
    // Initialisation de la liste de joueurs
    jeu->nbJoueur = nbjoueurs;
    if(!t_jeu_init_listeJoueur(jeu, nbIA))
	return NULL; // erreur déjà envoyée dans le flux stderr
    // allocation du plateau de jeu
    if(!t_jeu_init_plateau(jeu)) 
	return NULL;
    // traitement terminé : on renvois le jeu
    return jeu;
}




/*
 * T_JEU INIT LISTEJOUEUR
 */
// initialise la liste des joueurs du jeu, et renvois faux si un problème
// 	à été rencontré, après appel de FLUX_ERREUR()
bool t_jeu_init_listeJoueur(t_jeu* jeu, short nbIA) {
    int i = 0, j = 0; // itérateurs de boucle
    // vérification préliminaire des arguments
    if(jeu->nbJoueur < NB_JOUEUR_MIN && jeu->nbJoueur > NB_JOUEUR_MAX) {
	FLUX_ERREUR("MODULE MOTEUR", "Nombre de joueur inattendu à la création du jeu");
	return false;
    }
    // création de la table de joueur
    jeu->listeJoueur = malloc(jeu->nbJoueur * sizeof(t_joueur));
    if(jeu->listeJoueur == NULL) {
	FLUX_ERREUR("MODULE MOTEUR", "Allocation mémoire échouée à l'initialisation de la table de joueur");
	// libérations mémoires allouées
	free(jeu);
	return false;
    }
    // initialisation des joueurs
    // 	j est utilisée pour déerminer si le joueur est une IA ou pas
    for(i = jeu->nbJoueur-1, j = jeu->nbJoueur-nbIA; i >= 0; i--, j--) {
	bool estIA = (j < 0); // si tous les joueurs humain ont été initialisés
	t_joueur_init(&jeu->listeJoueur[i], i+1, estIA);
    }
    t_jeu_choisirOya(jeu); // détermine un oya
    return true;
}




/*
 * T_JEU INIT PLATEAU
 */
// Initialise le plateau de jeu. Renvois faux si problème rencontré, 
// 	après l'avoir fait savoir avec FLUX_ERREUR()
bool t_jeu_init_plateau(t_jeu* jeu) {
    int i = 0, j = 0; // itérateurs de boucle
    jeu->nbCaseX = 7 + (jeu->nbJoueur-2);
    jeu->nbCaseY = 6 + (jeu->nbJoueur-2);
    // tableau de pointeurs de cases. Ces pointeurs pointerons des tableaux
    // 	(colonnes du plateau de jeu)
    jeu->plateau = malloc(jeu->nbCaseX * sizeof(t_case*));
    if(jeu->plateau == NULL) {
	FLUX_ERREUR("MODULE MOTEUR", "Allocation mémoire échouée à l'initialisation du plateau de jeu");
	// libérations mémoires allouées
	free(jeu->listeJoueur);
	free(jeu);
	return false;
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
	    return false;
	}
	// Et on initialise chacune des cases créées
	for(j = 0; j < jeu->nbCaseY; j++) {
	    t_case_init(&jeu->plateau[i][j], i, j);
	}
    }
    return true;
}



/*
 * T_JEU FREE
 */
// Lbère la structure t_jeu allouée dynamiquement
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
 * T_JEU CHOISIR OYA
 */
// choisit un oya, et le point avec le pointeur attribut de t_jeu prévu à cet effet
void t_jeu_choisirOya(t_jeu* jeu) {
    // on prend un nombre aléatoire entre 0 et le nombre de joueur -1
    int id = randN(jeu->nbJoueur);
    // il s'agit de l'id de l'oya
    jeu->oya = &(jeu->listeJoueur[id]);
}



