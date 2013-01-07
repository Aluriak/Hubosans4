#include "IA.h"
#include "../graphique/TERM/graphique_TERM.h"


/*
 * IA HEURISTIQUE
 */
// renvois le gain de la situation du jeu envoyé pour l'oya (between 0 and 100)
// ou -1 en cas d'erreur
// règles de priorités :
//      - l'oya a 3 pièces alignées     : 90
//      - l'oya a 2 pièces alignées     : 70
//      - l'oya a 1 pièce alignée       : 50
//      - un autre a 1 pièce alignée    : 40
//      - un autre a 2 pièces alignées  : 20
//      - un autre a 3 pièces alignées  : 0
// On garde évidemment la priorité la plus haute, on teste donc pour 4, puis 3, 
//  puis 2, puis 1 pièce.
//  plus une priorité est basse, plus elle est indésirable
int IA_h(t_jeu* jeu, int idIA) {
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
    int priorite = -1;
    // nombre de pièces maximum alignées :
    int nb_pieceMax = 0;



    // DÉTERMINATION DE LA PRIORITÉ
    // on détermine le nombre de pièces max alignées pour chaque joueur
    // Pour chaque case
        // pour chaque joueur
                // on utilise la fonction suivante, pour chaque joueur
                // int MOTEUR_test_puissance4(jeu, coordCase, idJoueur);
                // Renvois le nombre de cases alignées par le joueur par rapport
                //  à cette case
                // La k-ième case du tableau de priorité est égale à
                //      max(résultat fonction, valeur de la case du tableau)
    // pour chaque case du jeu (on parcours de haut en bas, de gauche à droite)
    for(i = jeu->nbCaseX-1; i >= 0; i--) {
        for(j = jeu->nbCaseY-1; j >= 0; j--) {
            coordCase.x = i;
            coordCase.y = j;
            // pour chaque joueur 
            for(k = jeu->nbJoueur-1; k >= 0; k--) {
                // on prend le nombre de case alignées par rapport à cette case
                nb_pieceMax = MOTEUR_test_puissance4(jeu, coordCase, k);
                // on prend le nombre max de pièces alignées par le joueur
                nb_pieceAligneeMax[k] = max(nb_pieceAligneeMax[k], nb_pieceMax);
            }
        }
    }
            

    // on a maintenant le nombre maximum de pièce alignées pour chaque joueur
    // on parcours les joueurs, et on prend le nombre de pièces max alignées
    // pour chaque joueur
    nb_pieceMax = tab_max(nb_pieceAligneeMax, jeu->nbJoueur);
    // maintenant, on regarde si l'IA jouée a ce nombre de pièces alignées
    if(nb_pieceAligneeMax[idIA] == nb_pieceMax) {
        // on définit la priorité renvoyée
        if(nb_pieceMax >= 3)
            priorite = 100;
        else if(nb_pieceMax == 2)
            priorite = 70;
        else if(nb_pieceMax == 1)
            priorite = 60;
        else // cas où il y a 0 pions alignés
            priorite = 50; // priorité moyenne
    }
    else { // c'est un adversaire qui a le nombre de pièce max !
        // on définit la priorité renvoyée
        if(nb_pieceMax >= 3)
            priorite = 0;
        else if(nb_pieceMax == 2)
            priorite = 20;
        else if(nb_pieceMax == 1)
            priorite = 40;
        else 
            priorite = 50;
    }

    // RETOUR DE LA PRIORITÉ
    // libération
    free(nb_pieceAligneeMax);
    // return
    /*printf("priorite = %d (J%d)\n", priorite, jeu->oya);*/
    /*TERM_afficherJeu(jeu);*/
    return priorite;    
}




