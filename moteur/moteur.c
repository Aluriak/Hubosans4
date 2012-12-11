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
t_joueur* MOTEUR_tourSuivant(t_jeu* jeu, t_action action) 
{
    if(action.typePiece == VIDE) // action.typePiece est NULL, donc sauvegarde
    {
    	printf("Building module, please wait.");
    	//MOTEUR_sauvegarde();
    }
    // sinon, c'est une pièce à jouer
    else 
    {
    	int ligne = MOTEUR_coordPieceJouee(jeu, action.typePiece, action.colonne);
	int oya = jeu->oya;
    	if(ligne == -1) {
		// A corriger, le moteur n'affiche rien ! :o
		printf("Unable to put piece here !");
    	}
    	else {
    		jeu->plateau[action.colonne][ligne].typePiece=action.typePiece;
		// On vérifie si le joueur à joué une pièce blocante
		if(action.typePiece==BLOQUANTE) // Si oui, on décrémente
		{
			// On parcours la liste des joueurs, jusqu'à ce que l'on trouve :
			// oya == jeu->listeJoueur[i].idJ
			int i; // itérateur de boucle
			for(i=0;i<jeu->nbJoueur-1;i++)
			{
				// Si l'id du joueur = oya, c'est qu'on à trouvé le joueur courant
				if(jeu->listeJoueur[i].idJ==oya)
				{
					// On décrémente son nombre de pieces bloquante
					jeu->listeJoueur[i].nbPieceBloquante--;
					jeu->plateau[action.colonne][ligne].joueurPieceCreuse=oya;
					jeu->plateau[action.colonne][ligne].joueurPiecePleine=oya;
					i=7; // Afin d'éviter de boucler sur les autres joueurs
				}
			}
		}
		// On enregistre qui à joué la piece CREUSE
		else if(action.typePiece==CREUSE)
		{
			jeu->plateau[action.colonne][ligne].joueurPieceCreuse=oya;
		}
		// On enregistre qui à joué la piece PLEINE
		else if(action.typePiece==PLEINE)
		{
			jeu->plateau[action.colonne][ligne].joueurPiecePleine=oya;
		}
		// On test si il y a un puissance 4
		// >>> On déclare les variables et structures dont on a besoin <<<
		coord coordCase;
		coordCase.x=action.colonne;
		coordCase.y=ligne;
		// >>> END <<<
		// On lance la fonction de calcul
		int c_p4=MOTEUR_test_puissance4(jeu, coordCase, oya);
		printf("val c_p4 = %i\n", c_p4);
		// >>> On lance le test final <<<
		// Si c_p4 est égal ou supérieur à 4, alors puissance 4
		if(c_p4>=4)
		{
			// On modifie la structure gagnant de type t_joueur
			//gagnant->idJ=oya;
			//return EXIT_SUCCESS;
			printf("Puissance 4 !\n");
		}
		// Sinon on passe au joueur suivant
		else
		{
			// L'oya est mis au joueur suivant
			printf("Tour suivant\n");
			t_jeu_joueurSuivant(jeu);
			return NULL;
      		}
     }
   }
   return NULL;
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
	max[1]=((jeu->nbCaseY-1)-max[2])-1;
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
	for(i=1;i!=5;i++)
	{
		fprintf(stderr, "max[%i] : %i\n", i,max[i]);
	}
	fprintf(stderr, "max_H : %i\n", max_h);
	fprintf(stderr, "max_B : %i\n", max_b);
	fprintf(stderr, "max_G : %i\n", max_g);
	fprintf(stderr, "max_D : %i\n", max_d);
	int c_p4=1; // Compteur pour le puissance 4, si c_p4 >= 4, alors il y a puissance 4
	// >>> TEST BAS-HAUT <<<
	i=coordCase.x; // Pour un traitement correct des conditions
	// On part de la case courante -3 jusqu'à la case courante + 3
	/*
	 * Les coordonnées étant inversé, nous devons soustraire pour monter en haut du plateau, et additioner
	 * pour nous rendre en bas du plateau ! =) et oui ...
	 */
	for(j=coordCase.y+max_b;j<coordCase.y-max_h;j++)
	{
		// Si la piece courante à le même id que le joueur courant, alors on incrémente 
		if(jeu->plateau[j][i].joueurPieceCreuse == idJ ||
	   	   jeu->plateau[j][i].joueurPiecePleine == idJ)
		{
			c_p4++;
			printf("c_p4 : %i\n", c_p4);
		}
		// Si on sort du if, c'est qu'il y a une coupure entre deux piece de même type (elles ne se suivent pas)
		else
		{
			c_p4=0; // On recommence le décompte à zéro
			printf("c_p4 : %i\n", c_p4);
		}
	}
	if(c_p4>=4)
	{
		return c_p4;
	}
	fprintf(stderr, "loop #1 : OK \n");
	// Avant de changer de type de test on remet les compteurs à zéro
	c_p4=0;
	// >>> TEST GAUCHE-DROITE <<<
	//On part de la case courante -3 jusqu'à la case courante +3
	for(i=coordCase.x-max_g;i<coordCase.x+max_d;i++)
	{
		// Si la piece courante à le même id que le joueur courant, alors on incrémente
		if(jeu->plateau[j][i].joueurPieceCreuse == idJ ||
		   jeu->plateau[j][i].joueurPiecePleine == idJ)
		{
			c_p4++;
			printf("c_p4 : %i\n", c_p4);
		}
		else
		{
			c_p4=0; // On recommence le décompte à zéro
			printf("c_p4 : %i\n", c_p4);
		}
	}
	if(c_p4>=4)
	{
		return c_p4;
	}
	fprintf(stderr, "loop #2 : OK \n");
	// Avant de changer de type de test on remet les compteurs à zéro
	c_p4=0;
	// >>> TEST DIAG BasDroit->HautGauche <<<
	//On part de la case courante +3 jusqu'à la case courante -3 pour les colonnes
	for(i=coordCase.x+max_d;i>coordCase.x-max_g;i--)
	{
		// On part de la case courante -3 jusqu'à la case courante +3 pour les lignes
		for(j=coordCase.y+max_b;j>coordCase.y-max_h;j--)
		{
			if(jeu->plateau[j][i].joueurPieceCreuse == idJ ||
			   jeu->plateau[j][i].joueurPiecePleine == idJ)
			{
				c_p4++;
				printf("c_p4 : %i\n", c_p4);
			}
			else
			{
				c_p4=0; // On recommence le décompte à zéro
				printf("c_p4 : %i\n", c_p4);
			}
		}
	}
	if(c_p4>=4)
	{
		return c_p4;
	}
	fprintf(stderr, "loop #3 : OK \n");
	// Avant de changer de type de test, on remet le compteurs à zéro
	c_p4=0;
	// >>> TEST DIAG BasGauche->HautDroit <<<
	// On part de la case courante -3 jusqu'à la case courante +3 pour les colonnes
	for(i=coordCase.x-max_g;i<coordCase.x+max_d;i++)
	{
		// On part de la case courante -3 jusqu'à la case courante +3 pour les lignes
		for(j=coordCase.y+max_b;j>coordCase.y-max_h;j--)
		{
			if(jeu->plateau[j][i].joueurPieceCreuse == idJ ||
			   jeu->plateau[j][i].joueurPieceCreuse == idJ)
			{
				c_p4++;
				printf("c_p4 : %i\n", c_p4);
			}
			else
			{
				c_p4=0; // On recommence le décompte à zéro
				printf("c_p4 : %i\n", c_p4);
			}
		}
	}
	if(c_p4>=4)
	{
		return c_p4;
	}
	fprintf(stderr, "loop #4 : OK \n");
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
int MOTEUR_test_cond_puissance4(int c_p4)
{
	// Si le compteur c_p4 est supérieur ou égal
	// à 4, alors il y a puissance 4
	if(c_p4>=4)
	{
		return 1;
	}
	// Sinon on retourne 0
	else
	{
		return 0;
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
