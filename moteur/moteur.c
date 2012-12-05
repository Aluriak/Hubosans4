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
t_joueur* MOTEUR_tourSuivant(t_jeu* jeu, t_action action) {
    //int i = 0; //itérateur de boucle
    //si le type de pièce de l'action est VIDE, alors on considère que 
    //	l'utilisateur à voulut sauvegarder la partie.
    //	la colonne correspond au slot de sauvegarde
    //	nom d'un slot : saveN.sv (avec N le numéro de slot)

    // On s'occupe des sauvegardes
    /*
    FILE * file_save;
    if(action.typePiece == VIDE) { // action.typePiece est NULL, donc sauvegarde
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
    }
    // sinon, c'est une pièce à jouer
    else {*/
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
		// L'oya est mis au joueur suivant
		t_jeu_joueurSuivant(jeu);
		}	
    //}
    //if(test_puissance4==OK)
    //{
    //	return joueur_gagnant;
    //}
    //else
    //{
    	return NULL;
      //}
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
 * MOTEUR BORNE MAX MIN
 *
// Détermine pour une case reçu en paramètre, la valeur MAX (3) ou
// la valeur MIN (MAX-X) de celle-ci, représentant ainsi la 
// distance la séparant des bordures de la matrice
int MOTEUR_borne_MAX_MIN(t_jeu* jeu, t_action action, int ligne)
{
	
}*/

/*
 * MOTEUR TEST PUISSANCE 4
 */
//renvois si le joueur en courant vient de faire un puissance 4.
//Reçois en paramètre :
//	- le jeu
//	- l'action en cours
//	- la ligne de l'action en cours
int MOTEUR_test_puissance4(t_jeu* jeu, t_action action, int ligne)
{
	int oya=jeu->oya;
	int i,j; // Itérateur de boucle
	int c_p4=1; // Compteur pour le puissance 4, si c_p4 >= 4, alors il y a puissance 4
	int no_p4=0; // Booléen qui permet de sortir de la boucle en cas de non puissance 4
	while(c_p4<4 || no_p4==0)
	{
		// >>> TEST BAS-HAUT <<<
		i=action.colonne; // Pour un traitement correct des conditions
		// On part de la case courante -3 jusqu'à la case courante + 3
		for(j=ligne-3;j<ligne+3;j++)
		{
			// Si la piece courante à le même id que le joueur courant, alors on incrémente 
			if(jeu->plateau[j][i].joueurPieceCreuse == oya ||
		   	   jeu->plateau[j][i].joueurPiecePleine == oya)
			{
				c_p4++;
			}
			// Si on sort du if, c'est qu'il y a une coupure entre deux piece de même type (elles ne se suivent pas)
			else
			{
				c_p4=0; // On recommence le décompte à zéro
			}
		}
		// Avant de changer de type de test on remet les compteurs à zéro
		c_p4=0;
		// >>> TEST GAUCHE-DROITE <<<
		//On part de la case courante -3 jusqu'à la case courante +3
		for(i=action.colonne-3;i<action.colonne+3;i++)
		{
			// Si la piece courante à le même id que le joueur courant, alors on incrémente
			if(jeu->plateau[j][i].joueurPieceCreuse == oya ||
			   jeu->plateau[j][i].joueurPiecePleine == oya)
			{
				c_p4++;
			}
			else
			{
				c_p4=0; // On recommence le décompte à zéro
			}
		}
		// Avant de changer de type de test on remet les compteurs à zéro
		c_p4=0;
		// >>> TEST DIAG BasDroit->HautGauche <<<
		//On part de la case courante +3 jusqu'à la case courante -3 pour les colonnes
		for(i=action.colonne+3;i>action.colonne-3;i--)
		{
			// On part de la case courante -3 jusqu'à la case courante +3 pour les lignes
			for(j=ligne-3;j<ligne+3;j++)
			{
				if(jeu->plateau[j][i].joueurPieceCreuse == oya ||
				   jeu->plateau[j][i].joueurPiecePleine == oya)
				{
					c_p4++;
				}
				else
				{
					c_p4=0; // On recommence le décompte à zéro
				}
			}
		}
		// Avant de changer de type de test, on remet le compteurs à zéro
		c_p4=0;
		// >>> TEST DIAG BasGauche->HautDroit <<<
		// On part de la case courante -3 jusqu'à la case courante +3 pour les colonnes
		for(i=action.colonne-3;i<action.colonne+3;i++)
		{
			// On part de la case courante -3 jusqu'à la case courante +3 pour les lignes
			for(j=ligne-3;j>ligne+3;j++)
			{
				if(jeu->plateau[j][i].joueurPieceCreuse == oya ||
				   jeu->plateau[j][i].joueurPieceCreuse == oya)
				{
				   	c_p4++;
				}
				else
				{
					c_p4=0; // On recommence le décompte à zéro
				}
			}
		}
		// Tout les test on été effectués, sans puissance 4.
		// On passe donc le bool no_p4 à 1 afin de sortir de la boucle
		no_p4=1;
	}
	// Une fois sortie de la boucle, on vérifie quelle condition nous en a fait sortir
	if(c_p4>=4)
	{
		return 1; // il y a puissance 4
	}
	else
	{
		return 0; // il n'y a pas puissance 4
	}
}

/*
 * MOTEUR TEST COND PUISSANCE 4
 *
// Appellée par MOTEUR TEST PUISSANCE 4, elle effectue les test sur une case données
// Si 
int MOTEUR_test_cond_puissance_4()
{
		
}*/
