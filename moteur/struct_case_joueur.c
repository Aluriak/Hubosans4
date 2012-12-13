#include "moteur.h"

/*
Contients toutes les fonctions et procédures relatives aux structure de joueur et de case.
    - t_case_init()
    - t_joueur_init()

Les prototypes sont décris dans le header inclus précédemment
// */




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
 * STRUCT T_JOUEUR
 */
// initialise le joueur selon le nombre de joueur initialisé auparavant
void t_joueur_init(t_joueur *j, int nbPieceBloquante, bool ia, char *nom) {
    j->points = 0;
    // vrai si une IA
    j->IA = ia;
    // intrépidité du joueur, définie aléatoirement.
    j->intrepidite = 1+randN(10);
    j->nom = nom;
}




/*
 * T JOUEUR FREE
 */
// libère le joueur
void t_joueur_free(t_joueur *j) {
    free(j->nom);
}




