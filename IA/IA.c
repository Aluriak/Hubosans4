#include "IA.h"




/*
 * IA EFFECTUER TOUR
 */
// effectue le tour de jeu de l'oya selon le fonctionnement de l'IA
// s'appuie sur un algorithme minimax, et une heuristique
t_action IA_effectuerTour(t_jeu *jeu) {
    // INITIALISATIONS
    int idIA = jeu->oya; // id du joueur joué par l'IA
    int prioMax = -1; // priorite maximum trouvée, correspondant à la priorité 
    //          de l'action actionPrio
    int alpha = -1, beta = 101;
    int profondeur = jeu->listeJoueur[idIA].niveauIA * jeu->nbJoueur * 5; 
    int gagnant = -1; // gagnant de la partie
    // actions
    t_action action; // première action à opérer
    t_action actionPrio; // action ayant la meilleure priorité
    // on créer un jeu, copié-collé du précédent.
    // on travaillera sur cette copie pour éviter de toucher au jeu lui-même
    t_jeu* cpjeu = t_jeu_copie(jeu);

    // PARCOURS DES BRANCHES DU PREMIER NOEUD, et appel à minimax pour chacune
    for(action.colonne=0; action.colonne < cpjeu->nbCaseX; action.colonne++) {
        // pour chaque type de pièce :
        for(action.typePiece = 1; action.typePiece < 4; action.typePiece++){
            // si l'oya possède une pièce du type voulu
            if(t_jeu_oyaPossedePiece(cpjeu, action.typePiece)) {
                // on joue le coups, et on récupère le gagnant, ou le code de retour
                gagnant = MOTEUR_tourSuivant(cpjeu, action);
                if(gagnant >= -1) { // si action valide
                        printf("gagnant = %i\n", gagnant);
                        // on déjoue le coups
                        MOTEUR_annulerDernierCoup(cpjeu);
                        // si le gagnant est l'IA
                        if(gagnant == idIA) {
                            // on choisis cette action comme prioritaire !
                            if(prioMax == 100 && randN(3) == 0)
                                actionPrio = action;
                            else if(prioMax != 100)
                                actionPrio = action;
                            prioMax = 100;
                        }
                        // si il n'y a aucun gagnant, on appelle alpha-bêta
                        else if(gagnant == -1) {
                            // appel de alpha-bêta, avec alpha et beta négatifs et inversés
                            //int score = IA_alphaBeta(cpjeu, alpha, beta,
                            int score = -IA_alphaBeta(cpjeu, -beta, -alpha,
                                    profondeur, idIA);
                                printf("score = %i\n", score);
                            if(score > prioMax) {
                                prioMax = score;
                                actionPrio = action;
                                printf("prioMax = %i\n", prioMax);
                            }
                        }
                } // end coup valide
            } // si pas de pièce dispo, pas de jeu !
        } // end for each typePiece
    } // end for each colonne

    // LIBÉRATIONS
    t_jeu_free(cpjeu); // plus besoin du jeu
    // renvoit de l'action
    return actionPrio;
}



/*
 * IA ALPHA BETA
 */
// étudie récursivement le plateau de jeu, et retourne la priorité du jeu actuel 
//      suite à une étude sur la profondeur indiquée.
//      Appel récursif, algorithme minimax employé avec élagage alpha-bêta.
// arguments : le jeu, la profondeur a atteindre, l'id du joueur joué par l'IA,
//      la prioMax calculée jusqu'ici,
int IA_alphaBeta(t_jeu* jeu, int alpha, int beta, int profondeur, int idIA) {
    // INITIALISATIONS
    t_action action; // action utilisée dans les boucles
    // TRAITEMENTS
    if(profondeur == 0)
        return IA_h(jeu, idIA);
    else {
        // pour chaque coup possible
        // pour chaque colonne
        for(action.colonne=0; action.colonne < jeu->nbCaseX; action.colonne++) {
            // pour chaque type de pièce :
            for(action.typePiece = 1; action.typePiece < 4; action.typePiece++){
                // si la pièce est possédée
                if(!t_jeu_oyaPossedePiece(jeu, action.typePiece)) {
                    // on joue le coups, et on récupère le gagnant, ou le code de retour
                    int gagnant = MOTEUR_tourSuivant(jeu, action);
                    if(gagnant == -1) { // si jeu continu normalement
                        int score = -IA_alphaBeta(jeu, -beta, -alpha, profondeur-1, idIA);
                        MOTEUR_annulerDernierCoup(jeu); // annulation du coup précédent
		        if (score >= alpha) {
                            alpha = score;
                            if(alpha >= beta)
			        break;
		        }
                    }
                    /*// sinon, si ya un gagnant*/
                    /*else if(gagnant >= 0) {*/
                        /*MOTEUR_annulerDernierCoup(jeu); // annulation du coup précédent*/
                        /*// si c'est l'IA qui gagne*/
                        /*if(gagnant == idIA) */
                            /*return 91+profondeur; // retour d'une haute priorité, */
                            /*// plus haute si plus proche du noeud étudié*/
                        /*else // autre joueur gagnant*/
                            /*return 0; // situation non désirée !*/
                    /*}// sinon, ya eu un problème, on passe à la suite sans traitement*/
                } // pas de pièce dispo, on arrêta là pour cette pièce

            } // end boucle piece
        } // end boucle colonne
    }
    return alpha;
} // end alpha-bêta







