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
    // On crée un bool pour savoir quand l'user demande à quitter le jeu
    bool quit_prgm = false, quit_jeu = false, quit_menu = false; // quitte si vrai



    while(quit_prgm == false) {
        while(quit_menu == false) {
            regleJeu = TERM_afficherMenu();
            // si le jeu n'est pas correctement intialisé
	    if(regleJeu.nbJoueurs==-1) {
                // on arrête tout
		quit_menu = quit_jeu = quit_prgm = true; // arrêt
	    }
	    // Si -2, alors on lance le module de chargement de partie
	    else if(regleJeu.nbJoueurs==-2) {
		TERM_clear(); // nettoyage du TERM
		TERM_afficherHubosans4(); // affichage esthétique
		char * load = TERM_afficherModuleChargement();
		if(load != NULL) {
		    if(strcmp(load, "quit") != 0) {
			// Chargement module de base
			t_regleJeu init_load;
			init_load = MOTEUR_ChargementBase(load);
			// Initialisation du jeu
			t_jeu_init(&jeu, 
			           init_load.nbJoueurs,
				   init_load.nbIA,
				   init_load.tab_nivIA,
				   init_load.nbPieceBloquante,
				   init_load.nbPiecePleine,
				   init_load.nbPieceCreuse,
				   init_load.allow_last);

			// Chargement de la sauvegarde
			MOTEUR_chargement(&jeu, load);
			// libération de load
			free(load);

			// On peut démarrer le jeu !
			quit_menu = true;
			quit_jeu = false;
			gagnant = -1;
		    }
		}
	    }
	    // Sinon si -3, affichage tableau des scores
	    else if(regleJeu.nbJoueurs==-3) {
		// Affichage score
		TERM_afficherScore();
		// Attente de l'utilisateur
		TERM_wait();
	    }
	    else {
                // création du jeu selon les règles demandées
		t_jeu_init(&jeu, regleJeu.nbJoueurs, 
			   regleJeu.nbIA, 
			   regleJeu.tab_nivIA, 
			   regleJeu.nbPieceBloquante, 
			   regleJeu.nbPiecePleine, 
			   regleJeu.nbPieceCreuse,
			   regleJeu.allow_last);
                // on peut démarrer le jeu !
                quit_menu = true;
                quit_jeu = false;
	    }
        }
        // boucle de jeu
        while(quit_jeu == false) {
            // gestion du jeu
	    while(gagnant < 0) {
		TERM_afficherJeu(&jeu);
                // on fait jouer le joueur par l'IA ou l'utilisateur, c'est selon.
		if(jeu.listeJoueur[jeu.oya].IA == true)
                    action = IA_effectuerTour(&jeu);
		else
		    action = TERM_entreeUtilisateur(&jeu);
		// On envoie au moteur les choix entrées par l'utilisateur
		gagnant = MOTEUR_tourSuivant(&jeu, action);
		// Si -3, alors l'user demande de l'aide
		if(gagnant == -3)
		{
			TERM_afficherHelp();
			TERM_wait();
		}
		// Si -2, alors c'est une erreur
		else if(gagnant == -2)
		{
			TERM_afficherErreur();
			TERM_wait();
		}
		// Si -4, alors l'user veut sauvegarder
		else if(gagnant == -4)
		{
			action = TERM_afficherModuleSauvegarde(&jeu);
			MOTEUR_sauvegarde(&jeu, action);
		}
	    }

	    // arrivé ici, il y a puissance 4 ou bien égalité
	    if(gagnant >= 0 && gagnant <= 5)
	    {
		    // On affiche le plateau de jeu gagnant
		    TERM_afficherJeuFinit(&jeu, gagnant);
		    // On attend 5 secondes
		    TERM_wait(5);
		    // On enregistre le score du gagant
		    char * score = TERM_afficherNomScore();
		    MOTEUR_enregistrerScore(&jeu, gagnant, score);
		    gagnant = -1;
	    }
	    else if(gagnant == 43)
	    {
		    TERM_afficherJeuEgalite(&jeu);
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
            // on arrête le jeu
            quit_jeu = true;
            // on démarre le menu
            quit_menu = false;
            // on libère la structure de jeu
	    t_jeu_free(&jeu);
        }
    }


    // END
    return EXIT_SUCCESS;
}



/*
 * MAIN INIT
 */
// gère les pré-initialisations du programme
void main_init() {
    // initialisation du hasard en fonction du temps
    srand(time(NULL));
}




