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
// 	- on créé la structure t_action désirée, et on la retourne
t_action IA_effectuerTour(t_jeu *jeu, t_joueur* joueur) {
    // initialisations
    int i = 0; // itérateurs de boucle
    int prioMax = 0, inter; // priorité maximum et intermédiaire de traitement
    t_action action = {-1, -1}; // action à opérer
    //int prevision = jeu->niveauIA; // nombre de tours vus à l'avance
    // calcul des priorites
    t_priorite* priorites = IA_calculPriorites(jeu, joueur);

    // on recherche la plus haute priorité parmis la table de priorités
    prioMax = prio_max(priorites[0]);
    for(i = 1; i < jeu->nbCaseX; i++) {
	inter = prio_max(priorites[i]);
	if(inter > prioMax)
	    prioMax = inter;
    }
    // on a la priorité maximum. On vas donc retrouver cette priorité
    // 	dans la liste des priorités pour identifier ce qu'il faut jouer

    // pour chaque colonne (on arrête quand on a trouvé une action)
    for(i = 0; i < jeu->nbCaseX && action.colonne != -1; i++) {
	// si la priorité maximum trouvée est dans cette colonne
	if(prio_max(priorites[i]) == prioMax) {
	    // on cherche pour quelle pièce elle est maximum
	    // Si maximum pour bloquante ET que 
	    // 	l'IA possède encore des pièces bloquantes
	    // 	l'IA n'est pas suffisemment intrépide 
	    // 		pour utiliser une pièce bloquante 
	    if(priorites[i].bloquante == prioMax 
		    && joueur->nbPieceBloquante > 0
		    && randN(joueur->intrepidite) == 0
		    ) 
		action.typePiece = BLOQUANTE;
	    // sinon, pour pièce creuse
	    else if(priorites[i].creuse == prioMax) 
		action.typePiece = CREUSE;
	    // sinon, pour pièce pleine
	    else
		action.typePiece = PLEINE;
	    // enfin, on définit la colonne où doit être lâchée la pièce
	    action.colonne = i;
	}
    }

    // en cas d'action non trouvée
    if(action.colonne == -1) {
	FLUX_ERREUR("IA", 
		"L'IA a rencontré une configuration de jeu inattendue");
	// action totalement aléatoire
	action.colonne = randN(jeu->nbCaseX);
	if(randN(1))
	    action.typePiece = CREUSE;
	else
	    action.typePiece = PLEINE;
    }

    // libérations
    free(priorites);
    // renvoit de l'action
    return action;
}



