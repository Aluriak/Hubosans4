#include "IA.h"



/*
 * IA EFFECTUER TOUR
 */
// effectue le tour de jeu du joueur pointé selon le fonctionnement de l'IA
// Les étapes de jeu sont les suivantes : 
// 	- pour chaque colonne, on associe trois priorité entre 0 et 10
// 		- 0 = inutile de jouer ici (rien ne s'y passe)
// 		- 10 = impératif de jouer ici (joueur adverse sur le 
// 			point de mettre un quatrième pion)
// 		- P1 = pour une pièce creuse
// 		- P2 = pour une pièce pleine
// 		- P3 = pour une pièce bloquante
// 	- on identifie le couple (colonne, pion) de plus haute priorité
// 	- on joue à cet endroit
void IA_effectuerTour(t_jeu *jeu, t_joueur* joueur) {
    // calcul des priorites
    it_priorite* priorites = IA_calculPriorites(jeu, joueur);
    // libérations
    free(priorite);
}



/*
 * IA CALCUL PRIORITE
 */
// calcule les priorités des couples (colonne;pion), et les renvois 
// 	sous la forme d'un tableau de t_priorite, 
// 	avec une case pour chaque colonne
t_priorite* IA_calculPriorites(t_jeu* jeu, t_joueur* joueur) {
    // initialisation
    int i = jeu->nbCaseX-1; // nombre de colonnes dans l'itérateur de boucle
    // création du tableau de priorité
    t_priorite* priorites = malloc(jeu->nbCaseX*sizeof(t_priorite));
    // pour chaque colonne
    for(; i >= 0; i--) {
	// on teste pour la pièce creuse
    }
}



/*
 * IA COORD PIECE JOUEE
 */
// renvois la coordonnee y d'une pièce placée dans la colonne. Ou -1 si pièce 
// impossible à mettre (atteinte de la limite haute)
// NB: n'effectue aucune modification du jeu !
int IA_coordPieceJouee(t_jeu* jeu, e_piece piecePlacee, int colonne) {
    // initialisations
    int i = 0; // itérateur de boucle
    int ligne = -1; // ligne où la pièce va se placer
    e_piece pieceCase; // pieces occupant la case étudiée

    // pour chaque case de la colonne, tant que la ligne n'a pas été trouvée
    for(i = jeu->nbCaseY-1; i >= 0 && ligne == -1; i--) {
	pieceCase = jeu->plateau[colonne][i].typePiece;
	// si la pièce de la case étudiée bloque le chemin 
	// 	(pièce bloquante, ou de même type que la pièce placée)
	if(pieceCase == BLOQUANTE 
		|| pieceCase == piecePlacee 
		|| pieceCase = DOUBLE) {
	    // on détermine si on renvois -1 (pas de case précédente), 
	    // 	ou l'id de la case précédente
	    if(i == jeu->nbCaseY-1)	
		i = -1; // arrêt de la boucle;
	    else
		ligne = i+1; 
	}
	// sinon, on avance à la case d'après sans autre artifice
    }
    return ligne;
}



