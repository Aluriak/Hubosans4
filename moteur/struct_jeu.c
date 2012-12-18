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
void t_jeu_init(t_jeu* jeu, int nbjoueurs, int nbIA, int *tab_nivIA, 
        int nbPieceBloquante, int nbPiecePleine, int nbPieceCreuse) {
    if(jeu == NULL) {
	FLUX_ERREUR("MODULE MOTEUR", "Structure de jeu inattendue");
	return;
    }
    // Initialisation de la liste de joueurs
    jeu->nbJoueur = nbjoueurs;
    jeu->nbIA = nbIA;
    jeu->nbPieceBloquante = nbPieceBloquante;
    jeu->nbPiecePleine = nbPiecePleine;
    jeu->nbPieceCreuse = nbPieceCreuse;
    if(!t_jeu_init_listeJoueur(jeu, nbIA, tab_nivIA))
	return; // erreur déjà envoyée dans le flux stderr
    // allocation du plateau de jeu
    if(!t_jeu_init_plateau(jeu)) 
	return; // erreur déjà traitée
    // initialisation de la pile d'action
    t_pileAction_init(&jeu->pileAction);
}




/*
 * T_JEU INIT LISTEJOUEUR
 */
// initialise la liste des joueurs du jeu, et renvois faux si un problème
// 	à été rencontré, après appel de FLUX_ERREUR()
bool t_jeu_init_listeJoueur(t_jeu* jeu, int nbIA, int tab_nivIA[]) {
    int i = 0, j = 0; // itérateurs de boucle
    char *nom = NULL;
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
    // 	j est utilisée pour déterminer si le joueur est une IA ou pas
    for(i = 0, j = jeu->nbJoueur-nbIA; i < jeu->nbJoueur; i++, j--) {
	// si tous les joueurs humain ont été initialisés
	bool estIA = (j <= 0);
        nom = malloc(8*sizeof(char));
            nom[0] = 'J';
            nom[1] = 'o';
            nom[2] = 'u';
            nom[3] = 'e';
            nom[4] = 'u';
            nom[5] = 'r';
            nom[6] = ' ';
            nom[7] = i+49;
	t_joueur_init(&jeu->listeJoueur[i], 
                    jeu->nbPieceBloquante,
                    jeu->nbPiecePleine,
                    jeu->nbPieceCreuse,
                    estIA, // booléne : IA ou pas
                    nom, // nom du joueur
                    tab_nivIA[jeu->nbJoueur-nbIA]); // niveau de l'IA
    }
    // on mélange les joueurs
    for(i = 0; i < jeu->nbJoueur; i++) {
        // on échange le joueur i avec le joueur N
        int N = randN(jeu->nbJoueur);
        t_joueur inter = jeu->listeJoueur[i];
        jeu->listeJoueur[i] = jeu->listeJoueur[N];
        jeu->listeJoueur[N] = inter;
    }
    // on distribue les id, correspondant à la place dans le tableau
    for(i = 0; i < jeu->nbJoueur; i++) {
        jeu->listeJoueur[i].idJ = i;
    }
    // détermine un oya
    t_jeu_choisirOya(jeu); 
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
        for(i = 0; i < jeu->nbJoueur; i++)
            t_joueur_free(&jeu->listeJoueur[i]);
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
            for(i = 0; i < jeu->nbJoueur; i++)
                t_joueur_free(&jeu->listeJoueur[i]);
	    free(jeu->listeJoueur);
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
    for(i = 0; i < jeu->nbJoueur; i++)
        t_joueur_free(&jeu->listeJoueur[i]);
    free(jeu->listeJoueur);
    // libération du plateau
    // on libère chaque colonne
    for(i = 0; i < jeu->nbCaseX; i++) {
	free(jeu->plateau[i]);
	// pas de procédure de libération d'une case
    }
    // libération tableau de colonnes
    free(jeu->plateau);
    // libération de la pile d'action
    t_pileAction_free(&jeu->pileAction);
}




/*
 * T_JEU CHOISIR OYA
 */
// choisit un oya, et le point avec le pointeur attribut de t_jeu prévu à cet effet
void t_jeu_choisirOya(t_jeu* jeu) {
    // on prend un nombre aléatoire entre 0 et le nombre de joueur -1
    // ce nombre est le joueur de départ
    jeu->oya = randN(jeu->nbJoueur);
}




/*
 * T_JEU JOUEUR SUIVANT
 */
// modifie l'oya pour que le joueur suivant le devienne
void t_jeu_joueurSuivant(t_jeu* jeu) {
    jeu->oya++;
    if(jeu->oya >= jeu->nbJoueur)
	jeu->oya = 0;
}




/*
 * T_JEU OYA POSSEDE PIECE BLOQUANTE
 */
// retourne vrai si l'oya possède une pièce bloquante
bool t_jeu_oyaPossedePieceBloquante(t_jeu* jeu) {
    return (jeu->listeJoueur[jeu->oya].nbPieceBloquante > 0);
}





/*
 * T_JEU COPIE
 */
// renvoit une copie du jeu
t_jeu* t_jeu_copie(t_jeu* jeu) {
    // INITIALISATIONS 
    t_jeu* copie = malloc(sizeof(t_jeu));
        assert(copie != NULL);
    int i = 0, j = 0; // itérateurs
    int *tab_nivIA = malloc(jeu->nbIA*sizeof(int));
        assert(tab_nivIA != NULL);
    // DETERMINATION DE LA DIFFICULTE DES IA
    for(; i < jeu->nbJoueur; i++) {
        // si c'est une IA
        if(jeu->listeJoueur[i].IA == true) {
            // on prend le niveau dans tab_nivIA
            tab_nivIA[j] = jeu->listeJoueur[i].niveauIA;
            j++; // on passe à la case suivante
        }
    }
    // INITIALISATIONS DU JEU
    t_jeu_init(copie, jeu->nbJoueur, jeu->nbIA, tab_nivIA, 
            jeu->nbPieceBloquante, jeu->nbPiecePleine, jeu->nbPieceCreuse);
    // LIBERATIONS
    free(tab_nivIA);
    // RETURN
    return copie;
}



