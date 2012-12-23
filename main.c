#include "main.h"




/*
 * MAIN
 */
// main
int main(int argc, char* argv[]) {
    // pré-initialisation
    main_init();

    // initialisations
    t_jeu jeu; // initialisé plus bas, après dialogue avec l'interface graphique
    t_regleJeu regleJeu; // valeurs déterminant l'intialisation du jeu
    int gagnant = -1;
    t_action action;
    bool sdl = false;
    // On crée un bool pour savoir quand l'user demande à quitter le jeu
    bool quit = false; // quitte le jeu
    //bool menu = false; // quitte la partie en cours et retourne menu
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
		/*
		regleJeu = SDL_AfficherMenu(ecran);
		t_jeu_init(jeu, regleJeu.nbJoueurs, 
			   regleJeu.nbIA, 
			   regleJeu.tab_nivIA); 
		// */
	    }
	    else {
		regleJeu = TERM_afficherMenu();
		t_jeu_init(&jeu, regleJeu.nbJoueurs, 
			   regleJeu.nbIA, 
			   regleJeu.tab_nivIA, 
			   regleJeu.nbPieceBloquante, 
			   regleJeu.nbPiecePleine, 
			   regleJeu.nbPieceCreuse); 
	    }

	    // jeu
	    while(gagnant < 0) {
		if(sdl) {
		    //SDL_afficherJeu(jeu, ecran);
		    //action = SDL_entreeUtilisateur(jeu, ecran);
		}
		else {
		    TERM_afficherJeu(&jeu);
		    if(jeu.listeJoueur[jeu.oya].IA == true)
			//action = IA_effectuerTour(jeu, oya);
			action = TERM_entreeUtilisateur(&jeu); // TEMPORAIRE
		    else
			action = TERM_entreeUtilisateur(&jeu);
		}
		gagnant = MOTEUR_tourSuivant(&jeu, action);
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
			TERM_afficherJeuFinit(&jeu, gagnant);
		}
		else if(gagnant == 43)
		{
			TERM_afficherJeuEgalite(&jeu);
		}
	    }
    }
    // libération du jeu
    t_jeu_free(&jeu);
    // TODO: libérations et désinitialisations SDL
    return 0;
}



/*
 * MAIN INIT
 */
// gère les pré-initialisations du programme
void main_init() {
    // initialisation du hasard en fonction du temps
    srand(time(NULL));
}




