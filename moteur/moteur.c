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
     * 1. SAVE
     * 2. LAST
     * 3. HELP
     * 4. EXIT
     *
     * Si différent, erreur et on recommence la demande, sans changer de joueur
     *
     * INDEX DES RETOURS
     *
     * return -1 : La partie n'est pas terminée et continue normalement
     * return -2 : Erreur, l'action n'est pas valide
     * return -3 : On affiche l'aide des commandes
     * return 42 : On quitte la partie en cours && retour au menu principal
     * return 43 : Le plateau de jeu est plein, on retourne égalité
     */
    if(action.typePiece == VIDE) // action.colonne == VIDE, donc on passe en mode commande
    {
    	// Si 1, alors on lance le module de sauvegarde
    	if(action.colonne == 1)
	{
    		printf("Building module, please wait.");
    		//MOTEUR_sauvegarde();
	}
	// Si 2, alors on annule le dernier coup
	else if(action.colonne == 2)
	{
		// TODO
		/*
		 * if(allow_last)
		 * {
		 * 	MOTEUR_annuler_dernier_coup();	
		 * }
		 * else
		 * {
		 * 	return -2; // Erreur
		 * }
		 */
		return -1;
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
	// Sinon, on retourne une erreur (choix inconnu)
	else
	{
		return -2; // Erreur
	}
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
		return -2;
    	}
    	else
	{
		/*
		 * On test si le plateau de jeu est plein
		 */
		// On crée une variable contenant la taille du plateau
		int taille = (jeu->nbCaseX * jeu->nbCaseY);
		// On test si le nombres pièces posées est égal à la taille du plateau
		if(taille == jeu->pileAction.nbElem)
		{
			// Si oui, on retourne code:erreur 43
			return 43;
		}
		bool next = false;
		// On lance la procédure de modification du plateau de jeu
		MOTEUR_pieceJouee(jeu, action, ligne, next);
		// ENREGISTREMENT DU COUP
		// !!! On enregistre le coup uniquement lorsque celui-ci à été validé par 
		// le moteur !!!
		// >>> On empile l'action en cours <<<
		t_pileAction_emp(&jeu->pileAction, action);
    		// TEST PUISSANCE 4
		// >>> On déclare les variables et structures dont on a besoin <<<
		coord coordCase;
		coordCase.x=action.colonne;
		coordCase.y=ligne;
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
bool MOTEUR_pieceJouee(t_jeu * jeu, t_action action, int ligne, bool next)
{
	int oya=jeu->oya; // On récupère l'oya
	jeu->plateau[action.colonne][ligne].typePiece=action.typePiece; // On modifie le plateau de jeu en fonction de la piece jouée
	// On vérifie si le joueur à joué une pièce blocante
	if(action.typePiece==BLOQUANTE) // Si oui, on décrémente
	{
		//Si le nombre de piece bloquante n'est pas égal à zéro, alors on peut en placer une
		if(jeu->listeJoueur[oya].nbPieceBloquante>0)
		{
			jeu->listeJoueur[oya].nbPieceBloquante--; // On décrémente le nombre de piece bloquante de l'oya
			// On place l'id de l'oya dans pieceCreuse & piecePleine, car il s'agit d'un piece bloquante
			jeu->plateau[action.colonne][ligne].joueurPieceCreuse=oya; 
			jeu->plateau[action.colonne][ligne].joueurPiecePleine=oya;
			// On indique qu'il s'agit bien d'un piece bloquante
			jeu->plateau[action.colonne][ligne].typePiece=action.typePiece;
			return next = true;
		}
		//Sinon on retourne null, et on redemande au joueur de placer une pièce
		else
		{
			return next;
		}
	}
	// On enregistre qui à joué la piece CREUSE
	else if(action.typePiece==CREUSE)
	{
		/*
		 * Si la case en question à déja une piece (c'est-à-dire que l'un de ses
		 * id est différent de -1, alors on met le type de pièce à double
		 */
		if(jeu->plateau[action.colonne][ligne].joueurPieceCreuse !=-1 ||
		   jeu->plateau[action.colonne][ligne].joueurPiecePleine != -1)
		{
			jeu->plateau[action.colonne][ligne].joueurPieceCreuse=oya;
			jeu->plateau[action.colonne][ligne].joueurPieceCreuse=DOUBLE;
			return next = true;

		}
		// Sinon on c'est que la case en question est totalement vide, on peut 
		// donc y mettre n'importe quel type de piece sans problème
		else
		{
			jeu->plateau[action.colonne][ligne].joueurPieceCreuse=oya;
			jeu->plateau[action.colonne][ligne].typePiece=action.typePiece;
			return next = true;
		}
	}
	// On enregistre qui à joué la piece PLEINE
	else
	{
		/*
		 * Si la case en question à déja une piece (c'est-à-dire que l'un de ses
		 * id est différent de -1, alors on met le type de pièce à double
		 */
		if(jeu->plateau[action.colonne][ligne].joueurPieceCreuse !=-1 ||
		   jeu->plateau[action.colonne][ligne].joueurPiecePleine != -1)

		{
			jeu->plateau[action.colonne][ligne].joueurPiecePleine=oya;
			jeu->plateau[action.colonne][ligne].typePiece=DOUBLE;
			return next = true;
		}
		// Sinon on c'est que la case en question est totalement vide, on peut 
		// donc y mettre n'importe quel type de piece sans problème
		else
		{
			jeu->plateau[action.colonne][ligne].joueurPiecePleine=oya;
			jeu->plateau[action.colonne][ligne].typePiece=action.typePiece;
			return next = true;
		}
	}
}


/*
 * MOTEUR TOUR PRECEDENT
 */
// retire l'action précédente du jeu, retourne vrai. Si pas de denrière action,
//      retourne faux.
bool MOTEUR_tourPrecedent(t_jeu* jeu) {
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
    for(i = jeu->nbCaseY-1; i >= 0; i--) {
	pieceCase = jeu->plateau[colonne][i].typePiece;
	// si la pièce de la case étudiée bloque le chemin 
	// 	(pièce bloquante, ou de même type que la pièce placée)
	if((	pieceCase == BLOQUANTE 
		|| pieceCase == piecePlacee 
		|| pieceCase == DOUBLE)
	    || // exception : cas où la pièce est bloquante
		(piecePlacee == BLOQUANTE && pieceCase != VIDE)) {
	    // si il n'y a pas de case au dessus, on renvois -1
	    if(i == 0) {
		i = -1; // arrêt de la boucle
		ligne = -1; // colonne pleine
	    }
	    // sinon, la ligne prend la valeur de la case supérieure
	    else
		ligne = i-1; 
	}
	// sinon, c'est que la case est praticable, on arrête le traitement ici
	else 
	    i = -1;
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
	idJ = jeu->oya; // On prend l'id du joueur en cours
	// Déclare un tableau pour récupérer les valeurs max
	int * max;
	max=malloc(4*sizeof(int));
	max=MOTEUR_borne_MAX(jeu, coordCase);
	// On trie les valeurs au bon endroit
	int max_h=max[1], max_b=max[2]; // Borne haute et basse du plateau
	int max_g=max[3], max_d=max[4]; // Borne gauche et droite du plateau
	int i,j; // Itérateur de boucle
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
		if(c_p4>=4)
		{
			return c_p4;
		}

	}
	free(max);
	return c_p4; // On retourne la valeur de c_p4 pour post-traitement
}

/*
 * MOTEUR TEST COND PUISSANCE 4
 */
// Test si la il y a puissance 4
// Prend en paramètre :
// 			- un int correspondant au compteur de
// 			  puissance 4
int MOTEUR_test_cond_puissance4(t_jeu * jeu, int c_p4, bool next)
{
	int oya = jeu->oya; // On récupère l'oya
	// Si le compteur c_p4 est supérieur ou égal
	// à 4, alors il y a puissance 4
	if(c_p4>=4)
	{
		return oya;
	}
	// 
	else
	{
		if(next)
		{
			t_jeu_joueurSuivant(jeu);
			return -1;
		}
		else
		{
			return -1;
		}
	}
}

/*
 * MOTEUR SAUVEGARDE
 */
// Procédure de sauvegarde
// Reçois en paramètre :
// 			-
/*MOTEUR_sauvegarde()
{
//int i = 0; //itérateur de boucle
    //si le type de pièce de l'action est VIDE, alors on considère que 
    //	l'utilisateur à voulut sauvegarder la partie.
    //	la colonne correspond au slot de sauvegarde
    //	nom d'un slot : saveN.sv (avec N le numéro de slot)

    // On s'occupe des sauvegardes
    
    FILE * file_save;

// On compte le nombre de chiffres dans le string
    	char * str = action.colonne; // Contient la chaine à analyser
	char slot_num[3]; // Contient le numéro du slot
	int i=0; // itérateur de boucle
	// On récupère le nombre de chiffres de str dans slot_num 	
	do {
		slot_num[i]=str[i];
		i++;
	} while(isdigit(slot_num[i]));
	// Création de la chaine de caractère pour le nom final
	char save[10] = "save";
	char end_save[3] = ".sv";
	// Fusion des chaines de caractères
	strcat(save, slot_num);
	strcat(save, end_save);
	// Création du fichier 
	file_save = fopen(save, "w");
	// On commence par sauvegarder tout ce qui est hors du plateau de jeu
	
	//	>>> On sauvegarde les joueurs <<<
	

	
	//Structure de joueur
	


	// TODO: A compléter, envoie du jeu dans fichier de sauvegarde
	// Ne pas oublier une gestion d'erreur
}*/
