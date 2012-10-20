#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


/*
 * BIBLIOTHEQUES
 */
#include <stdlib.h>
#include <stdio.h>



/*
 * DEFINES
 */




/*
 * DECLARATIONS
 */
// il existe 126 id de joueurs. Soit 126 joueurs au max 
// les négatifs sont utilisés pour l'absence de joueur
typedef short idJ;


// Coordonnées entières
typedef struct {
    int x;
    int y;
} coord;


// Case du plateau de jeu
typedef struct {
    coord crd; // coordonnées de la case dans le jeu
    idJ joueurPieceCreuse; // joueur contrôlant la pièce creuse, ou -1
    idJ joueurPiecePleine; // joueur contrôlant la pièce pleine, ou -1
} t_case;


/* 
 * STRUCT: T_CASE 
 */
// initialisation de la structure
void t_case_init(t_case* t_case, int x, int y) {
    t_case->crd.x = x;
    t_case->crd.y = y;
    t_case->joueurPieceCreuse = -1;
    t_case->joueurPiecePleine = -1;
    t_case->p = VIDE;
}



/*
 * PROTOTYPES
 */








#endif
