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
    t_jeu *jeu = t_jeu_init(4, 3); // 4 joueurs, dont 3 IA
    if(jeu == NULL) return EXIT_SUCCESS;
    //t_joueur* gagnant = NULL;

    // premier affichage
    TERM_afficherJeu(jeu);

    // jeu
    /*
    while(gagnant == NULL) {
	TERM_afficherJeu(jeu);
	gagnant = t_jeu_tourSuivant(jeu);
    }
    // arrivé ici, il y a puissance 4
    // */

    // libération du jeu
    t_jeu_free(jeu);
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




