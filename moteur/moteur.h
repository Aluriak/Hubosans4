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
    int idJ; // id reconnaissant le joueur
    int nbPieceBloquante; // nb de pièces bloquantes possédées par le joueur
    // il existe 125 id de joueurs. Soit 125 joueurs au max 
    // zéro et les négatifs sont utilisés pour l'absence de joueur
    // MAIS, pour des raisons de couleur, six joueurs maximum.
    // les id vont de 1 (premier joueur) à 6 (dernier)
    int couleur; // valeur de couleur du joueur (de 31 à 36)
    bool IA; // vrai si IA, faux si humain
    int intrepidite; // intrépidité du joueur lorsque jouée par l'IA. 
    // Chiffre oscillant entre 0 et 10, avec 10 intrépidité maximum 
    // 	(pièces bloquantes utilisées dés que possible) et 0 
    // 		(pièces bloquantes utilisées rarement)
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
    int oya; // id du joueur étant l'oya
    short nbJoueur; // nombre de joueurs listés (l'id va de 1 à 6)
    int niveauIA; // niveau des IA (entre 1(facile) et 3 (difficile))
} t_jeu;


// structure d'action. Contient une action de jeu : une colonne où la pièce 
// 	est tombée, et le type de la pièce.
typedef struct {
    int colonne; // colonne où la pièce à été lâchée
    e_piece typePiece; // type de pièce
} t_action;



/*
 * PROTOTYPES
 */
// MOTEUR
    t_joueur* MOTEUR_tourSuivant(t_jeu* jeu, t_action action); // effectue le tour suivant du jeu, et renvois l'adresse du joueur ayant fait un puissance 4 ce tour ou NULL.
    int MOTEUR_coordPieceJouee(t_jeu* jeu, e_piece piece, int colonne); // renvois la coordonnee y d'une pièce placée dans la colonne. Ou -1 si pièce impossible à mettre (atteinte le limite haute)

// STRUCT T_CASE (dans struct_case_joueur.c)
    void t_case_init(t_case* t_case, int x, int y); // initialisation de la structure

// STRUCT T_JOUEUR (dans struct_case_joueur.c)
    void t_joueur_init(t_joueur *j, int nbPieceBloquante, int id, bool ia); // initialise le joueur

// STRUCT T_JEU (dans struct_jeu.c)
    void t_jeu_init(t_jeu* jeu, short nbjoueurs, int nbIA, int niveauIA); // allocation et initialisation de la structure. Le pointeur est NULL en cas d'erreur
    void t_jeu_free(t_jeu* jeu); // libère le t_jeu alloué dynamiquement
    // Sous-procédures
	bool t_jeu_init_listeJoueur(t_jeu* jeu, int nbIA); // initialise la liste des joueurs du jeu, et renvois faux si un problème à été rencontré, après appel de FLUX_ERREUR()
	bool t_jeu_init_plateau(t_jeu* jeu); // Initialise le plateau de jeu. Renvois faux si problème rencontré, après l'avoir fait savoir avec FLUX_ERREUR()
	void t_jeu_choisirOya(t_jeu* jeu); // choisit un oya, et le point avec le pointeur attribut de t_jeu prévu à cet effet
	void t_jeu_joueurSUivant(t_jeu* jeu); // modifie l'oya pour que le joueur suivant le devienne





#endif
