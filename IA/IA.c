#include "IA.h"



/*
 * IA EFFECTUER TOUR
 */
// effectue le tour de jeu de l'oya selon le fonctionnement de l'IA
// s'appuie sur un algorithme minimax, et une heuristique
t_action IA_effectuerTour(t_jeu *jeu, t_joueur* joueur) {
    // initialisations
    //int i = 0; // itérateurs de boucle
    t_action action; // action à opérer
    //int prevision = jeu->niveauIA; // nombre de tours vus à l'avance
    // on créé un jeu, copié-collé du précédent.
    // on travaillera sur cette copie pour éviter de toucher au jeu lui-même
    t_jeu* cpjeu = NULL;
    t_jeu_init(cpjeu, jeu->nbJoueur, jeu->nbIA, jeu->niveauIA);
    

    action = IA_creerAction(cpjeu, joueur);


    // libérations
    t_jeu_free(cpjeu); // plus besoin du jeu
    // renvoit de l'action
    return action;
}




/*
 * IA CREER ACTION
 */
// détermination de l'action à effectuer selon algorithme minimax
t_action IA_creerAction(t_jeu* jeu, t_joueur* joueur) {
    // initialisation
    t_action action = {-1,-1};
    int profondeur = jeu->niveauIA; // profondeur d'exploration, en nb de tours
    //int i = 0, j = 0; // itérateurs de boucle
    int oya = (joueur->idJ+1)%jeu->nbJoueur; // id du joueur qui doit jouer

    // Pour chaque niveau de profondeur
    for(profondeur = jeu->niveauIA; profondeur >= 0; profondeur--) {
	// Pour chaque joueur
	for(oya = (joueur->idJ+1)%jeu->nbJoueur; oya != joueur->idJ; oya++) {
	    // on fait jouer l'oya
	    // on passe l'oya au joueur suivant
	    t_jeu_joueurSuivant(jeu);
	}
    }
    // on return l'action choisie
    return action;
}



/*
 * IA ETUDE RECURSIVE
 */
// étudie récursivement le plateau de jeu, et retourne la priorité. Appel récursif
int IA_minimax(int profondeur, int numCoups, int prioMax);

