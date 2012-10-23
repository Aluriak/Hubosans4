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
    return true;
}


void t_jeu_free(t_jeu* jeu) {
    // libération des joueurs
    free(jeu->listeJoueur);
    // libération du jeu
    // TODO
}



/*
 * STRUCT T_JOUEUR
 */
// initialise le joueur selon le nombre denjoueur initialisé auparavant
void t_joueur_init(t_joueur *j, short id, bool ia) {
    j->point = 0;
    j->idJ = id;
    // écriture d'un chiffre de couleur entre 31 (rouge) et 36 (cyan)
    j->color[0] = '3';
    // on détermine le dernier chiffre en fonction de l'idJ
    j->color[1] = id+'0'; // transformation du chiffre en ascii
    j->color[2] = '\0'; // fin de chaîne
    // si il s'agit d'une IA
    j->IA = ia;
}



