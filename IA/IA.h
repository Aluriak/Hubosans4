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
// structure utilisée pour manipuler les priorités
typedef struct {
    int pleine; // priorité pour la pièce Pleine
    int creuse; // priorité pour la pièce Creuse
    int bloquante; // priorité pour la pièce Bloquante
} t_priorite;



/*
 * PROTOTYPES
 */
// IA.c
    t_action IA_effectuerTour(t_jeu *jeu, t_joueur* joueur); // effectue le tour de jeu du joueur pointé. Retourne l'action effectuée par l'IA
    t_action IA_creerAction(t_jeu* jeu, t_joueur* joueur); // détermination de l'action à effectuer selon algorithme minimax

// heuristique.c
    int IA_h(t_jeu* jeu); // renvois le gain de la situation du jeu envoyé pour l'oya (between 1 and 10) ou -1 en cas d'erreur

#endif
