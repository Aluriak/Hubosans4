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
    /*// INITIALISATIONS*/
    /*int i = 0, j = 0; // itérateurs de boucle*/
    /*// nombre maximum de pièces du même joueur alignées trouvé jusque là*/
    /*// tableau dont l'index est l'id des joueur. Chaque joueur, avec son id, */
    /*// accède au nombre maximum de pièce qu'il a alignées avec suffisemment*/
    /*//  de cases vide pour faire un puissance 4*/
    /*int *nb_pieceAligneeMax = malloc(jeu->nbJoueur*sizeof(int)); */
        /*if(nb_pieceAligneeMax == NULL) { // gestion d'erreur*/
            /*FLUX_ERREUR("IA:", "malloc pour idJ* dans l'heuristique échouée");*/
            /*exit(EXIT_FAILURE);*/
        /*}*/
    /*// mise à 0 de toutes les cases*/
    /*for(i = 0; i < jeu->nbJoueur; i++)*/
        /*nb_pieceAligneeMax[i] = 0;*/
    /*// priorité à retourner :*/
    /*int priorite = -1;*/



    /*// DÉTERMINATION DE LA PRIORITÉ*/
    /*// pour chaque joueur*/
        /*// pour chaque direction (hori, vert, diag1, diag2)*/
            /*// pour chaque ligne de cette direction */
                /*// on compte les cases vides alignées, */
                /*// TODO*/
            



    /*// pour chaque case vide ayant au moins une pièce à côté*/
    /*for(i = 0; i < jeu->nbCaseX, i++) {*/
        /*for(j = 0; j < jeu->nbCaseX, j++) {*/
            /*// si la case est vide*/
            /*if(jeu->plateau[i][j].typePiece == VIDE) {*/
            /*}*/
        /*}*/
    /*}*/


    /*// RETOUR DE LA PRIORITÉ*/
    /*// libération*/
    /*free(idJ);*/
    /*// return*/
    /*return priorite;    */
    return -1;
}




