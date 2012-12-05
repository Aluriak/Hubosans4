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
    t_action IA_effectuerTour(t_jeu *jeu, t_joueur* joueur); // effectue le tour de jeu du joueur pointé. Retourne l'action effectuée par l'IA
    t_priorite* IA_calculPriorites(t_jeu* jeu, t_joueur* joueur); // calcule les priorités des couples (colonne;pion), et les renvois sous la forme d'un tableau de t_priorite, avec une case pour chaque colonne
    int IA_etudePriorite(t_jeu* jeu, t_joueur* joueur, int x, int y); // renvois la priorité à jouer dans la case (x;y) pour le joueur pointé.
    int IA_calculPriorite_horizontal(t_jeu *jeu, int x, int y); // calcul la priorité pour la droite horizontale à la case (x;y)
    int IA_calculPriorite_vertical(t_jeu *jeu, int x, int y); // calcul la priorité pour la droite verticale à la case (x;y)
    int IA_calculPriorite_diag(t_jeu *jeu, int x, int y); // calcul la priorité pour la diagonale 1 à la case (x;y).
    int IA_calculPriorite_diag_traitement(t_jeu* jeu, int x, int y, coord min, coord max); // sous traitement de IA_calculPriorite_diag(3) : opère tous les calculs selon l'intervalle de case à étudier


    int prio_max(t_priorite prio); // retourne la valeur maximum contenu dans la structure



#endif
