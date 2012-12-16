#include "IA.h"




/*
 * IA EFFECTUER TOUR
 */
// effectue le tour de jeu de l'oya selon le fonctionnement de l'IA
// s'appuie sur un algorithme minimax, et une heuristique
t_action IA_effectuerTour(t_jeu *jeu) {
    /*// INITIALISATIONS*/
    /*int priorite = -1; // priorite calculée*/
    /*int prioMax = -1; // priorite maximum trouvée, correspondant à la priorité */
    /*//          de l'action actionPrio*/
    /*int profondeur = jeu->listeJoueur[jeu->oya].niveauIA; */
    /*// actions*/
    /*t_action action; // première action à opérer*/
    /*t_action actionPrio; // première action ayant la meilleure priorité*/
    /*// on créé un jeu, copié-collé du précédent.*/
    /*// on travaillera sur cette copie pour éviter de toucher au jeu lui-même*/
    /*t_jeu* cpjeu = t_jeu_copie(jeu);*/
    

    /*// PARCOURS DES BRANCHES DU PREMIER NOEUD, et appel à minimax pour chacune*/
    /*for(action.colonne=0; action.colonne < jeu->nbCaseX; action.colonne++) {*/
        /*// pour chaque type de pièce :*/
        /*for(action.typePiece = 1; action.typePiece < 4; action.typePiece++){*/
            /*// si l'oya ne possède plus de pièce bloquante*/
            /*if(action.typePiece == BLOQUANTE && */
                    /*!t_jeu_oyaPossedePieceBloquante(jeu)) {*/
                /*continue; // on passe à l'itération suivante*/
            /*}*/
            /*// on joue le coups*/
            /*MOTEUR_tourSuivant(jeu, action);*/
            /*// on rappelle l'algorithme minimax, pour la profondeur suivante*/
            /*priorite = IA_minimax(jeu, profondeur-1, */
                                    /*prioMax, &actionPrio, action);*/
            /*// si la priorité étudiée est plus grande*/
            /*if(priorite > prioMax) {*/
                /*prioMax = priorite; // nouvelle prioMax*/
                /*// l'action prioritaire est désormais égale à l'action */
                /*actionPrio = action;*/
            /*}*/
            /*// on déjoue le coups*/
            /*MOTEUR_tourPrecedent(jeu);*/
        /*} // end for each typePiece*/
    /*} // end for each colonne*/

    /*// LIBÉRATIONS*/
    /*t_jeu_free(cpjeu); // plus besoin du jeu*/
    /*// renvoit de l'action*/
    /*return action;*/
}






/*
 * IA ETUDE RECURSIVE
 */
// étudie récursivement le plateau de jeu, et retourne la priorité. 
//      Appel récursif, algorithme minimax employé
// arguments : le jeu, la profondeur a atteindre, la prioMax calculée jusqu'ici,
//      l'action à faire selon l'actuelle meilleure priorité, 
//      et l'action à la base de l'arbre étudié
// les deux actions sont transmises pour enregistrer l'action de l'IA.
int IA_minimax(t_jeu* jeu, int profondeur, int prioMax, 
        t_action *actionPrio, t_action actionEtudiee) {
    /*// INITIALISATIONS*/
    /*t_action action = {0,1}; // action générée*/
    /*int priorite = -1; // priorité du noeud actuel*/
    /*// ALGORITHME MINIMAX*/
    /*// cette fonction traite un noeud, et un seul. Elle s'appelle elle-même pour*/
    /*// explorer les noeuds suivant, ou l'heuristique si la profondeur max est*/
    /*// atteinte. L'algorithme est donc le suivant :*/
    /*// tant qu'on est pas à la profondeur maximum*/
    /*if(profondeur > 0) {*/
        /*// pour chaque colonne possible à ce noeuds : */
        /*for(action.colonne=0; action.colonne < jeu->nbCaseX; action.colonne++) {*/
            /*// pour chaque type de pièce :*/
            /*for(action.typePiece = 1; action.typePiece < 4; action.typePiece++){*/
                /*// si l'oya ne possède plus de pièce bloquante*/
                /*if(action.typePiece == BLOQUANTE && */
                        /*!t_jeu_oyaPossedePieceBloquante(jeu)) {*/
                    /*continue; // on passe à l'itération suivante*/
                /*}*/
                /*// on joue le coups*/
                /*MOTEUR_tourSuivant(jeu, action);*/
                /*// on rappelle l'algorithme minimax, pour la profondeur suivante*/
                /*priorite = IA_minimax(jeu, profondeur-1, */
                                        /*prioMax, actionPrio, actionEtudiee);*/
                /*// si la priorité étudiée est plus grande*/
                /*if(priorite > prioMax) {*/
                    /*prioMax = priorite; // nouvelle prioMax*/
                    /*// l'action prioritaire est désormais l'action étudiée*/
                    /**actionPrio = actionEtudiee;*/
                /*}*/
                /*// on déjoue le coups*/
                /*MOTEUR_tourPrecedent(jeu);*/
            /*} // end for each typePiece*/
        /*} // end for each colonne*/
    /*}*/
    /*// sinon, la profondeur est atteinte : appel de l'heuristique !*/
    /*else {*/
        /*priorite = IA_h(jeu);*/
        /*// si la priorité étudiée est plus grande*/
        /*if(priorite > prioMax) {*/
            /*prioMax = priorite; // nouvelle prioMax*/
            /*// l'action prioritaire est désormais l'action étudiée*/
            /**actionPrio = actionEtudiee;*/
        /*}*/
    /*}*/
    /*return prioMax;*/
}




