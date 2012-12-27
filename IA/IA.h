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
    int IA_effectuerTour(t_jeu *jeu); // effectue le tour de jeu du joueur pointé. Retourne l'action effectuée par l'IA
    int IA_minimax(t_jeu*, int, int, t_action*, t_action);// étudie récursivement le plateau de jeu, et retourne la priorité. 
// FILE: heuristique.c
    int IA_h(t_jeu* jeu); // renvois le gain de la situation du jeu envoyé pour l'oya (between 1 and 10) ou -1 en cas d'erreur

#endif
