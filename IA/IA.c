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
    int profondeur = jeu->listeJoueur[idIA].niveauIA * jeu->nbJoueur * 3; 
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
            // si l'oya ne possède plus de pièce du type voulu
            if(!t_jeu_oyaPossedePiece(cpjeu, action.typePiece)) {
                continue; // on passe à l'itération suivante
            }
            // on joue le coups, et on récupère le gagnant, ou le code de retour
            gagnant = MOTEUR_tourSuivant(cpjeu, action);
            if(gagnant == -2) // si action non valide
                continue;  // on passe à l'action suivante
            if(gagnant >= 0 && gagnant != idIA)
                priorite = 0; // situation absolument non désirée !
            else if(gagnant >= 0)
                priorite = 100; // situation absolument désirée !
            // si il n'y a aucun gagnant, on appelle minimax
            else {
                // on rappelle l'algorithme minimax, pour la profondeur ciblée
                priorite = IA_alphaBeta(cpjeu, alpha, beta, profondeur, idIA);
                // on prend la plus grande priorité parmis celles proposées
                if(priorite > prioMax) {
                    prioMax = priorite; // nouvelle prioMax
                    // l'action prioritaire est désormais égale à l'action 
                    actionPrio = action;
                    printf("DEBUG: prioMax = %i pour colonne %i\n", prioMax, action.colonne);
                }
                // si c'est la même priorité, ya une chance pour que ça joue plutôt là
                else if(priorite == prioMax && randN(4) == 0) {
                    actionPrio = action;
                }
            }
            //printf("ACT: colonne %d, pièce %d, priorite = %d\n", action.colonne, action.typePiece, priorite);
            // enfin, on déjoue le coups
            if(gagnant >= -1) {
                MOTEUR_annulerDernierCoup(cpjeu);
                gagnant = -2;
            }
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
    // ALPHA-BÊTA
    // si le jeu est une "feuille" de l'arbre
    if(profondeur == 0) {
        return IA_h(jeu, idIA); // renvoit de la priorité
    }
    else {
        // si l'oya est un adversaire (noeud minimal)
        if(jeu->oya != idIA) {
            priorite = 101; // valeur infinie positive
            // PARCOURS des branches de ce noeuds, et appel à alphabeta
            for(action.colonne=0; action.colonne < jeu->nbCaseX; action.colonne++) {
                // pour chaque type de pièce :
                for(action.typePiece = 1; action.typePiece < 4; action.typePiece++){
                    // si l'oya ne possède plus de pièce du type voulu
                    if(!t_jeu_oyaPossedePiece(jeu, action.typePiece)) {
                        continue; // on passe à l'itération suivante
                    }
                    // on joue le coups, et on récupère le gagnant, ou le code de retour
                    gagnant = MOTEUR_tourSuivant(jeu, action);
                    if(gagnant == -2) // si action non valide
                        continue;  // on passe à l'action suivante
                    if(gagnant >= 0 && gagnant != idIA)
                        priorite = 0; // situation absolument non désirée !
                    else if(gagnant >= 0)
                        priorite = 100; // situation absolument désirée !
                    // si il n'y a aucun gagnant, on appelle minimax
                    else {
                        priorite = min(priorite, 
                                IA_alphaBeta(jeu, alpha, beta, profondeur-1, idIA));
                        if(alpha >= priorite)
                            return priorite;
                        beta = min(beta, priorite);
                    }
                    // enfin, on déjoue le coups
                    MOTEUR_tourPrecedent(jeu);
                } // fin bouclage sur action.typePiece
            } // fin bouclage sur action.colonne
        } // si l'oya est l'IA jouée (noeud maximal)
        else {
            priorite = -1; // valeur infinie négative
            // PARCOURS des branches de ce noeuds, et appel à alphabeta
            for(action.colonne=0; action.colonne < jeu->nbCaseX; action.colonne++) {
                // pour chaque type de pièce :
                for(action.typePiece = 1; action.typePiece < 4; action.typePiece++){
                    // si l'oya ne possède plus de pièce du type voulu
                    if(!t_jeu_oyaPossedePiece(jeu, action.typePiece)) {
                        continue; // on passe à l'itération suivante
                    }
                    // on joue le coups, et on récupère le gagnant, ou le code de retour
                    gagnant = MOTEUR_tourSuivant(jeu, action);
                    if(gagnant == -2) // si action non valide
                        continue;  // on passe à l'action suivante
                    if(gagnant >= 0 && gagnant != idIA)
                        priorite = 0; // situation absolument non désirée !
                    else if(gagnant >= 0)
                        priorite = 100; // situation absolument désirée !
                    // si il n'y a aucun gagnant, on appelle minimax
                    else {
                        priorite = max(priorite, IA_alphaBeta(jeu, alpha, beta, 
                                        profondeur-1, idIA));
                        if(priorite >= beta) // coupure de type beta
                            return priorite;
                        alpha = max(alpha, priorite);
                    }
                    // enfin, on déjoue le coups
                    MOTEUR_annulerDernierCoup(jeu);
                } // fin bouclage sur action.typePiece
            } // fin bouclage sur action.colonne
        }
    }
    return priorite;
}

