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
typedef enum {VIDE=0, CREUSE=1, PLEINE=2, BLOQUANTE=3, DOUBLE} e_piece;
// DOUBLE = CREUSE + PLEINE


// structure d'action. Contient une action de jeu : une colonne où la pièce 
// 	est tombée, et le type de la pièce.
typedef struct {
    int colonne; // colonne où la pièce à été lâchée
    e_piece typePiece; // type de pièce
} t_action;

// structure d'élément de pile d'action
struct t_pile_elem_ {
    t_action action; // action 
    struct t_pile_elem_* nxt; // élément suivant, ou NULL
};
typedef struct t_pile_elem_ t_pile_elem;

// structure de pile d'action
typedef struct {
    t_pile_elem* sommet; // première valeur
    int nbElem; // nombre d'éléments dans la pile
} t_pileAction;



// structure de joueur
typedef struct {
    int points; // nombre de points pour cette partie
    int idJ; // id du joueur, entre 0 et 5, et indiquant sa place dans la liste
    int nbPieceBloquante; // nb de pièces bloquantes possédées par le joueur
    int nbPiecePleine; // nb de pièces pleines possédées par le joueur
    int nbPieceCreuse; // nb de pièces creuses possédées par le joueur
    // il existe 125 id de joueurs. Soit 125 joueurs au max 
    // zéro et les négatifs sont utilisés pour l'absence de joueur
    // MAIS, pour des raisons de couleur, six joueurs maximum.
    // les id vont de 1 (premier joueur) à 6 (dernier)
    bool IA; // vrai si IA, faux si humain
    int niveauIA; // niveau de l'IA (entre 1 (facile) et 4(difficile))
    int intrepidite; // intrépidité du joueur lorsque jouée par l'IA. 
    // Chiffre oscillant entre 0 et 10, avec 10 intrépidité maximum 
    // 	(pièces bloquantes utilisées dés que possible) et 0 
    // 		(pièces bloquantes utilisées rarement)
    char* nom; // nom du joueur
} t_joueur;


// Coordonnées entières
typedef struct {
    int x;
    int y;
} coord;


// Case du plateau de jeu
typedef struct {
    coord crd; // coordonnées de la case dans le jeu
    int joueurPieceCreuse; // joueur contrôlant la pièce creuse, ou -1
    int joueurPiecePleine; // joueur contrôlant la pièce pleine, ou -1
    e_piece typePiece; // pièce(s) présente(nt) dans la case
} t_case;


// structure de jeu
typedef struct {
    t_case** plateau; // matrice de t_case
    int nbCaseX; // nombre de cases en X
    int nbCaseY; // nombre de cases en Y
    t_joueur* listeJoueur; // liste des joueurs
    int oya; // id du joueur étant l'oya
    int nbJoueur; // nombre de joueurs listés (l'id va de 1 à 6)
    int nbIA; // nombre de joueurs joués par l'IA
    t_pileAction pileAction; // pile des actions du jeu
    int nbPieceBloquante; // nb de pièces bloquantes possédées au début
    int nbPiecePleine; // nb de pièces pleines possédées au début
    int nbPieceCreuse; // nb de pièces creuses possédées au début
} t_jeu;





/*
 * PROTOTYPES
 */
// MOTEUR
    int MOTEUR_tourSuivant(t_jeu* jeu, t_action action); // effectue le tour suivant du jeu, et renvois l'adresse du joueur ayant fait un puissance 4 ce tour ou NULL.

    bool MOTEUR_pieceJouee(t_jeu * jeu, t_action action, int ligne, bool next); //Reçois en paramètre le une action, une ligne & modifie le plateau de jeu ainsi que le joueur en question, et retourne 1 pour indiquer que la pièce à bien été placée, 0 sino

    bool MOTEUR_tourPrecedent(t_jeu* jeu); // retire l'action précédente du jeu, retourne vrai. Si pas de denrière action, retourne faux.

    int MOTEUR_coordPieceJouee(t_jeu* jeu, e_piece piece, int colonne); // renvois la coordonnee y d'une pièce placée dans la colonne. Ou -1 si pièce impossible à mettre (atteinte le limite haute)

    int * MOTEUR_borne_MAX(t_jeu* jeu, coord coordCase); //Détermine pour une case reçu en paramètre, la valeur MAX (3) ou minimum de celle-ci, représentant ainsi la  distance la séparant des bordures de la matrice

    int MOTEUR_test_c_p4(t_jeu* jeu, int i, int j, int idJ, int c_p4); // Effectue les différents test et retourne la nouvelle valeur de c_p4

    int MOTEUR_test_puissance4(t_jeu* jeu, coord coordCase, int idJ); // renvois le nombre de piece à la suite appartenant au même joueur

    int MOTEUR_test_cond_puissance4(t_jeu * jeu, int c_p4, bool next); // test si il y a puissance 4

    int MOTEUR_sauvegarde(t_jeu * jeu, t_action action); // Sauvegarde la partie en cours


// STRUCT T_CASE (dans struct_case_joueur.c)
    void t_case_init(t_case* t_case, int x, int y); // initialisation de la structure



// STRUCT T_JOUEUR (dans struct_case_joueur.c)
    void t_joueur_init(t_joueur *j, int nbPieceBloquante, int nbPiecePleine, int nbPieceCreuse, bool ia, char* nom, int nivIA); // initialise le joueur
    void t_joueur_free(t_joueur *j); // libère le joueur



// STRUCT T_JEU (dans struct_jeu.c)
    void t_jeu_init(t_jeu* jeu, int nbjoueurs, int nbIA, int *tab_nivIA, int nbPieceBloquante, int nbPiecePleine, int nbPieceCreuse); // allocation et initialisation de la structure. Le pointeur est NULL en cas d'erreur
    void t_jeu_free(t_jeu* jeu); // libère le t_jeu alloué dynamiquement
    
    // SOUS-PROCÉDURES
	bool t_jeu_init_listeJoueur(t_jeu* jeu, int nbIA, int tab_nivIA[]); // initialise la liste des joueurs du jeu, et renvois faux si un problème à été rencontré, après appel de FLUX_ERREUR()
	bool t_jeu_init_plateau(t_jeu* jeu); // Initialise le plateau de jeu. Renvois faux si problème rencontré, après l'avoir fait savoir avec FLUX_ERREUR()
	void t_jeu_choisirOya(t_jeu* jeu); // choisit un oya, et le point avec le pointeur attribut de t_jeu prévu à cet effet
	void t_jeu_joueurSuivant(t_jeu* jeu); // modifie l'oya pour que le joueur suivant le devienne
        bool t_jeu_oyaPossedePiece(t_jeu*, e_piece); // retourne vrai si l'oya possède une pièce du type demandé
        t_jeu* t_jeu_copie(t_jeu*); // renvoit une copie du jeu


// T_PILEACTION (pileAction.c)
    void t_pileAction_init(t_pileAction* p); // Initialise la pile aux bonnes valeurs de départ
    void t_pileAction_free(t_pileAction* p); // libère la pile
    void t_pileAction_emp(t_pileAction *p, t_action action); // empile l'action demandée
    t_action t_pileAction_dep(t_pileAction *p); // Retourne l'action du sommet de la pile, qui est dépilée. action nulle si pile vide
    t_action t_pileAction_val(t_pileAction *p); // retourne l'action du sommet de la pile, sans y toucher
    void t_pileAction_vider(t_pileAction* p); // Vide la pile



#endif
