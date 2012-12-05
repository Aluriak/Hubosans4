#include "main.h"




/*
 * MAIN
 */
// main
int main(int argc, char* argv[]) {
    // pré-initialisation
    main_init();

    // initialisations
    t_jeu *jeu = NULL; // initialisé par l'interface graphique
    t_joueur* gagnant = NULL;
    t_action action;
    bool sdl = false;
    //SDL_Surface* ecran = NULL; // écran de jeu

    // si le premier argument est "-g"
    if(argc > 1 && (strcmp(argv[1],"-g") == 0 || 
		    strcmp(argv[1], "--sdl"))) {
	//sdl = true; // on passe en affichage SDL
	// TODO: initialiser la SDL, créer la SDL_surface
    }

    // Menu principal
    if(sdl) {
	//jeu = SDL_AfficherMenu(ecran);
	//SDL_afficherJeu(&jeu, ecran);
    }
    else {
	jeu = TERM_afficherMenu();
	TERM_afficherJeu(jeu);
    }

    // jeu
    while(gagnant == NULL) {
	if(sdl) {
	    //SDL_afficherJeu(jeu, ecran);
	    //action = SDL_entreeUtilisateur(jeu, ecran);
	}
	else {
	    TERM_afficherJeu(jeu);
	    action = TERM_entreeUtilisateur(jeu);
	}
	gagnant = MOTEUR_tourSuivant(jeu, action);
    }
    // arrivé ici, il y a puissance 4
    /*
    if(sdl)
	//SDL_afficherFinDeJeu(&jeu, ecran);
    else
	//TERM_afficherFinDeJeu(&jeu);
    // */

    // libération du jeu
    t_jeu_free(jeu);
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




