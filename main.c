#include "main.h"




/*
 * MAIN
 */
// main
int main(int argc, char* argv[]) {
    //*	DEBUG
    t_jeu *jeu = t_jeu_init(2, 1); // 2 joueurs, dont 1 IA
    if(jeu == NULL) return false;
    TERM_afficherJeu(jeu);

    // libération du jeu
    free(jeu);
    //	DEBUG 	*/
    return EXIT_SUCCESS;
}




