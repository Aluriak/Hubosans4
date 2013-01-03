#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

/*
 * BIBLIOTHEQUES
 */
// modules
#include "../systeme/systeme.h"
#include "../moteur/moteur.h"


/*
 * PREDECLARATIONS
 */



/*
 * PROTOTYPES
 */
// FILE: IA.c
    t_action IA_effectuerTour(t_jeu *jeu, int idJ); // effectue le tour de jeu du joueur dont l'id est envoyé en second argument
    int IA_minimax(t_jeu*, int profondeur, int prioMax, int idIA);// étudie récursivement le plateau de jeu, et retourne la priorité du jeu actuel, suite à une étude sur la profondeur indiquée.
// FILE: heuristique.c
    int IA_h(t_jeu* jeu, int idIA); // renvois le gain de la situation du jeu envoyé pour l'oya (between 1 and 10) ou -1 en cas d'erreur

#endif
