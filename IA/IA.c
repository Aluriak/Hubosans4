#include "IA.h"




/*
 * IA EFFECTUER TOUR
 */
// effectue le tour de jeu de l'oya selon le fonctionnement de l'IA
// s'appuie sur un algorithme minimax, et une heuristique
t_action IA_effectuerTour(t_jeu *jeu) {
    // INITIALISATIONS
    int idIA = jeu->oya; // id du joueur joué par l'IA
    int priorite = -1; // priorite calculée
    int prioMax = -1; // priorite maximum trouvée, correspondant à la priorité 
    //          de l'action actionPrio
    int alpha = 0, beta = 100;
    int profondeur = jeu->listeJoueur[idIA].niveauIA * jeu->nbJoueur * 100; 
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
                    printf("%i\t", gagnant);
                        // s'il y a un gagnant, différent de l'IA
                        if(gagnant >= 0 && gagnant != idIA)
                            priorite = 0; // situation absolument non désirée !
                        else if(gagnant == idIA) {
                            priorite = 100; // situation absolument désirée !
                            // on choisis cette action !
                            if(prioMax == 100 && randN(3) == 0)
                                actionPrio = action;
                            else if(prioMax != 100)
                                actionPrio = action;
                            prioMax = 100;
                        }
                        // si il n'y a aucun gagnant, on appelle minimax
                        else {
                            // appel de alpha-bêta, avec alpha et beta négatifs et inversés
                            priorite = IA_alphaBeta(cpjeu, alpha, beta,
                                    profondeur, idIA);
                            if(priorite > prioMax) {
                                prioMax = priorite;
                                actionPrio = action;
                                printf("prioMax = %i\n", prioMax);
                            }
                            // si prio égales, des chances existent pour que l'IA joue
                            //  à ce nouvel endroit
                            /*else if(priorite == prioMax && randN(3) == 0)*/
                                /*actionPrio = action;*/
                        }
                        // enfin, on déjoue le coups
                        MOTEUR_annulerDernierCoup(cpjeu);
                }
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
    int priorite = -1; // priorité du jeu
    t_action action;
    int gagnant = -1;
    int prioMax = 0;
    // ALPHA-BÊTA
    // si le jeu est une "feuille" de l'arbre
    if(profondeur == 0) {
        return IA_h(jeu, idIA); // renvoit de la priorité
    }
    else {
        prioMax = -1; // valeur infinie négative
        // PARCOURS des branches de ce noeuds, et appel à alphabeta
        for(action.colonne=0; action.colonne < jeu->nbCaseX; action.colonne++) {
            // pour chaque type de pièce :
            for(action.typePiece = 1; action.typePiece < 4; action.typePiece++){
                // si l'oya ne possède plus de pièce du type voulu
                if(!t_jeu_oyaPossedePiece(jeu, action.typePiece)) {
                    // on joue le coups, et on récupère le gagnant, ou le code de retour
                    gagnant = MOTEUR_tourSuivant(jeu, action);
                    if(gagnant >= -1) { // si action valide
                            if(gagnant >= 0 && gagnant != idIA) {
                                MOTEUR_annulerDernierCoup(jeu);
                                return 0; // situation absolument non désirée !
                            }
                            else if(gagnant == idIA) {
                                MOTEUR_annulerDernierCoup(jeu);
                                return 91+profondeur; // situation absolument 
                                //      désirée, pondérée par la distance au noeud actuel
                            }
                            // si il n'y a aucun gagnant, on appelle alpha-bêta
                            else {
                                // appel de alpha-bêta, 
                                //      avec alpha et beta négatifs et inversés
                                priorite = -IA_alphaBeta(jeu, -beta, -alpha, 
                                            profondeur-1, idIA);
                                if(priorite > prioMax) {
                                    prioMax = priorite;
                                    if(prioMax > alpha) {
                                        alpha = prioMax;
                                        if(alpha >= beta) {
                                            MOTEUR_annulerDernierCoup(jeu);
                                            return prioMax;
                                        }
                                    }
                                }
                            }
                            // on enlève le coup joué
                            MOTEUR_annulerDernierCoup(jeu);
                    } // action valide
                } // possède piece
            } // parcours typepiece
        } // parcours colonne
        return prioMax;
    }
}





