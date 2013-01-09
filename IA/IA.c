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
    int profondeur = jeu->listeJoueur[idIA].niveauIA * jeu->nbJoueur; 
    int alpha = -1000, beta = 1000; // alpha et bêta initialisés à - inf et +inf
    int gagnant = -1; // gagnant de la partie
    // actions
    t_action action; // première action à opérer
    t_action actionPrio = {4, 1}; // action ayant la meilleure priorité
    // on créer un jeu, copié-collé du précédent.
    // on travaillera sur cette copie pour éviter de toucher au jeu lui-même
    //jeu = t_jeu_copie(jeu); // on perd le pointeur vers le jeu originel, dont on n'a plus
        // besoin

    // PARCOURS DES BRANCHES DU PREMIER NOEUD, et appel à minimax pour chacune
    for(action.colonne=0; action.colonne < jeu->nbCaseX; action.colonne++) {
        // pour chaque type de pièce :
        for(action.typePiece = 1; action.typePiece < 4; action.typePiece++){
            // si l'oya possède une pièce du type voulu
            if(t_jeu_oyaPossedePiece(jeu, action.typePiece)) {
                // on joue le coups, et on récupère le gagnant, ou le code de retour
                gagnant = MOTEUR_tourSuivant(jeu, action);
                if(gagnant >= -1 && gagnant < jeu->nbJoueur) { // si action valide
                        printf("gagnant = %i\n", gagnant);
                        // on déjoue le coups
                        MOTEUR_annulerDernierCoup(jeu);
                        // si le gagnant est l'IA
                        if(gagnant == idIA) {
                            // on choisis cette action comme prioritaire !
                            // si on avais déjà une action aussi prioritaire, 
                            //  1 chance sur trois pour que l'IA effectue la nouvelle 
                            //  plutôt que celle qu'elle avait déjà calculé
                            if(prioMax == 100 && randN(3) == 0)
                                actionPrio = action;
                            else if(prioMax != 100)
                                actionPrio = action;
                            prioMax = 100;
                            printf("gagnant direct avec colonne = %i et pièce %i\n", action.colonne, action.typePiece);
                        }
                        // si il n'y a aucun gagnant, on appelle alpha-bêta
                        else if(gagnant == -1) {
                            // appel de alpha-bêta, avec alpha et beta négatifs et inversés
                            int score = IA_alphaBeta(jeu, alpha, beta, profondeur, idIA);
                                printf("score = %i\n", score);
                            if(score >= prioMax) {
                                prioMax = score;
                                actionPrio = action;
                                printf("prioMax = %i pour action (%i;%i)\n", prioMax, actionPrio.colonne, actionPrio.typePiece);
                            }
                        }
                } // end coup valide
                else // DEBUG
                    printf("PLOUF\n");
            } // si pas de pièce dispo, pas de jeu !
        } // end for each typePiece
    } // end for each colonne

    // LIBÉRATIONS
    //t_jeu_free(jeu); // plus besoin du jeu
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
    int score, gagnant; // score renvoyé récursivement et valeur de retour du moteur
    // TRAITEMENTS
    if(profondeur <= 0)
        return IA_h(jeu, idIA);
    else {
        // si noeud min
        if(jeu->oya != idIA) {
            score = 1000; // score infini
            // pour chaque coup possible
            // pour chaque colonne
            for(action.colonne=0; action.colonne < jeu->nbCaseX; action.colonne++) {
                // pour chaque type de pièce :
                for(action.typePiece = 1; action.typePiece < 4; action.typePiece++){

                    // si la pièce est possédée
                    if(t_jeu_oyaPossedePiece(jeu, action.typePiece)) {
                        // on joue le coups et récupère le gagnant, ou le code de retour
                        gagnant = MOTEUR_tourSuivant(jeu, action);
                        // si jeu continu normalement
                        if(gagnant >= -1 && gagnant < jeu->nbJoueur) { 
                            score = min(score, IA_alphaBeta(jeu, alpha, beta, 
                                            profondeur-1, idIA));
                            // annulation du coup précédent
                            MOTEUR_annulerDernierCoup(jeu); 
		            if(alpha >= score) // coupure alpha
                                return score;
                            beta = min(beta, score);
                        }
                        // sinon, si ya un gagnant (qui est forcément l'adversaire
                        else if(gagnant >= 0 && gagnant < jeu->nbJoueur) {
                            MOTEUR_annulerDernierCoup(jeu); // annulation du coup précédent
                            return 0; // situation non désirée !
                        }// sinon, ya eu un problème, on passe à la suite sans traitement
                    } // pas de pièce dispo, on arrêta là pour cette pièce

                } // end boucle piece
            } // end boucle colonne
        }
        // si noeud max
        else if(jeu->oya == idIA) {
            score = -1000; // score -infini
            // pour chaque coup possible
            // pour chaque colonne
            for(action.colonne=0; action.colonne < jeu->nbCaseX; action.colonne++) {
                // pour chaque type de pièce :
                for(action.typePiece = 1; action.typePiece < 4; action.typePiece++){

                    // si la pièce est possédée
                    if(t_jeu_oyaPossedePiece(jeu, action.typePiece)) {
                        // on joue le coups et récupère le gagnant, ou le code de retour
                        gagnant = MOTEUR_tourSuivant(jeu, action);
                        // si jeu continu normalement
                        if(gagnant >= -1 && gagnant < jeu->nbJoueur) { 
                            score = max(score, IA_alphaBeta(jeu, alpha, beta, 
                                            profondeur-1, idIA));
                            // annulation du coup précédent
                            MOTEUR_annulerDernierCoup(jeu); 
		            if(score >= beta) // coupure beta
                                return score;
                            alpha = max(alpha, score);
                        }
                        // sinon, si ya un gagnant (qui est forcément l'IA)
                        else if(gagnant >= 0 && gagnant < jeu->nbJoueur) {
                            MOTEUR_annulerDernierCoup(jeu); // annulation du coup précédent
                            return 90; // situation désirée !
                        }// sinon, ya eu un problème, on passe à la suite sans traitement
                    } // pas de pièce dispo, on arrêta là pour cette pièce

                } // end boucle piece
            } // end boucle colonne
        }
        return score;
    } // fin si jeu pas une feuille
} // end alpha-bêta





