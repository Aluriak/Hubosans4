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
    void TERM_confColor(char* clr); // configure la couleur de texte terminal
    void TERM_afficherJeu(t_jeu* jeu); // affiche le jeu dans le terminal


#endif
