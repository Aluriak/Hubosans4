#include "moteur.h"


/*
 * T_JEU TOUR SUIVANT
 */
// effectue le tour suivant du jeu, et renvois l'adresse du joueur 
// 	ayant fait un puissance 4 ce tour ou NULL.
//Les étapes de calculs sont les suivantes :
//	- On identifie le couple (colonne,pion) renvoyé par action
//	- On modifie jeu en fonction d'action
//		- En testant si aucun conflit n'est présent
//		- En vérifiant si !puissance4
int MOTEUR_tourSuivant(t_jeu* jeu, t_action action) 
{
    /*
     * Pour le moteur, si action.typePiece == VIDE, cela signifie que le joueur
     * a voulu effectuer une commande. On regarde donc action.colonne, qui 
     * sera considéré comme la commande voulu :
     * 
     * 1. DEMANDE DE SAVE
     * 2. LAST
     * 3. HELP
     * 4. EXIT
     * 5. CHARGEMENT
     * <0.MODULE DE SAUVEGARDE 
     *
     * Si différent, erreur et on recommence la demande, sans changer de joueur
     *
     * INDEX DES RETOURS
     *
     * return -1 : La partie n'est pas terminée et continue normalement
     * return -2 : Erreur, l'action n'est pas valide
     * return -3 : On affiche l'aide des commandes
     * return -4 : Le moteur appel graphique pour demande de slot de save
     * return 42 : On quitte la partie en cours && retour au menu principal
     * return 43 : Le plateau de jeu est plein, on retourne égalité
     */
    if(action.typePiece == VIDE) // action.colonne == VIDE, donc on passe en mode commande
    {
    	// Si 1, alors c'est une demande de sauvegarde
    	if(action.colonne == 1)
	{
    		return -4;
	}
	// Si inférieur à 0, alors il s'agit du retour du slot_num
	else if(action.colonne < 0)
	{
		action.colonne = action.colonne + (-action.colonne*2);
		MOTEUR_sauvegarde(jeu, action, allow_last);
	}
	// Si 2, alors on annule le dernier coup
	else if(action.colonne == 2)
	{
		// TODO
		if(jeu->allow_last)
		{
			MOTEUR_annulerDernierCoup(jeu);	
		}
		else
		{
		  	return -2; // Erreur
		}
	}
	// Si 3, alors on affiche l'aide des commandes
	else if(action.colonne == 3)
	{
		return -3;
	}
	// Si 4, alors on quitte la partie en cours
	else if(action.colonne == 4)
	{
		return 42; // The answer ... =)
	}
	else if(action.colonne == 5)
	{
		char save[20];
		t_jeu jeu;
		MOTEUR_chargement(jeu, save);
	}
	// Sinon, on retourne une erreur (choix inconnu)
	else
	{
		return -2; // Erreur
	}
    }
    // sinon, c'est une pièce à jouer
    else if(!t_jeu_oyaPossedePiece(jeu, action.typePiece)) {
        return -2; // action non valide ca rl'oya ne possède pas la pièce qu'il veut jouer
    }
    // sinon, c'est une pièce à jouer
    else 
    {
    	// On récupère la valeur de la ligne ou il est possible de placer la pièce
    	int ligne = MOTEUR_coordPieceJouee(jeu, action.typePiece, action.colonne);
	int oya = jeu->oya; // On récupère la valeur de l'oya
	// Si la valeur de ligne est égal à -1, c'est qu'il est impossible de placer la pièce ici
    	if(ligne == -1)
	{
	        // peut-être le plateau de jeu est-il plein...
                // on teste alors chaque colonne. Si aucune pièce ne peut être placée, 
                //      alors le plateau est plein
                t_action inter; // action intermédiaire de calcul
                bool plateauPlein = true; // vrai tant que plateau supposé remplis
                for(inter.colonne = 0; inter.colonne < jeu->nbCaseX && plateauPlein; 
                                inter.colonne++) {
                    for(inter.typePiece = 1; inter.typePiece < 4 && plateauPlein; 
                                    inter.typePiece++) {
                        // si la pièce peut-être mise
                        if(MOTEUR_coordPieceJouee(jeu, 
                                    inter.colonne, inter.typePiece) > -1)
                            plateauPlein = false; // plateau non remplis !
                    }
                }
                // retour code d'erreur
                if(plateauPlein)
                    return -43;
                else
		    return -2;
    	}
    	else
	{
		// On lance la procédure de modification du plateau de jeu
		bool next = MOTEUR_pieceJouee(jeu, action, ligne);
		if(!next) // si la pièce n'a pas été placée
		{
			return -2; // coup impossible
		}
                else // ENREGISTREMENT DU COUP
		{
			// On empile l'action en cours
			t_pileAction_emp(&jeu->pileAction, action);
		}
    		// TEST PUISSANCE 4 && CALCUL DES POINTS
		// >>> On déclare les variables et structures dont on a besoin <<<
		coord coordCase;
		coordCase.x=action.colonne;
		coordCase.y=ligne;
		// On commence par calculer les points
		MOTEUR_score(jeu, oya, action.colonne, ligne);
		// Puis le puissance 4
		// On lance la fonction de calcul
		int c_p4 = MOTEUR_test_puissance4(jeu, coordCase, oya);
		// Si c_p4 est égal ou supérieur à 4, alors puissance 4
		return MOTEUR_test_cond_puissance4(jeu, c_p4, next);
       }
   }
   return -1;
}

/*
 * MOTEUR PIECE JOUEE
 */
//Reçois en paramètre une action, une ligne & modifie le plateau de jeu ainsi 
//que le joueur en question, et retourne 1 pour indiquer que la pièce à bien 
//été placée, O sinon
bool MOTEUR_pieceJouee(t_jeu * jeu, t_action action, int ligne)
{
	int oya=jeu->oya; // On récupère l'oya
	// On vérifie si le joueur à joué une pièce blocante
	if(action.typePiece==BLOQUANTE) // Si oui, on décrémente
	{
		jeu->listeJoueur[oya].nbPieceBloquante--; // On décrémente le nombre de piece bloquante de l'oya
		// On place l'id de l'oya dans pieceCreuse & piecePleine, car il s'agit d'un piece bloquante
		jeu->plateau[action.colonne][ligne].joueurPieceCreuse=oya; 
		jeu->plateau[action.colonne][ligne].joueurPiecePleine=oya;
		// On indique qu'il s'agit bien d'un piece bloquante
		jeu->plateau[action.colonne][ligne].typePiece = BLOQUANTE;
	}
	// On enregistre qui à joué la piece CREUSE
	else if(action.typePiece==CREUSE)
	{
		/*
		 * Si la case en question à déja une piece (c'est-à-dire que l'un de ses
		 * id est différent de -1, alors on met le type de pièce à double
		 */
		if(jeu->plateau[action.colonne][ligne].joueurPiecePleine !=-1)
		{
			jeu->plateau[action.colonne][ligne].typePiece = DOUBLE;
		}
		// Sinon on c'est que la case en question est totalement vide, on peut 
		// donc y mettre n'importe quel type de piece sans problème
		else
		{
			jeu->plateau[action.colonne][ligne].typePiece=action.typePiece;
		}
                // l'oya contôle la pièce creuse de cette case
		jeu->plateau[action.colonne][ligne].joueurPieceCreuse=oya;
		// On décrémente le nombre de piece Creuse du joueur
		jeu->listeJoueur[oya].nbPieceCreuse--;
	}
	// On enregistre qui à joué la piece PLEINE
	else if(action.typePiece == PLEINE)
	{
		/*
		 * Si la case en question à déja une piece (c'est-à-dire que l'un de ses
		 * id est différent de -1, alors on met le type de pièce à double
		 */
		if(jeu->plateau[action.colonne][ligne].joueurPieceCreuse !=-1)
		{
			jeu->plateau[action.colonne][ligne].typePiece=DOUBLE;
		}
		// Sinon on c'est que la case en question est totalement vide, on peut 
		// donc y mettre n'importe quel type de piece sans problème
		else
		{
			jeu->plateau[action.colonne][ligne].typePiece=PLEINE;
		}
                // l'oya contôle la pièce pleine de cette case
		jeu->plateau[action.colonne][ligne].joueurPiecePleine=oya;
		// On décrémente le nombre de piece Pleine possedé par le joueur
		jeu->listeJoueur[oya].nbPiecePleine--;
	}
	// Sinon c'est que le type de pièce est inconnue
	else
	{
		return false;
	}
        // et on retourne vrai, si la pièce à bien été jouée
        return true;
}


/*
 * MOTEUR ANNULER DERNIER COUP
 */
// retire l'action précédente du jeu, retourne vrai. Si pas de denrière action,
//      retourne faux.
bool MOTEUR_annulerDernierCoup(t_jeu* jeu) {
    // initialisations
    int y = 0; // itérateur de boucle
    t_case* caseAModifier = NULL; // pointeur de case
    // on dépile la dernière action, et on l'enregistre
    t_action action = t_pileAction_dep(&(jeu->pileAction));
    // si l'action retournée est l'action nulle, on retourne faux.
    if(action.colonne == -1 || action.typePiece == -1) 
        return false;
    // sinon, c'est qu'une action est déterminée, il faut la retirer du jeu
    else {
        // on identifie la pièce placée lors de l'action : c'est la première du
        // type recherché dans la colonne de l'action.
        // pour chaque ligne de la colonne de l'action :
        for(y = 0; y < jeu->nbCaseY; y++) {
            // on pointe la case
            caseAModifier = &(jeu->plateau[action.colonne][y]); 
            // si on a trouvé la pièce
            if(caseAModifier->typePiece == action.typePiece) {
                caseAModifier->typePiece = VIDE;
                caseAModifier->joueurPieceCreuse = -1;
                caseAModifier->joueurPiecePleine = -1;
                y = jeu->nbCaseY; // fin de la boucle
            }
            else if(caseAModifier->typePiece == DOUBLE && 
                action.typePiece != BLOQUANTE) {
                if(action.typePiece == CREUSE) {
                    caseAModifier->typePiece = PLEINE;
                    caseAModifier->joueurPieceCreuse = -1;
                }
                else if(action.typePiece == PLEINE) {
                    caseAModifier->typePiece = CREUSE;
                    caseAModifier->joueurPiecePleine = -1;
                }
                y = jeu->nbCaseY; // fin de la boucle
            }
        }
        // l'oya deviens le joueur précédent
        if(jeu->oya == 0)
            jeu->oya = jeu->nbJoueur-1;
        else
            jeu->oya--;
        return true;
    }
}



/*
 * MOTEUR COORD PIECE JOUEE
 */
// renvois la coordonnee y d'une pièce placée dans la colonne. Ou -1 si pièce 
// impossible à mettre (atteinte de la limite haute)
// NB: n'effectue aucune modification du jeu !
int MOTEUR_coordPieceJouee(t_jeu* jeu, e_piece piecePlacee, int colonne) {
    // initialisations
    int i = 0; // itérateur de boucle
    int ligne = jeu->nbCaseY-1; // ligne où la pièce va se placer
    e_piece pieceCase; // pieces occupant la case étudiée

    // pour chaque case de la colonne, de bas en haut
    for(i = 0; i < jeu->nbCaseY; i++) {
	pieceCase = jeu->plateau[colonne][i].typePiece;
	// si la pièce de la case étudiée bloque le chemin 
	// 	(pièce bloquante, ou de même type que la pièce placée)
	if(pieceCase == BLOQUANTE 
		|| pieceCase == piecePlacee 
		|| pieceCase == DOUBLE
	        || (piecePlacee == BLOQUANTE && pieceCase != VIDE)) {
	            // si il n'y a pas de case au dessus, on renvois -1
	            if(i == 0) {
		        i = jeu->nbCaseY; // arrêt de la boucle
		        ligne = -1; // colonne pleine
	            }
	            // sinon, la ligne prend la valeur de la case supérieure
	            else {
		        ligne = i-1; 
		        i = jeu->nbCaseY; // arrêt de la boucle
                    }
	}
	// sinon, c'est que la case est praticable, on continue la boucle
    }
    return ligne;
}

/*
 * MOTEUR BORNE MAX
 */
// Détermine pour une case reçu en paramètre, la valeur MAX (3) ou
// minimum de celle-ci, représentant ainsi la  distance la séparant des
// bordures de la matrice
int * MOTEUR_borne_MAX(t_jeu* jeu, coord coordCase)
{	
	int i; // Itérateur de boucle
	// Tableau contenant les coordonnées max_h, max_b, max_g, max_d à retourner pour traitement
	int * max;
	max = malloc(4*sizeof(int)); // Tableau de taille 4 int pour chaque coordonnées
	/* 
	 * Les valeurs seront rangées comme cela : 
	 * max|  1   |   2   |   3   |   4   |
	 *     max_h | max_b | max_g | max_d |
	 */
	// >>> MAX_DROIT && MAX_BAS <<<
	max[4]=(jeu->nbCaseX-1)-coordCase.x;
	max[2]=(jeu->nbCaseY-1)-coordCase.y;
	// >>> MAX GAUCHE && MAX DROIT <<<
	max[1]=((jeu->nbCaseY-1)-max[2]);
	max[3]=((jeu->nbCaseX-1)-max[4]);
	// On détermine la valeur de max précisement ( min = 0 & max = 3)
	for(i=1;i!=5;i++)
	{
		// Si max est supérieur à 3, alors max=3 (inutile de prendre en compte les cases
		// suivante pour le test de puissance 4)
		if(max[i]>3)
		{
			max[i]=3;
		}
	}
	// On retourne le tableau contenant toutes les valeurs correspondant aux valeurs max
	return max;
}

/*
 * MOTEUR TEST C_P4++
 */
// Effectue les différents test et retourne la nouvelle valeur de c_p4
int MOTEUR_test_c_p4(t_jeu* jeu, int i, int j, int idJ, int c_p4)
{	
	// Si la piece courante à le même id que le joueur courant, alors on incrémente 
	if(jeu->plateau[i][j].joueurPieceCreuse == idJ ||
	   jeu->plateau[i][j].joueurPiecePleine == idJ)
	{
		c_p4++;
	}
	// Si on sort du if, c'est qu'il y a une coupure entre deux piece de même type (elles ne se suivent pas)
	else
	{
		c_p4=0; // On recommence le décompte à zéro
	}
	return c_p4;
}




/*
 * MOTEUR TEST PUISSANCE 4
 */
// renvois le nombre de pieces à la suite appartenant au même joueur
//Reçois en paramètre :
//	- le jeu
//	- une structure coord correspondant à la case en question
//	- un id de joueur
int MOTEUR_test_puissance4(t_jeu* jeu, coord coordCase, int idJ)
{
	// Déclare un tableau pour récupérer les valeurs max
	int * maxi;
	maxi=malloc(4*sizeof(int));
	maxi=MOTEUR_borne_MAX(jeu, coordCase);
	// On trie les valeurs au bon endroit
	int max_h=maxi[1], max_b=maxi[2]; // Borne haute et basse du plateau
	int max_g=maxi[3], max_d=maxi[4]; // Borne gauche et droite du plateau
	int i,j; // Itérateur de boucle
        int maxPiece = 0; // contient le nombre maximum de pièces alignées
	int c_p4=0; // Compteur pour le puissance 4, si c_p4 >= 4, alors il y a puissance 4
	i=coordCase.x; // Pour un traitement correct des conditions
	/*
	 * Les coordonnées étant inversé, nous devons soustraire pour monter en haut du plateau, et additioner
	 * pour nous rendre en bas du plateau ! =) et oui ...
	 */
	// >>> TEST BAS-HAUT <<<
	// On part de la case courante -3 jusqu'à la case courante + 3
	for(j=coordCase.y+max_b;j>coordCase.y-max_h;j--)
	{
		c_p4=MOTEUR_test_c_p4(jeu, i, j, idJ, c_p4); // c_p4 est égal à la valeur de retour de la fonction test_c_p4
                maxPiece = c_p4; // on enregistre le max de pièces alignées
		if(c_p4>=4)
		{
			return c_p4;
		}

	}
	// Avant de changer de type de test on remet les compteurs à zéro
	c_p4=0;
	// >>> TEST GAUCHE-DROITE <<<
	//On part de la case courante -3 jusqu'à la case courante +3
	for(i=coordCase.x-max_g, j=coordCase.y;i<=coordCase.x+max_d;i++)
	{
		c_p4=MOTEUR_test_c_p4(jeu, i, j, idJ, c_p4); // c_p4 est égal à la valeur de retour de la fonction test_c_p4
                maxPiece = max(maxPiece, c_p4); // on enregistre le max de pièces alignées
		if(c_p4>=4)
		{
			return c_p4;
		}

	}
	// Avant de changer de type de test on remet les compteurs à zéro
	c_p4=0;
	// >>> TEST DIAG BasDroit->HautGauche <<<
	//On part de la case courante +3 jusqu'à la case courante -3 pour les colonnes
	for(i=coordCase.x+max_d, j=coordCase.y+max_b; // Pour la case diag BasDroit max
	    (i>coordCase.x-max_g && j>coordCase.y-max_h); // Tant que pas case diag HautGauche
	    i--, j--) // On décrémente i & j
	{
		c_p4=MOTEUR_test_c_p4(jeu, i, j, idJ, c_p4); // c_p4 est égal à la valeur de retour de la fonction test_c_p4
                maxPiece = max(maxPiece,c_p4); // on enregistre le max de pièces alignées
		if(c_p4>=4)
		{
			return c_p4;
		}

	}
	// Avant de changer de type de test, on remet le compteurs à zéro
	c_p4=0;
	// >>> TEST DIAG BasGauche->HautDroit <<<
	// On part de la case courante -3 jusqu'à la case courante +3 pour les colonnes
	for(i=coordCase.x-max_g, j=coordCase.y+max_b; // Pour la case diag BasGauche max
	    (i<coordCase.x+max_d && j>coordCase.y-max_h); // Tant que pas case diag HautDroit max
	    i++, j--) // On décrémente i & j
	{
		c_p4=MOTEUR_test_c_p4(jeu, i, j, idJ, c_p4); // c_p4 est égal à la valeur de retour de la fonction test_c_p4
                maxPiece = max(maxPiece,c_p4); // on enregistre le max de pièces alignées
		if(c_p4>=4)
		{
			return c_p4;
		}

	}
	free(maxi);
        c_p4 = maxPiece; // on rend c_p4 égal au maximum de pièces rencontrées
	return c_p4; // On retourne la valeur de c_p4 pour post-traitement
}

/*
 * MOTEUR TEST COND PUISSANCE 4
 */
// Test si la il y a puissance 4
// Prend en paramètre :
// 			- un int correspondant au compteur de
// 			  puissance 4
// 			- un booléen indiquant si le tour peut passer au joueur suivant
// 			- 
int MOTEUR_test_cond_puissance4(t_jeu * jeu, int c_p4, bool next)
{
	int oya = jeu->oya; // On récupère l'oya
	// Si le compteur c_p4 est supérieur ou égal
	// à 4, alors il y a puissance 4
	if(c_p4>=4)
	{
		// On ajoute 200 points au gagnant
		jeu->listeJoueur[oya].points+=200;
		// On retourne le gagnant
		return oya;
	}
	// 
	else
	{	
		// Si la pièce est placée
		if(next)
		{
			// Alors on passe au joueur suivant
			t_jeu_joueurSuivant(jeu);
			return -1;
		}
		// Sinon
		else
		{
			// On continue avec le même joueur
			return -1;
		}
	}
}




/*
 * MOTEUR SAUVEGARDE
 */
// Procédure de sauvegarde
// Reçois en paramètre :
// 			- le jeu
// 			- une action
// 			- la pile d'action
void MOTEUR_sauvegarde(t_jeu * jeu, t_action action, bool allow_last)
{
	int i = 0, j =0; // Itérateur de boucle

	// >>> PREPARATION SAUVEGARDE <<<
	
	// Création des variables 
	char sauvegarde[15] = "save/save";
	char slot[2];
	char end_save[3] = ".sv";
	
	// On convertie action.colonne en string
	sprintf(slot, "%i", action.colonne); // Convertion int en string 
	
	// Fusion des chaines de caractères
	strcat(sauvegarde, slot);
	strcat(sauvegarde, end_save);

	// Ouveerture du fichier
	FILE * file_save = fopen(sauvegarde, "w");
	    	
	//>>> SAUVEGARDE <<<
	
	// ## élément important pour le chargement ##
	
	//	>>> Taille du plateau <<<
	fprintf(file_save, "%i %i ", jeu->nbCaseX, jeu->nbCaseY);
	//	>>> Nombre de joueur <<<
	fprintf(file_save, "%i ", jeu->nbJoueur);
	//	>>> Autorisation dernier coup <<<
	fprintf(file_save, "%i \n", allow_last);

	// ## plateau de jeu ##
		
	for(i=0;i<jeu->nbCaseX;i++)
	{
		for(j=0;j<jeu->nbCaseY;j++)
		{
			// Enregistrement des pièces 
			fprintf(file_save, "%i ", jeu->plateau[i][j].joueurPieceCreuse);
			fprintf(file_save, "%i ", jeu->plateau[i][j].joueurPiecePleine);
			fprintf(file_save, "%i ", jeu->plateau[i][j].typePiece);
			fprintf(file_save, "\n");
		}
	}

	// ## Données de jeu ##
	
	fprintf(file_save, "%i ", jeu->oya);
	//fprintf(file_save, "%i ", jeu->nbJoueur);
	fprintf(file_save, "%i ", jeu->nbIA);
	fprintf(file_save, "%i ", jeu->nbPieceBloquante);
	fprintf(file_save, "%i ", jeu->nbPiecePleine);
	fprintf(file_save, "%i ", jeu->nbPieceCreuse);
	fprintf(file_save, "\n");

	// ## Joueurs ##
	
	for(i=0;i<jeu->nbJoueur;i++);
	{
		fprintf(file_save, "%i ", jeu->listeJoueur[i].points);
		fprintf(file_save, "%i ", jeu->listeJoueur[i].idJ);
		fprintf(file_save, "%i ", jeu->listeJoueur[i].nbPieceBloquante);
		fprintf(file_save, "%i ", jeu->listeJoueur[i].nbPiecePleine);
		fprintf(file_save, "%i ", jeu->listeJoueur[i].nbPieceCreuse);
		fprintf(file_save, "%i ", jeu->listeJoueur[i].IA);
		fprintf(file_save, "%i ", jeu->listeJoueur[i].niveauIA);
		fprintf(file_save, "%i ", jeu->listeJoueur[i].intrepidite);
		//fprintf(file_save, "%s ", jeu->listeJoueur[i].nom);
		fprintf(file_save, "\n");
		printf("IA : %i\n", jeu->listeJoueur[i].IA);
		printf("creuse : %i\n", jeu->listeJoueur[i].nbPieceCreuse);
	}

	// ## Pile d'action ##
	
	// >>> END <<<
	
	fprintf(file_save, "\n\n");

	// Fermeture du fichier
	fclose(file_save);
}


/*
 * MOTEUR CHARGEMENT
 */
//  Charge la sauvegarde reçu en paramètre
t_jeu MOTEUR_chargement(t_jeu jeu, char * save)
{
	fprintf(stderr, "begin load : OK\n");
	int i = 0, j = 0; // Itérateur de boucle
	int creuse = 0, pleine = 0, piece = 0;
	int IA = 0;
	// Pour le nom
	//char *nom;
	//nom = malloc(8*sizeof(char));
	//int c_nom = 0; // compteur pour le nom
	int tmp_allow_last = 0; // tmp contenant la valeur du bool allow_last
	// >>> PREPARATION SAUVEGARDE <<<
	fprintf(stderr, "Creating var : OK\n");
	FILE * file_load;
	char beg_save[5] = "save/";
	strcat(beg_save, save);
	file_load = fopen(beg_save, "r");
	fprintf(stderr, "Creating file : OK\n");
	fprintf(stderr, "name : %s\n", save);
	// >>> CHARGEMENT <<<
	
	// On commence par récupérer les données essentielles
	// 	>> Taille du plateau
	fscanf(file_load, "%i %i", &jeu.nbCaseX, &jeu.nbCaseY);	
	// 	>> Nombre de joueurs
	fprintf(stderr, "debug : 1\n");
	fscanf(file_load, "%i", &jeu.nbJoueur);
	fprintf(stderr, "nbJoueurs : %i\n", jeu.nbJoueur);
	// 	>> Autorisation dernier coup
	fprintf(stderr, "debug : 2\n");
	fscanf(file_load, "%i", &tmp_allow_last);
	fprintf(stderr, "debug : 3\n");
	if(tmp_allow_last == 1)
	{
		allow_last = true;
	}
	else
	{
		allow_last = false;
	}
	fprintf(stderr, "debug : 4\n");

	// >>> PLATEAU DE JEU
	
	fprintf(stderr, "taille jeu : [%i][%i]\n", jeu.nbCaseX, jeu.nbCaseY);
	
	for(i=0;i<jeu.nbCaseX;i++)
	{
	fprintf(stderr, "debug : 5\n");
		for(j=0;j<jeu.nbCaseY;j++)
		{
			// Coordonnées de la case dans le jeu
			fprintf(stderr, "debug : 6\n");

			//fscanf(file_load, "%i", &jeu.plateau[i][j].crd.x);
			fprintf(stderr, "debug : 6.1\n");

			//fscanf(file_load, "%i", &jeu.plateau[i][j].crd.y);
			// Enregistrement des pièces 
			fscanf(file_load, "%i", &creuse); 		
			fscanf(file_load, "%i", &pleine); 
			fscanf(file_load, "%i", &piece);
			fprintf(stderr, "c : %i p : %i b : %i\n", creuse, pleine, piece);
			fprintf(stderr, "debug : 7\n");
			// Si une piece creuse
			if(creuse != -1)
			{
				// Si aussi une piece pleine
				if(pleine != -1)
				{
					// Alors c'est une piece bloquante
					jeu.plateau[i][j].typePiece=BLOQUANTE;
					// On place l'id du joueur ayant placé la piece
					jeu.plateau[i][j].joueurPieceCreuse=creuse;
					jeu.plateau[i][j].joueurPiecePleine=pleine;
				}
				// Sinon il ne s'agit que d'une piece creuse
				else
				{
					// On place le type piece de la case à creuse
					jeu.plateau[i][j].typePiece=CREUSE;
					// On ajoute l'id du joueur correspondant
					jeu.plateau[i][j].joueurPieceCreuse=creuse;
				}

				// On remet les variables à -1 pour ne pas entrer dans les autres boucles
				pleine = -1;
				creuse = -1;
			}
			// Sinon si c'est une piece pleine
			else if(pleine != -1)
			{
				// Si aussi une piece creuse
				if(creuse != -1)
				{
					// Alors c'est une piece bloquante
					jeu.plateau[i][j].typePiece=BLOQUANTE;
					// On place l'id du joueur ayant placé la piece
					jeu.plateau[i][j].joueurPieceCreuse=creuse;
					jeu.plateau[i][j].joueurPiecePleine=pleine;
				}
				// Sinon il ne s'agit que d'une piece pleine
				else
				{
					// On place le type piece de la case à pleine
					jeu.plateau[i][j].typePiece=PLEINE;
					// On ajoute l'id du joueur correspondant
					jeu.plateau[i][j].joueurPieceCreuse=pleine;
				}

				// On remet les variables à -1 pour ne pas entrer dans les autres boucles
				pleine = -1;
				creuse = -1;
			}
		}
	}

	// >>> DONNEES DE JEU
	
	fscanf(file_load, "%i", &jeu.oya);
	//fscanf(file_load, "%i", &jeu.nbJoueur);
	fscanf(file_load, "%i", &jeu.nbIA);
	fscanf(file_load, "%i", &jeu.nbPieceBloquante);
	fscanf(file_load, "%i", &jeu.nbPiecePleine);
	fscanf(file_load, "%i", &jeu.nbPieceCreuse);
	fprintf(stderr, "debug : 9\n");

	// >>> JOUEURS
	
	fprintf(stderr, "nbJoueurs : %i\n", jeu.nbJoueur);
	fprintf(stderr, "debug : 10\n");
	for(i=0;i<jeu.nbJoueur;i++)
	{
		fscanf(file_load, "%i", &jeu.listeJoueur[i].points);
		fprintf(stderr, "debug : 11\n");

		fscanf(file_load, "%i", &jeu.listeJoueur[i].idJ);
		fprintf(stderr, "debug : 12\n");

		fscanf(file_load, "%i", &jeu.listeJoueur[i].nbPieceBloquante);
		fprintf(stderr, "debug : 13\n");

		fscanf(file_load, "%i", &jeu.listeJoueur[i].nbPiecePleine);
		fprintf(stderr, "debug : 14\n");

		fscanf(file_load, "%i", &jeu.listeJoueur[i].nbPieceCreuse);
		fprintf(stderr, "debug : 15\n");

		fscanf(file_load, "%i", &IA);
		if(IA == 1)
		{
			jeu.listeJoueur[i].IA = true;
		}
		else
		{
			jeu.listeJoueur[i].IA = false;
		}
		fscanf(file_load, "%i", &jeu.listeJoueur[i].niveauIA);
		fscanf(file_load, "%i", &jeu.listeJoueur[i].intrepidite);
		//fscanf(file_load, "%s", &jeu->listeJoueur[i].nom);
	}
	fprintf(stderr, "END LOAD : OK\n");
	//free(nom);
	return jeu;
}


/*
 * MOTEUR SCORE
 */
// Modifie le score d'un joueur.
// Reçoit en paramètre :
// 	- un ID de joueur
// 	- la valeur à ajouter ou modifier
void MOTEUR_score(t_jeu * jeu, int idJ, int i, int j)
{
	// Si le joueur à posé une pièce bloquante
	//  --> -200
	if(jeu->plateau[i][j].typePiece==BLOQUANTE &&
	   jeu->plateau[i][j].joueurPieceCreuse==idJ &&
	   jeu->plateau[i][j].joueurPiecePleine==idJ)
	{
		// On ajoute 10 points au joueur
		jeu->listeJoueur[idJ].points+=10;
	}
	// Sinon si le joueur à posé une piece CREUSE ou PLEINE sur une case VIDE
	//  --> +30
	else if((jeu->plateau[i][j].typePiece==CREUSE ||
	    jeu->plateau[i][j].typePiece==PLEINE) &&
	   (jeu->plateau[i][j].joueurPieceCreuse==-1 ||
	    jeu->plateau[i][j].joueurPiecePleine==-1) &&
	   (jeu->plateau[i][j].joueurPieceCreuse==idJ ||
	    jeu->plateau[i][j].joueurPiecePleine==idJ))
	{
		// On ajoute 30 points au joueurs
		jeu->listeJoueur[idJ].points+=30;
	}
	
	// Sinon si le joueur à posé une pièce CREUSE ou PLEINE sur une case occupé
	//  --> +70
	else if((jeu->plateau[i][j].typePiece==DOUBLE) &&
	   ((jeu->plateau[i][j].joueurPieceCreuse==idJ &&
	    jeu->plateau[i][j].joueurPiecePleine!=-1) ||
	   (jeu->plateau[i][j].joueurPieceCreuse!=-1 &&
	    jeu->plateau[i][j].joueurPiecePleine==idJ)))
	{
		// On ajoute 70 points au joueur
		jeu->listeJoueur[idJ].points+=70;
	}
	/*
	 * La pièce posé par le joueur et le calcul du
	 * bloque des combo adversaire est fait
	 * séparement
	 */
	// Contient le nombre de pièce à la suite posée
	// par une joueur adverse & bloquées par le 
	// joueurs en cours
	//int combo=0;
	// Si le joueur contre une suite adverse de 2 ou 3 piece
	// TODO
	//  --> + 200 pour 2 pièce
	//  --> + 300 pour 3 pièce
}




/*
 * MOTEUR ENREGISTER SCORE
 */
// Enregistre le score du joueur
void MOTEUR_enregistrerScore(t_jeu * jeu, int idJ, char * name)
{
	// Ouverture du fichier, en mode ajout
	FILE * file_score = fopen("save/score.txt", "wa");
	// Enregistrement des données
	fprintf(file_score, "%s %i\n", name, jeu->listeJoueur[idJ].points);
	fprintf(file_score, "\n");
	// Fermeture des données
	fclose(file_score);
}


/*
 * MOTEUR VIDER SCORE
 */
// Vide le fichier des scores
void MOTEUR_viderScore()
{
	// TODO
}


/*
 * MOTEUR ANNULER DERNIER COUP
 */
// Annule le dernier coup du joueur en cours, et retourne l'oya
int MOTEUR_tourPrecedent(t_jeu* jeu)
{
	int i = 0;
        // on annule un coup pour chaque joueur
        for(i = 0; i < jeu->nbJoueur; i++) 
            MOTEUR_annulerDernierCoup(jeu);
        return jeu->oya;
}
