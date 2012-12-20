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
    int gagnant = -1;
    //t_joueur* gagnant = NULL;
    t_action action;
    bool sdl = false;
    // On crée un bool pour savoir quand l'user demande à quitter le jeu
    bool quit = false; // quitte le jeu
    bool menu = false; // quitte la partie en cours et retourne menu
    //SDL_Surface* ecran = NULL; // écran de jeu

    // si le premier argument est "-g" ou "--gui"
    if(argc > 1 && (strcmp(argv[1],"-g") == 0 || 
		    strcmp(argv[1], "--sdl"))) {
	//sdl = true; // on passe en affichage SDL
	// TODO: initialiser la SDL, créer la SDL_surface
    }
    while(!quit)
    {
	    // Menu principal
	    if(sdl) {
		//jeu = SDL_AfficherMenu(ecran);
		//SDL_afficherJeu(&jeu, ecran);
	    }
	    else {
		jeu = TERM_afficherMenu();
	    }

	    // jeu
	    while(gagnant < 0) {
		if(sdl) {
		    //SDL_afficherJeu(jeu, ecran);
		    //action = SDL_entreeUtilisateur(jeu, ecran);
		}
		else {
		    TERM_afficherJeu(jeu);
		    if(jeu->listeJoueur[jeu->oya].IA == true)
			//action = IA_effectuerTour(jeu, oya);
			action = TERM_entreeUtilisateur(jeu); // TEMPORAIRE
		    else
			action = TERM_entreeUtilisateur(jeu);
		}
		gagnant = MOTEUR_tourSuivant(jeu, action);
	    }
	    // arrivé ici, il y a puissance 4
	    
	    if(sdl)
	    {
		//SDL_afficherFinDeJeu(&jeu, ecran);
	    }
	    else
	    {
	    	if(gagnant >= 0 && gagnant <= 5)
		{
			TERM_afficherJeuFinit(jeu, gagnant);
		}
	    }
    }
	    // */

    // libération du jeu
    t_jeu_free(jeu);
    // TODO: libérations et désinitialisations SDL
    return 0;
}



/*
 * MAIN INIT
 */
// gère les pré-initialisations du programme
void main_init() {
    // initialisation du hasard en focntion du temps
    srand(time(NULL));
}




