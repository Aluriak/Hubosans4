#ifndef GRAPHIQUE_TERM_H_INCLUDED
#define GRAPHIQUE_TERM_H_INCLUDED

/*
 * BIBLIOTHEQUES
 */
#include <stdio.h>
#include <stdlib.h>
// modules
#include "../../systeme/systeme.h"
#include "../../moteur/moteur.h"

/*
 * PREDECLARATIONS
 */



/*
 * PROTOTYPES
 */
    void TERM_clear(); // efface le contenu du terminal
    void TERM_color(int couleur); // configure la couleur de texte terminal
    void TERM_afficherJeu(t_jeu* jeu); // affiche le jeu dans le terminal
    // procédures internes
	void TERM_afficherEnTete(t_jeu* jeu); // Affiche l'en-tête du jeu, contenant instructions, indications, et première partie du plateau de jeu
	void TERM_afficherCase(t_jeu* jeu, int i, int j); // affiche la case du jeu aux coordonnées (i;j), avec formatage couleur

#endif
