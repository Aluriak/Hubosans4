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
    bool sdl = false;
    SDL_Surface* ecran = NULL; // écran de jeu

    // si le premier argument est "-g"
    if(argc > 1 && argv[1] == "-g") {
	//sdl = true; // on passe en affichage SDL
	// TODO: initialiser la SDL, créer la SDL_surface
    }

    // Menu principal
    if(sdl) {
	//t_jeu* jeu = SDL_AfficherMenu(ecran);
	//SDL_afficherJeu(&jeu, ecran);
    }
    else {
	t_jeu* jeu = TERM_AfficherMenu();
	TERM_afficherJeu(&jeu);
    }

    // jeu
    while(gagnant == NULL) {
	if(sdl) {
	    //SDL_afficherJeu(&jeu, ecran);
	    //action = SDL_entreeUtilisateur(&jeu, ecran);
	}
	else {
	    TERM_afficherJeu(&jeu);
	    action = TERM_entreeUtilisateur(&jeu);
	}
	gagnant = MOTEUR_tourSuivant(&jeu, action);
    }
    // arrivé ici, il y a puissance 4
=======
    if(sdl)
	//SDL_afficherFinDeJeu(&jeu, ecran);
    else
	//TERM_afficherFinDeJeu(&jeu);

    // libération du jeu
    t_jeu_free(&jeu);
    // TODO: libérations et désinitialisations SDL
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




