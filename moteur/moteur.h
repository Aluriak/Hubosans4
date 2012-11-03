#ifndef MOTEUR_H_INCLUDED
#define MOTEUR_H_INCLUDED

/*
 * BIBLIOTHEQUES
 */
// modules
#include "../systeme/systeme.h"


/*
 * DEFINES
 */
#define NB_JOUEUR_MIN 2
#define NB_JOUEUR_MAX 6


/*
 * PREDECLARATIONS
 */
// enumération du type de pièce dans une case
typedef enum {VIDE, CREUSE, PLEINE, DOUBLE, BLOQUANTE} e_piece;
// DOUBLE = CREUSE + PLEINE


// structure de joueur
typedef struct {
    int points; // nombre de points pour cette partie
    short idJ; // id reconnaissant le joueur
    // il existe 125 id de joueurs. Soit 125 joueurs au max 
    // zéro et les négatifs sont utilisés pour l'absence de joueur
    // MAIS, pour des raisons de couleur, six joueurs maximum.
    // les id vont de 1 (premier joueur) à 6 (dernier)
    int couleur; // valeur de couleur du joueur (de 31 à 36)
    bool IA; // booléen à vrai si ce joueur est géré par l'IA
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
    t_joueur* oya; // pointeur vers l'oya (le joueur dont c'ets le tour)
    short nbJoueur; // nombre de joueurs listés (l'id va de 1 à 6)
} t_jeu;



/*
 * PROTOTYPES
 */
// STRUCT T_CASE (dans struct_case_joueur.c)
    void t_case_init(t_case* t_case, int x, int y); // initialisation de la structure

// STRUCT T_JOUEUR (dans struct_case_joueur.c)
    void t_joueur_init(t_joueur *j, short id, bool ia); // initialise le joueur selon le nombre denjoueur initialisé auparavant

// STRUCT T_JEU (dans struct_jeu.c)
    t_jeu* t_jeu_init(short nbjoueurs, short nbIA); // allocation et initialisation de la structure. Retourne l'adresse de la structure ou NULL
    void t_jeu_free(t_jeu* jeu); // libère le t_jeu alloué dynamiquement
    // Sous-procédures
	bool t_jeu_init_listeJoueur(t_jeu* jeu, short nbIA); // initialise la liste des joueurs du jeu, et renvois faux si un problème à été rencontré, après appel de FLUX_ERREUR()
	bool t_jeu_init_plateau(t_jeu* jeu); // Initialise le plateau de jeu. Renvois faux si problème rencontré, après l'avoir fait savoir avec FLUX_ERREUR()





#endif
