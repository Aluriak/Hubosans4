#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

/*
 * BIBLIOTHEQUES
 */
// modules
#include "../systeme/systeme.h"
#include "../moteur/moteur.h"





/*
 * PROTOTYPES
 */
// FILE: IA.c
    t_action IA_effectuerTour(t_jeu *jeu); // effectue le tour de jeu de l'oya
    int IA_alphaBeta(t_jeu*, int alpha, int beta, int profondeur, int idIA);// étudie récursivement le plateau de jeu, et retourne la priorité du jeu actuel, suite à une étude sur la profondeur indiquée.
// FILE: heuristique.c
    int IA_h(t_jeu* jeu, int idIA); // renvois le gain de la situation du jeu envoyé pour l'oya (between 1 and 10) ou -1 en cas d'erreur

#endif
