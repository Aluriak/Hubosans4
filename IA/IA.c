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
    int profondeur = jeu->listeJoueur[idIA].niveauIA * jeu->nbJoueur; 
    int gagnant = -1; // gagnant de la partie
    // actions
    t_action action; // première action à opérer
    t_action actionPrio; // première action ayant la meilleure priorité
    // on créé un jeu, copié-collé du précédent.
    // on travaillera sur cette copie pour éviter de toucher au jeu lui-même
    t_jeu* cpjeu = t_jeu_copie(jeu);

    // PARCOURS DES BRANCHES DU PREMIER NOEUD, et appel à minimax pour chacune
    for(action.colonne=0; action.colonne < jeu->nbCaseX; action.colonne++) {
        // pour chaque type de pièce :
        for(action.typePiece = 1; action.typePiece < 4; action.typePiece++){
            // si l'oya ne possède plus de pièce du type voulu
            if(!t_jeu_oyaPossedePiece(jeu, action.typePiece)) {
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
                priorite = IA_minimax(cpjeu, profondeur, prioMax, idIA);
                // on prend la plus grande priorité parmis celles proposées
                if(priorite > prioMax) {
                    prioMax = priorite; // nouvelle prioMax
                    // l'action prioritaire est désormais égale à l'action 
                    actionPrio = action;
                }
            }
            //printf("ACT: colonne %d, pièce %d, priorite = %d\n", action.colonne, action.typePiece, priorite);
            // enfin, on déjoue le coups
            MOTEUR_tourPrecedent(cpjeu);
        } // end for each typePiece
    } // end for each colonne

    // LIBÉRATIONS
    t_jeu_free(cpjeu); // plus besoin du jeu
    // renvoit de l'action
    return actionPrio;
}






/*
 * IA MINIMAX
 */
// étudie récursivement le plateau de jeu, et retourne la priorité du jeu actuel 
//      suite à une étude sur la profondeur indiquée.
//      Appel récursif, algorithme minimax employé
// arguments : le jeu, la profondeur a atteindre, l'id du joueur joué par l'IA,
//      la prioMax calculée jusqu'ici,
int IA_minimax(t_jeu* jeu, int profondeur, int idIA, int prioMax) {
    // INITIALISATIONS
    t_action action = {0,1}; // action générée
    int gagnant = -1; // gagnant du jeu
    int priorite = -1; // priorité du noeud actuel
    // ALGORITHME MINIMAX
    // cette fonction traite un noeud, et un seul. Elle s'appelle elle-même pour
    // explorer les noeuds suivant, ou l'heuristique si la profondeur max est
    // atteinte. L'algorithme est donc le suivant :
    // tant qu'on est pas à la profondeur maximum
    if(profondeur > 0) {
    // pour chaque colonne possible à ce noeuds : 
    for(action.colonne=0; action.colonne < jeu->nbCaseX; action.colonne++) {
        // pour chaque type de pièce :
        for(action.typePiece = 1; action.typePiece < 4; action.typePiece++){
            // si l'oya ne possède plus de pièce du type voulu
            if(!t_jeu_oyaPossedePiece(jeu, action.typePiece)) {
                continue; // on passe à l'itération suivante
            }
            // on joue le coups, et on récupère le gagnant
            gagnant = MOTEUR_tourSuivant(jeu, action);
            if(gagnant >= 0 && gagnant != idIA)
                priorite = 0; // situation absolument non désirée !
            else if(gagnant >= 0)
                priorite = 100-profondeur; // situation absolument désirée !
                // on retire la profondeur pour qu'une solution éloignée soit 
                    // moins intéressante qu'une solution proche
            // si il n'y a aucun gagnant, on appelle minimax
            else if(gagnant == -2) // erreur, l'action n'est pas valide
                continue; // on passe à l'action suivante
            else {
                // on rappelle l'algorithme minimax, pour la profondeur suivante
                // On lui envois les arguments, dont l'action actuellement 
                // ritaire, et l'action étudiée
                priorite = IA_minimax(jeu, profondeur-1, prioMax, idIA);
                // si le joueur est l'IA, on prend le max
                if(jeu->oya == idIA) {
                    // si la priorité étudiée est plus grande
                    if(priorite > prioMax)
                        prioMax = priorite; // nouvelle prioMax
                }
                // sinon, on prend le min
                else {
                    // si la priorité étudiée est plus petite
                    if(priorite < prioMax)
                        prioMax = priorite; // nouvelle prioMax
                }
            }
            // si un coup à été joué :
            if(gagnant >= -1 && gagnant < 6)
                // on déjoue le coups
                MOTEUR_tourPrecedent(jeu);
            // ÉLAGAGE ALPHA-BÊTA
            // si la priorite max actuelle est plus grande que la valeur trouvée
            //  et que l'action est effectuée par un autre joueur, alors il n'est 
            //          pas la peine de continuer d'explorer cette partie de l'arbre
            if(prioMax != -1 && priorite != -1 && priorite < prioMax &&
                    jeu->oya != idIA) 
                break; // on passe au noed suivant, plus besoin de s'embêter avec celui-là
            // FIN ÉLAGAGE ALPHA-BÊTA
        } // end for each typePiece
    } // end for each colonne
    } // end profondeur > 0
    // sinon, la profondeur est atteinte : appel de l'heuristique !
    else {
        priorite = IA_h(jeu, idIA);
        // si la priorité étudiée est plus grande
        if(priorite > prioMax) {
            prioMax = priorite; // nouvelle prioMax
        }
    }
    return prioMax;
}








void fct_deb(int prof, int colonne, int t_piece, int prio) {
    int i = 0;
    for(i = 4-prof; i >= 0; i--) {
        printf("i\t");
    }
    printf("colonne %d, pièce %i => prio %d\n", colonne, t_piece, prio);
}
