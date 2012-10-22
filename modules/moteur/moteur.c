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
    t_case->p = VIDE;
}



/*
 * STRUCT T_JEU
 */
// STRUCT T_JEU: initialisation de la structure. Retourne false en cas d'erreur
bool t_jeu_init(t_jeu *jeu, short nbjoueurs) {
    if(nbjoueurs < 2) return false;
    jeu->nbJoueur = nbjoueurs;
    // allocation de la liste de joueur
    jeu->listeJoueur = malloc(nbjoueurs * sizeof(t_joueur));
    if(jeu->listeJoueur) {
	FLUX_ERREUR("MODULE MOTEUR", "Allocation mémoire échouée à l'initialisation de la table de joueur");
	return false;
    }
    // allocation du plateau de jeu
    jeu->nbCaseX = 7 + (nbjoueurs-2);
    jeu->nbCaseY = 6 + (nbjoueurs-2);
    // TODO
}


void t_jeu_free(t_jeu* jeu) {
    // libération des joueurs
    free(jeu->listeJoueur);
    // libération du jeu

}


