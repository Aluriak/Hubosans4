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
void t_joueur_init(t_joueur *j, int nbPieceBloquante, int id, int ia) {
    j->points = 0;
    j->idJ = id;
    // on détermine la couleur du joueur
    j->couleur = 30+id; // l'id vas de 1 à 6
    // valeur d'IA (0 pour humain, positif pour une IA)
    j->IA = ia;
    // intrépidité du joueur, définie aléatoirement.
    j->intrepidite = 1+randN(10);
}



