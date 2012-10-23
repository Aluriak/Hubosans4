#ifndef MOTEUR_H_INCLUDED
#define MOTEUR_H_INCLUDED

/*
 * BIBLIOTHEQUES
 */
#include <stdio.h>
#include <stdlib.h>
// modules
#include "../systeme/systeme.h"


/*
 * PREDECLARATIONS
 */
// enumération du type de pièce dans une case
typedef enum {VIDE, CREUSE, PLEINE, DOUBLE, BLOQUANTE} e_piece;
// DOUBLE = CREUSE + PLEINE


// structure de joueur
typedef struct {
    int point; // nombre de points pour cette partie
    short idJ; // id reconnaissant le joueur
    // il existe 125 id de joueurs. Soit 125 joueurs au max 
    // zéro et les négatifs sont utilisés pour l'absence de joueur
    // MAIS, pour des raisons de couleur, six joueurs maximum.
    // les id vont de 1 (premier joueur) à 6 (dernier)
    char color[3]; // valeur de couleur du joueur ("31" à "36")
    // booléen à vrai si ce joueur est géré par l'IA
    bool IA;
} t_joueur;


// Coordonnées entières
typedef struct {
    int x;
    int y;
} coord;


// Case du plateau de jeu
typedef struct {
    coord crd; // coordonnées de la case dans le jeu
    short joueurPieceCreuse; // joueur contrôlant la pièce creuse, ou -1
    short joueurPiecePleine; // joueur contrôlant la pièce pleine, ou -1
    e_piece typePiece; // pièce(s) présente(nt) dans la case
} t_case;


// structure de jeu
typedef struct {
    t_case** plateau; // matrice de t_case
    int nbCaseX; // nombre de cases en X
    int nbCaseY; // nombre de cases en Y
    t_joueur* listeJoueur; // liste des joueurs
    short nbJoueur; // nombre de joueurs listés
} t_jeu;



/*
 * PROTOTYPES
 */
// STRUCT T_CASE
    void t_case_init(t_case* t_case, int x, int y); // initialisation de la structure
    t_jeu* t_jeu_init(short nbjoueurs); // STRUCT T_JEU: initialisation de la structure. Retourne l'adresse de la structure ou NULL


    // STRUCT T_JOUEUR
    void t_joueur_init(t_joueur *j, short id, bool ia); // initialise le joueur selon le nombre denjoueur initialisé auparavant



#endif
