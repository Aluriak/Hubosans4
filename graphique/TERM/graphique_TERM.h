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
- ALPHA, où une case est divisée en deux : une partie creuse, une partie pleine
- BETA, où une case n'est affichée que dans une case, avec le background pour 
    la partie creuse, et un zéro pour la partie pleine
// */

/*
 * PROTOTYPES
 */
    void TERM_clear(); // efface le contenu du terminal
    void TERM_color(int couleur); // configure la couleur de texte terminal
    void TERM_afficherJeu(t_jeu* jeu); // affiche le jeu dans le terminal
    // procédures internes
	void TERM_afficherEnTete(t_jeu* jeu); // Affiche l'en-tête du jeu, contenant instructions, indications, et première partie du plateau de jeu
	void TERM_afficherPlateau(t_jeu* jeu); // Affiche le plateau de jeu
	void TERM_afficherCase(t_jeu* jeu, int i, int j); // affiche la case du jeu aux coordonnées (i;j), avec formatage couleur
    t_action TERM_entreeUtilisateur(t_jeu *jeu); // demande à l'oya du jeu ce qu'il désire jouer, et renvois le résultat sous forme d'une action

#endif
