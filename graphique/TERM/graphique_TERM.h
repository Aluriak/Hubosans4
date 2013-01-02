#ifndef GRAPHIQUE_TERM_H_INCLUDED
#define GRAPHIQUE_TERM_H_INCLUDED

/*
 * BIBLIOTHEQUES
 */
// modules
#include "../../systeme/systeme.h"
#include "../../moteur/moteur.h"


/*
 * PREDECLARATIONS
 */
#define NB_JOUEUR_MAX 6 // limite dûe au nombre de couleurs du terminal

// structure de règle de jeu
// Cette structure contient les valeur sdéterminant un jeu.
// Renvoyé par l'interface graphique pour permettre la création du jeu.   
typedef struct {
    int nbJoueurs;
    int nbIA;
    int tab_nivIA[NB_JOUEUR_MAX];
    int nbPieceBloquante;
    int nbPiecePleine;
    int nbPieceCreuse;
} t_regleJeu;



/*
 * PROTOTYPES
 */
    void TERM_clear(); // efface le contenu du terminal
    void TERM_color(int couleur); // configure la couleur de texte terminal
    void TERM_backgroundColor(int couleur); // configure la couleur de background du terminal
    void TERM_afficherJeu(t_jeu* jeu); // affiche le jeu dans le terminal
    // procédures internes
	void TERM_afficherEnTete(t_jeu* jeu); // Affiche l'en-tête du jeu, contenant instructions, indications, et première partie du plateau de jeu
	void TERM_afficherPlateau(t_jeu* jeu); // Affiche le plateau de jeu
	void TERM_afficherCase(t_jeu* jeu, int i, int j); // affiche la case du jeu aux coordonnées (i;j), avec formatage couleur
    t_action TERM_entreeUtilisateur(t_jeu *jeu); // demande à l'oya du jeu ce qu'il désire jouer, et renvois le résultat sous forme d'une action
    t_regleJeu TERM_afficherMenu(); // affiche le menu principal et gère l'entrée utilisateur pour la configuration du jeu, et retourne la structure de jeu en conséquence
    void TERM_afficherJeuFinit(t_jeu* jeu, int gagnant); // fait les affichage du jeu lorsqu'il se termine
    void TERM_afficherHelp(); // Affiche le menu
    void TERM_afficherJeuEgalite(t_jeu * jeu); // Affiche la fin de jeu en cas de plateau plein && pas puissance4
    void TERM_afficherErreur(); // Indique à l'user que le chois entrées est impossible
    void TERM_afficherHubosans4(); // Affiche HUBOSANS4 en ascii





#endif
