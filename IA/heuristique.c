#include "IA.h"



/*
 * IA HEURISTIQUE
 */
// renvois le gain de la situation du jeu envoyé pour l'oya (between 0 and 100)
// ou -1 en cas d'erreur
// règles de priorités :
//      - l'oya a 3 pièces alignées avec au moins 1 case vide      : 90
//      - l'oya a 2 pièces alignées avec au moins 2 cases vides    : 70
//      - l'oya a 1 pièce alignée avec au moins 3 cases vides      : 90
//      - un autre a 3 pièces alignées avec au moins 1 case vide   : 10
//      - un autre a 2 pièces alignées avec au moins 2 cases vides : 10
//      - un autre a 1 pièce alignée avec au moins 3 cases vides   : 10
// On garde évidemment la priorité la plus haute, on teste donc pour 4, puis 3, 
//  puis 2, puis 1 pièce.
int IA_h(t_jeu* jeu) {
    // INITIALISATIONS
    int i = 0, j = 0, k = 0; // itérateurs de boucle
    coord coordCase = {-1,-1}; // coordonnées de la case étudiée
    // nombre maximum de pièces du même joueur alignées trouvé jusque là
    // tableau dont l'index est l'id des joueur. Chaque joueur, avec son id, 
    // accède au nombre maximum de pièce qu'il a alignées avec suffisemment
    //  de cases vide pour faire un puissance 4
    int *nb_pieceAligneeMax = malloc(jeu->nbJoueur*sizeof(int)); 
        if(nb_pieceAligneeMax == NULL) { // gestion d'erreur
            FLUX_ERREUR("IA:", "malloc pour idJ* dans l'heuristique échouée");
            exit(EXIT_FAILURE);
        }
    // mise à 0 de toutes les cases
    for(i = 0; i < jeu->nbJoueur; i++)
        nb_pieceAligneeMax[i] = 0;
    // priorité à retourner :
    int priorite = -1; // utilisée aussi pour le calcul intermédiaire



    // DÉTERMINATION DE LA PRIORITÉ
    // Pour chaque case
        // pour chaque joueur
                // on utilise la fonction suivante :
                // int MOTEUR_test_puissance4(3);
                // Renvois le nombre de cases alignées par le joueur par rapport
                //  à cette case
    // pour chaque case du jeu (on parcours de haut en bas, de gauche à droite)
    for(i = jeu->nbCaseX-1; i >= 0; i--) {
        for(j = jeu->nbCaseY-1; j >= 0; j--) {
            coordCase.x = i;
            coordCase.y = j;
            // pour chaque joueur 
            for(k = 0; k < jeu->nbJoueur; k++) {
                // on prend le nombre de case alignées par rapport à cette case
                priorite = MOTEUR_test_puissance4(jeu, coordCase, k);
                // on prend le nombre max de pièces alignées par le joueur
                nb_pieceAligneeMax[k] = max(nb_pieceAligneeMax[k], priorite);
            }
        }
    }
            

    // on a maintenant le nombre maximum


    // RETOUR DE LA PRIORITÉ
    // libération
    free(nb_pieceAligneeMax);
    // return
    return priorite;    
}




