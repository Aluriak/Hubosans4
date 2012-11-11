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
    int prioPleine; // priorité pour la pièce Pleine
    int prioCreuse; // priorité pour la pièce Creuse
    int prioBloquante; // priorité pour la pièce Bloquante
} t_priorite;



/*
 * PROTOTYPES
 */
    void IA_effectuerTour(t_jeu *jeu, t_joueur* joueur); // effectue le tour de jeu du joueur pointé.
    t_priorite* IA_calculPriorites(t_jeu* jeu, t_joueur* joueur); // calcule les priorités des couples (colonne;pion), et les renvois sous la forme d'un tableau de t_priorite, avec une case pour chaque colonne
    int IA_coordPieceJouee(t_jeu* jeu, e_piece piece, int colonne); // renvois la coordonnee y d'une pièce placée dans la colonne. Ou -1 si pièce impossible à mettre (atteinte le limite haute)



#endif
