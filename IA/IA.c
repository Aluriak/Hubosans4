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
    t_priorite* priorites = IA_calculPriorites(jeu, joueur);
    // libérations
    free(priorites);
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
    int y = -1; // coordonnée y de la pièce étudiée 
    // création du tableau de priorité
    t_priorite* priorites = malloc(jeu->nbCaseX*sizeof(t_priorite));
    // pour chaque colonne
    for(; i >= 0; i--) {
	// on teste pour la pièce creuse
	// récupération de la coordonnée d'une pièce creuse lâchée en colonne i
	y = IA_coordPieceJouee(jeu, CREUSE, i);
	// étude de la priorite en (i;y)
	priorites[i].creuse = IA_etudePriorite(jeu, joueur, i, y);
    }
    return priorites;
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
		|| pieceCase == DOUBLE) {
	    // on détermine si on renvois -1 (pas de case précédente), 
	    // 	ou l'id de la case précédente
	    if(i == (jeu->nbCaseY-1))	
		i = -1; // arrêt de la boucle;
	    else
		ligne = i+1; 
	}
	// sinon, on avance à la case d'après sans autre artifice
    }
    return ligne;
}



/*
 * IA ETUDE PRIORITE
 */
// renvois la priorité à jouer dans la case (x;y) pour le joueur pointé.
// la priorité est une valeur entre 0 (inutile) et 10 (prioritaire)
// 	- ce joueur peut mettre une pièce ici pour gagner : 10
// 	- un autre joueur peut mettre une pièce ici pour gagner : 9
// 	- un autre joueur peut mettre une troisième pièce d'affilée : 6
int IA_etudePriorite(t_jeu* jeu, t_joueur* joueur, int x, int y) {
    // initialisation
    int priorite = 0; // priorité finale
    int j = 0; // itérateur de boucle
    int prioHorizontale = 0, prioDiag = 0; // variable de traitement
    // tableau contenant les priorités de chacun des joueurs
    int* prioriteJoueur = malloc(jeu->nbJoueur*sizeof(int));

    // ÉTUDE DE LA PRIORITE GLOBALE
    // la priorité d'une case est calculée comme suit :
    // 	- pour chaque joueur : 	on détermine la priorité de cette case, 
    // 		suivant le nombre de pièces déjà bien placées. 
    // 		Si il y en a trois, cela veut dire que placer une pièce 
    // 		dans la case étudiée permet de réaliser un puissance 4.
    // 		On estime ainsi la droite horizontale, et les deux diagonales, 
    // 		et l'on prend la plus haute de ces priorités.
    // 	- on prend la priorité maximale parmis toutes ces priorités

    // pour chaque joueur
    for(j = jeu->nbJoueur-1; j >= 0; j--) {
	// ligne horizontale
	prioHorizontale = IA_calculPriorite_horizontal(jeu, x, y);
	// diagonales
	prioDiag = IA_calculPriorite_diag(jeu, x, y);
	// maximum
	prioriteJoueur[j] = max(prioHorizontale,prioDiag);
	// si le joueur j est aussi l'IA actuellement traitée
	if(&(jeu->listeJoueur[j]) == joueur)
	    prioriteJoueur[j]++;
    }

    // on prend le maximum du tableau
    priorite = tab_max(prioriteJoueur, jeu->nbJoueur);

    // libérations
    free(prioriteJoueur);
    // return
    return priorite;
}




/*
 * IA CALCUL PRIORITE HORIZONTAL
 */
// calcul la priorité pour la droite horizontale à la case (x;y)
int IA_calculPriorite_horizontal(t_jeu *jeu, int x, int y) {
    // initialisation
    int priorite = 0; // priorité de la case
    int i = 0, j = 0; // itérateurs de boucle
    int nbPieceAlignee; // stock le nombre de pièces alignées et contiguees
    short id1, id2; // id des joueurs contrôlant la case étudiée
    coord min, max; // coordonnées des cases en bout de ligne à tester

    // on détermine l'intervalle de cases à étudier
    min.x = x-3;
	if(min.x < 0) min.x = 0;
    min.y = y;
    max.x = x+3;
	if(max.x > (jeu->nbCaseX-1)) max.x = jeu->nbCaseX-1;
    max.y = y;
    
    // PARCOURS DES CASES
    
    // cases de gauche : de (x;y) à (min.x;y)
    id1 = jeu->plateau[x][y].joueurPieceCreuse;
    id2 = jeu->plateau[x][y].joueurPiecePleine;
    // tant que la case lue porte au moins une pièce du joueur considéré
    for(i = 1; x-i >= min.x && (id1 == j+1 || id2 == j+1); i++) {
	id1 = jeu->plateau[x-i][y].joueurPieceCreuse;
	id2 = jeu->plateau[x-i][y].joueurPiecePleine;
    }
    // arrivé ici, x-i est l'id de la première case que le joueur 
    // 	ne contrôle pas. 
    // 	Donc i-1 donne le nombre de cases contrôlées par le joueur.
    nbPieceAlignee = i-1;
    
    // cases de droite : de (x;y) à (max.x;y)
    id1 = jeu->plateau[x][y].joueurPieceCreuse;
    id2 = jeu->plateau[x][y].joueurPiecePleine;
    // tant que la case lue porte au moins une pièce du joueur considéré
    for(i = 1; x+i >= max.x && (id1 == j+1 || id2 == j+1); i++) {
	id1 = jeu->plateau[x+i][y].joueurPieceCreuse;
	id2 = jeu->plateau[x+i][y].joueurPiecePleine;
    }
    // arrivé ici, x-i est l'id de la première case que le joueur 
    // 	ne contrôle pas. 
    // 	Donc i-1 donne le nombre de cases contrôlées par le joueur.
    nbPieceAlignee += i-1;
    
    // le nombre de pièces alignées donne immédiatement la priorité
    // En effet, si trois pièces sont alignées, un puissance 4 
    // 	peut-être effectué par le joueur à son prochain tour. 
    // 	La priorité est donc de 9, ou 10 si ce joueur est l'IA 
    // 	actuellement traitée.
    if(nbPieceAlignee == 3) {
	priorite = 9;
    }
    // Si deux pièces sont alignées, c'est intéressant : priorité à 6 (ou 7)
    else if(nbPieceAlignee == 2) {
	priorite = 6;
    }
    // Si il n'y a qu'une pièce, c'est moins intéressant encore : 2 (ou 3)
    else if(nbPieceAlignee == 1) {
	priorite = 2;
    }
    // dans tous les autres cas, on s'en fiche
    // 	(oui, même dans le cas impossible où il y a 4 pièces. (le jeu s'arrête 
    // 		au puissance 4, normalement) )
    else 
	priorite = 0;

    // renvoit de la priorité
    return priorite;
}






/*
 * IA CALCUL PRIORITE DIAGONALE 
 */
// calcule la priorité pour les diagonales de la case (x;y)
int IA_calculPriorite_diag(t_jeu *jeu, int x, int y) {
    // initialisation
    int priorite1 = 0, priorite2 = 0; // priorités des diagonales
    coord coordPionMin, coordPionMax; // coordonnées des cases en bout de ligne à tester

    // on détercoordPionMine l'intervalle de cases à étudier
    // première diagonale
    coordPionMin.x = x-3;
	if(coordPionMin.x < 0) coordPionMin.x = 0;
    coordPionMin.y = y-3;
	if(coordPionMin.y < 0) coordPionMin.y = 0;
    coordPionMax.x = x+3;
	if(coordPionMax.x > (jeu->nbCaseX-1)) coordPionMax.x = jeu->nbCaseX-1;
    coordPionMax.y = y+3;
	if(coordPionMax.y > (jeu->nbCaseY-1)) coordPionMax.y = jeu->nbCaseY-1;
    // récupération de la priorité pour cette configuration
    priorite1 = IA_calculPriorite_diag_traitement(jeu, x, y, 
	    coordPionMin, coordPionMax);


    // seconde diagonale
    coordPionMin.x = x-3;
	if(coordPionMin.x < 0) coordPionMin.x = 0;
    coordPionMin.y = y+3;
	if(coordPionMin.y > (jeu->nbCaseY-1)) coordPionMin.y = jeu->nbCaseY-1;
    coordPionMax.x = x+3;
	if(coordPionMax.x > (jeu->nbCaseX-1)) coordPionMax.x = jeu->nbCaseX-1;
    coordPionMax.y = y-3;
	if(coordPionMax.y < 0) coordPionMax.y = 0;
    priorite2 = IA_calculPriorite_diag_traitement(jeu, x, y, 
	    coordPionMin, coordPionMax);


    return max(priorite1, priorite2);
}





/*
 * IA CALCUL PRIORITE DIAG TRAITEMENT
 */
// sous traitement de IA_calculPriorite_diag(3) : opère tous les calculs 
// 	selon l'intervalle de case à étudier
int IA_calculPriorite_diag_traitement(t_jeu* jeu, 
	int x, int y, coord min, coord max) {
    // initialisation
    int priorite = 0; // priorité de la case
    int i = 0, j = 0; // itérateurs de boucle
    int nbPieceAlignee; // stock le nombre de pièces alignées et contiguees
    short id1, id2; // id des joueurs contrôlant la case étudiée

    // PARCOURS DES CASES

    // cases de gauche : de (x;y) à (min.x;y)
    id1 = jeu->plateau[x][y].joueurPieceCreuse;
    id2 = jeu->plateau[x][y].joueurPiecePleine;
    // tant que la case lue porte au moins une pièce du joueur considéré
    for(i = 1; y-i >= max.y && x-i >= min.x && 
	    (id1 == j+1 || id2 == j+1); i++) {
	id1 = jeu->plateau[x-i][y-i].joueurPieceCreuse;
	id2 = jeu->plateau[x-i][y-i].joueurPiecePleine;
    }
    // arrivé ici, x-i est l'id de la première case que le joueur 
    // 	ne contrôle pas. 
    // 	Donc i-1 donne le nombre de cases contrôlées par le joueur.
    nbPieceAlignee = i-1;
    
    // cases de droite : de (x;y) à (max.x;y)
    id1 = jeu->plateau[x][y].joueurPieceCreuse;
    id2 = jeu->plateau[x][y].joueurPiecePleine;
    // tant que la case lue porte au moins une pièce du joueur considéré
    for(i = 1; y+i >= max.y && x+i >= min.x && 
	    (id1 == j+1 || id2 == j+1); i++) {
	id1 = jeu->plateau[x+i][y+i].joueurPieceCreuse;
	id2 = jeu->plateau[x+i][y+i].joueurPiecePleine;
    }
    // arrivé ici, x-i est l'id de la première case que le joueur 
    // 	ne contrôle pas. 
    // 	Donc i-1 donne le nombre de cases contrôlées par le joueur.
    nbPieceAlignee += i-1;
    
    // le nombre de pièces alignées donne immédiatement la priorité
    // En effet, si trois pièces sont alignées, un puissance 4 
    // 	peut-être effectué par le joueur à son prochain tour. 
    // 	La priorité est donc de 9, ou 10 si ce joueur est l'IA 
    // 	actuellement traitée.
    if(nbPieceAlignee == 3) {
	priorite = 9;
    }
    // Si deux pièces sont alignées, c'est intéressant : priorité à 6 (ou 7)
    else if(nbPieceAlignee == 2) {
	priorite = 6;
    }
    // Si il n'y a qu'une pièce, c'est moins intéressant encore : 2 (ou 3)
    else if(nbPieceAlignee == 1) {
	priorite = 2;
    }
    // dans tous les autres cas, on s'en fiche
    // 	(oui, même dans le cas impossible où il y a 4 pièces. (le jeu s'arrête 
    // 		au puissance 4, normalement) )
    else 
	priorite = 0;

    // revoit de la priorité
    return priorite;
}




