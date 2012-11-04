#include "main.h"




/*
 * MAIN
 */
// main
int main(int argc, char* argv[]) {
    // pré-initialisation
    main_init();
    //*	DEBUG
    t_jeu *jeu = t_jeu_init(2, 1); // 2 joueurs, dont 1 IA
    if(jeu == NULL) return false;
    TERM_afficherJeu(jeu);
    // libération du jeu
    free(jeu);
    //	DEBUG 	*/
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



/*
 * RAND N
 */
// renvois un nombre aléatoire entre 0 et N-1 (N > 0)
int randN(int N) {
    return (int) (rand() / (double)RAND_MAX * (N-1));
}



