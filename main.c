#include "main.h"




/*
 * MAIN
 */
// main
int main(int argc, char* argv[]) {
    // pré-initialisation
    main_init();

    // initialisations
    // création du jeu
    t_jeu jeu;
    t_jeu_init(&jeu, 4, 3); // 4 joueurs, dont 3 IA


    //* DEBUG
    TERM_afficherJeu(&jeu);
    // DEBUG */
    /* 
    t_joueur* gagnant = NULL;
    t_action action;

    // jeu
    while(gagnant == NULL) {
	TERM_afficherJeu(&jeu);
	action = TERM_entreeUtilisateur(&jeu);
	gagnant = MOTEUR_tourSuivant(&jeu, action);
    }
    // arrivé ici, il y a puissance 4
    // */

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




