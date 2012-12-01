#include "main.h"




/*
 * MAIN
 */
// main
int main(int argc, char* argv[]) {
    // pré-initialisation
    main_init();

    // initialisations
    t_joueur* gagnant = NULL;
    t_action action;

    // Menu principal
    t_jeu* jeu = TERM_AfficherMenu();
    TERM_afficherJeu(&jeu);
    // jeu
    while(gagnant == NULL) {
	TERM_afficherJeu(&jeu);
	action = TERM_entreeUtilisateur(&jeu);
	gagnant = MOTEUR_tourSuivant(&jeu, action);
    }
    // arrivé ici, il y a puissance 4

    // libération du jeu
    t_jeu_free(&jeu);
    return EXIT_SUCCESS;
}



/*
 * MAIN INIT
 */
// gère les pré-initialisations du programme
void main_init() {
    // initialisation du hasard en focntion du temps
    srand(time(NULL));
}




