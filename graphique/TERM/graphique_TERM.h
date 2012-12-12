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

/*
Il existe deux modes d'affichage dans la sortie standard:
- Double, où une case est divisée en deux : une partie creuse, une partie pleine
- Simple, où une case n'est affichée que dans une case, avec le background pour 
    la partie creuse, et un zéro pour la partie pleine
Seul l'affichage Double est disponible pour le moment.
// */

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
    t_jeu* TERM_afficherMenu(); // affiche le menu principal et gère l'entrée utilisateur pour la configuration du jeu, et retourne la structure de jeu en conséquence
    void TERM_afficherJeuFinit(t_jeu* jeu, t_joueur* gagnant); // fait les affichage du jeu lorsqu'il se termine

#endif
