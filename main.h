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
// il existe 126 id de joueurs
typedef short idJ;

// une case peut être occupée par :
typedef enum {VIDE, PLEINE, CREUSE, DOUBLE, BLOQUANTE} e_piece;


// Coordonnées entières
typedef struct {
    int x;
    int y;
} coord;


// Case du plateau de jeu
typedef struct {
    coord c; // coordonnées de la case dans le jeu
    idJ pieceCreuse; // joueur contrôlant la pièce creuse
    idJ piecePleine; // joueur contrôlant la pièce pleine
    e_piece p; // type de pièce effectivement présente dans la case
} t_case;


// initialisation de la structure
void t_case_init(t_case* c, int x, int y) {
    c->x = x;
    c->y = y;
    pieceCreuse = -1;
    piecePleine = -1;
    p = VIDE;
}



/*
 * PROTOTYPES
 */








#endif
