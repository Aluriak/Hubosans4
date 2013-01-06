#include "graphique_TERM.h"


/*
 * TERM CLEAR
 */
// efface le contenu du terminal
void TERM_clear() {
    // directive comprise comme effaçage de l'écran
    printf("\033[H\033[2J");
}



/*
 * TERM COLOR
 */
// configure la couleur de texte terminal
// 	Envoyer 0 pour réinitialiser
void TERM_color(int couleur) {
    printf("\033[%dm", couleur);
}




/*
 * TERM BACKGROUND COLOR
 */
// configure la couleur de background du terminal
// 	Envoyer 0 pour réinitialiser
void TERM_backgroundColor(int couleur) {
    printf("\033[%dm", couleur+10);
}




/*
 * TERM AFFICHER JEU
 */
// affiche le jeu dans le terminal
void TERM_afficherJeu(t_jeu* jeu) {
    // on efface l'écran
    /*TERM_clear();*/
    /*// Nom jeu*/
    /*TERM_afficherHubosans4(); */
    /*// Commande*/
    /*TERM_afficherCommande(jeu);*/
    // EN-TETE
    TERM_afficherEnTete(jeu);
    // PLATEAU
    TERM_afficherPlateau(jeu);
    /*
    printf("id = (%d;%d), type = %d", 
            jeu->plateau[3][jeu->nbCaseY-1].joueurPieceCreuse,
            jeu->plateau[3][jeu->nbCaseY-1].joueurPiecePleine,
            jeu->plateau[3][jeu->nbCaseY-1].typePiece
            );
    // */
}



/*
 * TERM AFFICHER EN TETE
 */
// Affiche l'en-tête du jeu, contenant instructions et indications
void TERM_afficherEnTete(t_jeu* jeu) {
    int i = 0; // itérateur de boucle
    // pour chaque joueur
    for(i = 0; i < jeu->nbJoueur; i++) {
	TERM_color(jeu->listeJoueur[i].idJ+31);
	printf("%s : %i points - pieces : %i B - %i P - %i C", 
		jeu->listeJoueur[i].nom, 
		jeu->listeJoueur[i].points,
		jeu->listeJoueur[i].nbPieceBloquante,
		jeu->listeJoueur[i].nbPiecePleine,
		jeu->listeJoueur[i].nbPieceCreuse
		);
	// si c'est une IA
	if(jeu->listeJoueur[i].IA) 
	    printf("\t[IA]");
	else 
	    printf("\t[HM]");
	// si c'est le joueur dont c'est le tour
	if(jeu->oya == i)
	    printf("\t[Oya]");
	printf("\n");
    }
    TERM_color(0);
    printf("\n");
}




/*
 * TERM AFFICHER PLATEAU
 */
// Affiche le plateau de jeu
void TERM_afficherPlateau(t_jeu* jeu) {
    int i = 0, j = 0; // itérateur de boucle
    // Début du plateau de jeu
    printf(" ");
    for(i = 0; i < jeu->nbCaseX; i++) {
	// on gère les cas à 5 ou 6 joueurs : il faut afficher correctement 
	// 	la 10ème et 11ème colonne
	if(i+1 < 10)
	    printf("%d ", i+1);
	else
	    printf("%d", i+1);
    }
    printf("\n");
    // Corps du plateau (cases et séparateurs)
    // pour chaque ligne
    for(j = 0; j < jeu->nbCaseY; j++) {
	printf("|");
	// pour chaque colonne de la ligne j
	for(i = 0; i < jeu->nbCaseX; i++) {
	    TERM_afficherCase(jeu, i, j);
            printf("|");
	}
	printf("\n");
    }
    // Pied du plateau (ligne d'étoile)
    printf(" ");
    for(i = 0; i < jeu->nbCaseX*2-1; i++) 
	printf("*");
    printf("\n");
}




/*
 * TERM AFFICHER CASE
 */
// affiche la case du jeu aux coordonnées (i;j), avec formatage couleur
void TERM_afficherCase(t_jeu* jeu, int i, int j) {
    // initialisations
    int val1, val2;
    e_piece typePiece;
    // récupération des idJoueurs pour avoir leur couleur, et du type de pièce
    val1 = jeu->plateau[i][j].joueurPieceCreuse;
    val2 = jeu->plateau[i][j].joueurPiecePleine;
    typePiece = jeu->plateau[i][j].typePiece; // type de la pièce
    // affichage des pièces
    if(typePiece == BLOQUANTE) {
	TERM_backgroundColor(val1+31); // couleur de fond du joueur
	printf("X"); // on affiche la pièce bloquante avec un X blanc
    }
    else if(typePiece == DOUBLE) {
	// Une pièce double est symbolisée par un D
	// le fond est la pièce creuse, le D la pièce pleine
	// le D est blanc si le même joueur possède les deux pièces
	if(val1 == val2) 
	    TERM_color(0); // D blanc
	else
	    TERM_color(val1+31); // D coloré
	TERM_backgroundColor(val2+31); // couleur de fond du joueur
	printf("D");
    }
    else if(typePiece == PLEINE) {
	// un zéro sur fond noir
	TERM_color(val2+31); // texte coloré selon couleur du joueur
	printf("0");
    }
    else if(typePiece == CREUSE) {
	// juste le fond de la case en couleur du joueur
	TERM_backgroundColor(val1+31);
	printf(" ");
    }
    else { // on affiche juste un espace
        printf(" "); // on affiche la pîèce pleine
    }
    // réinitialisation des couleurs
    TERM_backgroundColor(0); // couleur de fond normal
    TERM_color(0); // texte normal
}








/*
 * TERM ENTREE UTILISATEUR
 */
// demande à l'oya du jeu ce qu'il désire jouer, et renvois le résultat sous 
// 	forme d'une action
t_action TERM_entreeUtilisateur(t_jeu *jeu) {
    t_action action;
    action.colonne=-1;
    action.typePiece=VIDE;
    char entreeUser[INSECURE_N_MAX]; // inSecure revoit un tableau de INSECURE_N_MAX cases
    char pieceUser; // pièce de l'utilisateur
    while((action.colonne<0 || action.colonne >= jeu-> nbCaseX) &&
	  (action.typePiece != BLOQUANTE ||
	   action.typePiece != CREUSE ||
	   action.typePiece != PLEINE))
    {
	printf(">> Entrez Coordonnées & Type de piece : ");
        // inSecure gère tout : il renvois le 1er chiffre et la 1ère chaine de lettres
        inSecure(&action.colonne, entreeUser);
        // la pièce de l'utilisateur est la première lettre qu'il envois
        pieceUser = entreeUser[0];

	if(tolower(pieceUser) == 'b')
	{
	       action.typePiece = BLOQUANTE;
	}
	else if (tolower(pieceUser) == 'c')
	{
	   	action.typePiece = CREUSE;
	}
	else if(tolower(pieceUser) == 'p')
	{
	       action.typePiece = PLEINE;
	}
	else
	{
		return action;
	}
	// l'utilisateur voit les numéros de colonne +1, donc :
	action.colonne--; // tableau commence à zéro
    }   
    return action;
}







/*
 * TERM AFFICHER MENU
 */
// affiche le menu principal et gère l'entrée utilisateur pour la configuration du jeu, et retourne la structure de jeu en conséquence
// Les règles envoyées dont des règles correct si l'user à demander à créer un jue
// si nbJoueurs == -1, alors l'user demande à quitter
// nbIA correspond au slot à charger
//
t_regleJeu TERM_afficherMenu() {
    int choice = 0; // Contient le choix de l'user
    int niveauIA = 4; // niveau des IA
    int i = 0; // itérateur de boucle
    t_regleJeu regleJeu = {-1,-1};
    // Menu
    TERM_clear();
    TERM_afficherHubosans4();
    // Choix principaux
    printf("Bienvenue Joueur !\n\n");
    printf("\t 1. Nouvelle Partie\n");
    printf("\t 2. Charger Partie\n");
    printf("\t 3. Tableau des Scores\n");
    printf("\t 4. Quitter\n\n");
    do
    {
    	printf(">> Que voulez-vous faire ? ");
    	choice = inSecure_int();
    } while(choice != 1 &&
            choice != 2 &&
	    choice != 3 &&
	    choice != 4);

    // On attend le choix de l'user
    switch(choice)
    {
	case 1:
	    // nombre de joueurs
	    while(regleJeu.nbJoueurs < 2 || regleJeu.nbJoueurs > 6) {
		printf(">> Nombre de joueurs total (2 à 6) : ");
		regleJeu.nbJoueurs = inSecure_int();
	    }
	    // nombre d'IA
	    while(regleJeu.nbIA < 0 || regleJeu.nbIA > regleJeu.nbJoueurs) {
		printf(">> Nombre d'ia parmis les %i joueurs (max %i) : ", 
			regleJeu.nbJoueurs, regleJeu.nbJoueurs);
		regleJeu.nbIA = inSecure_int();
	    }
	    // autoriser annuler dernier coup
	    int tmp;
            char entreeUser[INSECURE_N_MAX];
	    while(entreeUser[0] != 'y' && entreeUser[0] != 'n')
	    {
	        printf(">> Autoriser annuler dernier coup ? [y - n] ");
		inSecure(&tmp, entreeUser);
	    }
	    if(entreeUser[0] == 'y')
	    {
	    	regleJeu.allow_last = true;
	    }
	    else
	    {
	    	regleJeu.allow_last = false;
	    }
	    // niveau des IA (entre 1 et 4)
	    if(regleJeu.nbIA > 0) {
		printf("Niveau des IA :\n\n");
		printf("\t 1.Facile\n");
		printf("\t 2.Moyen\n");
		printf("\t 3.Difficile\n");
		printf("\t 4.Très difficle\n\n");
		printf(">> Votre choix : ");
		for(i = 0; i < regleJeu.nbIA; i++) {
		    // tant qu'on a pas un niveau valide
		    do {
			printf(">> Niveau de l'IA %d : ", i+1);
		        niveauIA = inSecure_int();
		    } while(niveauIA < 0 || niveauIA > 4);
		    // on donne le niveau au joueur étudié
		    regleJeu.tab_nivIA[i] = niveauIA;
		}
	    }
	    // nombre de pièces
	    regleJeu.nbPieceBloquante = regleJeu.nbJoueurs;
	    regleJeu.nbPiecePleine = regleJeu.nbJoueurs*20;
	    regleJeu.nbPieceCreuse = regleJeu.nbJoueurs*20;
	    // On retourne les regles du jeu
	    return regleJeu;
	case 2:
		// On met le nombre de joueurs à -2
		regleJeu.nbJoueurs=-2;
		// On retourne les règles du jeu
		return regleJeu;
	case 3:
		printf("Not avaible now, sorry.\n");
	case 4:
		printf("Bye-Bye !\n");
		// On met le nombre de joueur à -1
		regleJeu.nbJoueurs=-1;
		// On retourne les règle du jeu
		return regleJeu;
    }
    return regleJeu;
}






/*
 * TERM AFFICHER JEU FINIT
 */
// fait les affichage du jeu lorsqu'il se termine
void TERM_afficherJeuFinit(t_jeu* jeu, int gagnant) {
    TERM_afficherJeu(jeu);
    // on affiche le nom du joueur d'id envoyé en argument comme gagnant de la partie
    printf("Le joueur %s remporte la partie !\n", jeu->listeJoueur[gagnant].nom); 
}
/*
 * TERM AFFICHER JEU EGALITE
 */
// Affiche la fin de jeu en cas de plateau plein && pas puissance4
void TERM_afficherJeuEgalite(t_jeu * jeu)
{
	TERM_clear();
	TERM_afficherJeu(jeu);
	printf("Il y a égalité, aucune autre possibilité de jeu (plateau plein)\n");

}


/*
 * TERM AFFICHER HELP
 */
// Affiche le menu d'aide
void TERM_afficherHelp()
{
	// On commence par nettoyer l'écran ... 
	// pchit pchit ....
	// .... ouais enfin le vider quoi =)
	TERM_clear();
	// Puis on affiche notre beau menu tout plein 
	printf("\t==HELP MENU==\n\n");
	printf("Bienvenue dans le menu d'aide du Puissance 4 !\n\n");
	printf("\t##Commandes HORS JEU##\n");
	printf("\t\t Taper 1 pour SAUVEGARDER\n");
	printf("\t\t Taper 2 pour ANNULER LE DERNIER COUP\n");
	printf("\t\t Taper 3 pour afficher HELP\n");
	printf("\t\t Taper 4 pour QUITTER\n\n");
	printf("\t##Commandes JEU##\n");
	printf("\t\t Entrez d'abord le numéro de la colonne, puis le type de pièce\n");
	printf("\t\t >>> INDEX TYPES PIECES <<<\n");
	printf("\t\t\t b : BLOQUANTE\n");
	printf("\t\t\t c : CREUSE\n");
	printf("\t\t\t p : PLEINE\n\n");
	printf("\t\t Exemple : 3c placera une pièce CREUSE dans la 3ème colonne\n\n");
	printf("OK ? So let's play !\n");
}



/*
 * TERM AFFICHER ERREUR 
 */
// Indique à l'user que le chois entrées est impossible
void TERM_afficherErreur()
{
	printf("Erreur : Entrées inconnue ou impossible\n");
}

/*
 * TERM AFFICHER COMMANDE
 */
// Affiche les commandes durant le jeu
void TERM_afficherCommande(t_jeu* jeu)
{
	if(!jeu->allow_last)
	{
		printf("\tIn game CMD : ");
		printf("1. SAVE - 2. UNDO [NO] - 3. HELP - 4. QUIT\n\n");
	}
	else
	{
		printf("\tIn game CMD : ");
		printf("1. SAVE - 2. UNDO [YES] - 3. HELP - 4. QUIT\n\n");
	}
}


/*
 * TERM AFFICHER HUBOSANS4
 */
// Affiche HUBOSANS4 en ascii
void TERM_afficherHubosans4()
{
    printf("                      ___ ___  ____ _____________ ________    _________   _____    _______    _________   _____                   \n"); 
    printf("    ______   ______  /   |   \\|    |   \\______    \\_____  \\  /   _____/  /  _  \\   \\      \\  /   _____/  /  |  |   ______   ______\n"); 
    printf("   /_____/  /_____/ /    ~    \\    |   /|    |  _/ /   |   \\ \\_____  \\  /  /_\\  \\  /   |   \\ \\_____  \\  /   |  |_ /_____/  /_____/ \n");
    printf("   /_____/  /_____/ \\    Y    /    |  / |    |   \\/    |    \\/        \\/    |    \\/    |    \\/        \\/    ^   / /_____/  /_____/ \n");
    printf("                     \\___|_  /|______/  |______  /\\_______  /_______  /\\____|__  /\\____|__  /_______  /\\____   |                   \n");
    printf("                           \\/                  \\/         \\/        \\/         \\/         \\/        \\/      |__|                   \n");
    printf("\n");
}


/*
 * TERM AFFICHER MODULE SAUVEGARDE
 */
// Affiche la demande de slot à l'user
t_action TERM_afficherModuleSauvegarde(t_jeu * jeu)
{
	t_action action;
	TERM_afficherJeu(jeu);
	printf(">> Entrez le numéro du slot : ");
	scanf("%i", &action.colonne);
	// On modifie la valeur de action.colonne pour le moteur
	action.colonne = action.colonne - (2*action.colonne); // On passe la valeur du slot en négatif afin de ne pas retourner un gagnant éronné (en effet, si une valeur est positive, elle a pour conséquence de quitter la partie en cours)
	return action;
}

/*
 * TERM AFFICHER SCORE
 */
// Affiche le tableau des scores
void TERM_afficherScore()
{
	// TODO	
}


/*
 * TERM AFFICHER MODULE CHARGEMENT
 */
// Affiche le module de chargement
char * TERM_afficherModuleChargement()
{
	char * save = malloc(20*sizeof(char));
	char * quit = malloc(20*sizeof(char));
	quit = "quit";
	printf("Chargement des sauvegardes :\n\n");
	// Création pointeur pour le répertoire
	DIR * rep;
	// Création var --> SLOT = numéro du slot
	int slot = 1;
	bool find = false; // Indique si le fichier existe
	// Ouverture du répetoire des sauvegarde
	rep = opendir("save/");
	struct dirent * lecture;
	// On lit tout les fichiers & on les affiches
	while((lecture = readdir(rep)))
	{
		printf("slot[%i] : %s\n", slot, lecture->d_name);
		slot ++;
	}
	printf("\n");
	printf(">> Entrez le nom de la sauvegarde [quit] : ");
	scanf("%s", save);
	// si save == quit, alors l'user veut quitter
	if(strcmp(save, quit) == 0)
	{
		return quit;
	}
	else
	{
		int res; // Contient resultat de comparaison de string
		// Tant que pas tout lister
		DIR * test = opendir("save/");
		struct dirent * lect;
		while((lect = readdir(test)))
		{
			res = strcmp(save, lect->d_name);
			// Si lecture->d_name == save
			if(res == 0)
			{
				find = true;
				// On retourne la sauvegarde
				fprintf(stderr, "load, name : %s\n", save);
				return save;
			}
		}
	}
	if(find == false)
	{
		printf("Erreur : sauvegarde corrompue ou inexistante\n");
		wait(2);
		return quit;
	}
	return EXIT_SUCCESS;
}
