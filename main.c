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
    while(quit == false)
    {	
    	    bool no_game = false;
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
		if(regleJeu.nbJoueurs==-1)
		{
			quit = true;
			break;
		}
		// Si -2, alors on lance le module de chargement de partie
		else if(regleJeu.nbJoueurs==-2)
		{
			char * exit = malloc(20*sizeof(char));
			char save[20];// = malloc(20*sizeof(char));
			exit = "quit";
			TERM_clear();
			TERM_afficherHubosans4();
			save[20] = TERM_afficherModuleChargement();
			if(strcmp(save, exit) == 0)
			{
				no_game = true;
				quit = false;
				gagnant = 42;
			}
			else
			{
				// Traitement
				printf("Module en construction\n");
				wait(2);
				no_game = true;
				gagnant = 42;
				//MOTEUR_chargement();
			}
		}
		else
		{
			t_jeu_init(&jeu, regleJeu.nbJoueurs, 
				   regleJeu.nbIA, 
				   regleJeu.tab_nivIA, 
				   regleJeu.nbPieceBloquante, 
				   regleJeu.nbPiecePleine, 
				   regleJeu.nbPieceCreuse); 
				   allow_last = regleJeu.allow_last;
		}
	    }
	    // jeu
	    while(gagnant < 0) {
		if(sdl) {
		    //SDL_afficherJeu(jeu, ecran);
		    //action = SDL_entreeUtilisateur(jeu, ecran);
		}
		else {
		    TERM_afficherJeu(&jeu, regleJeu);
		    if(jeu.listeJoueur[jeu.oya].IA == true)
			//action = IA_effectuerTour(jeu, oya);
			action = TERM_entreeUtilisateur(&jeu); // TEMPORAIRE
		    else
			action = TERM_entreeUtilisateur(&jeu);
		}
		// On envoie au moteur les choix entrées par l'utilisateur
		gagnant = MOTEUR_tourSuivant(&jeu, action, allow_last);
		// Si -3, alors l'user demande de l'aide
		if(gagnant == -3)
		{
			TERM_afficherHelp();
			wait(10);
		}
		// Si -2, alors c'est une erreur
		else if(gagnant == -2)
		{
			TERM_afficherErreur();
			wait(2);
		}
		// Si -4, alors l'user veut sauvegarder
		else if(gagnant == -4)
		{
			action = TERM_afficherModuleSauvegarde(&jeu, regleJeu);
			gagnant = MOTEUR_tourSuivant(&jeu, action, allow_last);
			gagnant = -1;
		}
	    }
	    // arrivé ici, il y a puissance 4 ou bien égalité
	    
	    if(sdl)
	    {
		//SDL_afficherFinDeJeu(&jeu, ecran);
	    }
	    else
	    {
	    	if(gagnant >= 0 && gagnant <= 5)
		{
			TERM_afficherJeuFinit(&jeu, gagnant, regleJeu);
			wait(5);
		}
		else if(gagnant == 43)
		{
			TERM_afficherJeuEgalite(&jeu, regleJeu);
		}
		/*
		 * Dans tout les autres cas, on considère que l'user veut
		 * retourner au menu
		 */
		else
		{
			// On remet la valeur de gagnant à -1
			gagnant = -1;	
		}
	    }
	    // Si une partie à été lancée
	    if(!no_game)
	    {
	    	 // Alors on free
	    	 t_jeu_free(&jeu);
	    }
      }
    return 0;
    // TODO: libérations et désinitialisations SDL
}



/*
 * MAIN INIT
 */
// gère les pré-initialisations du programme
void main_init() {
    // initialisation du hasard en fonction du temps
    srand(time(NULL));
}




