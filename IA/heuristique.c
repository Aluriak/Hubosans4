#include "IA.h"
#include "../graphique/TERM/graphique_TERM.h"


/*
 * IA HEURISTIQUE
 */
// renvois le gain de la situation du jeu envoyé pour l'oya (entre 0 et 100)
//  plus une priorité est basse, plus elle est indésirable
int IA_h(t_jeu* jeu, int idIA) {
    // INITIALISATION
    int i, y; // itérateurs de boucles
    int joueur; // id du joueur actuellement considéré
    int nb_piece_alignees; // empalcement occupé par le joueu
    int nb_vide; // emplacements vides
    int alignMax = 0; // alignement de pièces maximum pour trois pièces
    int joueur_max = -1; // joueur alignant le plus de pièce (idIA si égalité)
    t_case casac; // case étudiée

    // TRAITEMENT
    for(joueur = 0; joueur < jeu->nbJoueur; joueur++) 
    // pour chaque ligne
    for(y = 0; y < jeu->nbCaseY; y++) {
        nb_piece_alignees = nb_vide = 0;
        // parcours de la ligne
        for(i = 0; i < jeu->nbCaseX; i++) {
                casac = jeu->plateau[y][i]; // case actuellement étudiée
                // si la case appartient au moins en partie à l'IA
                if(IA_caseAppartientA(joueur, casac))
                    nb_piece_alignees++;
                // si elle est vide
                else if(IA_caseVide(casac))
                    nb_vide++;
                // sinon, c'est que la case est complètement bloquée par qqn d'autre
                else {
                    // on comptabilise le nombre de pièces si ya un espace vide
                    // et assez de place pour 4 pièces ou plus
                    // sinon c'est qu'on ne peut pas aligner plus de pièces
                    if(nb_vide > 0 && nb_vide+nb_piece_alignees >= 4) {
                        // si le nouvel alignement est plus grand, ou aussi grand
                        if(nb_piece_alignees >= alignMax) {
                            // alignMax au plus haut
                            alignMax = max(alignMax, nb_piece_alignees);
                            // et le joueur_max deviens le joueur actuel
                            joueur_max = joueur;
                        }
                    }
                    // compteurs réinitialisés
                    nb_vide = nb_piece_alignees = 0;
                }
        }
    }
    // pour chaque colonne
    for(i = 0; i < jeu->nbCaseX; i++) {
        nb_piece_alignees = nb_vide = 0;
        // parcours de la colonne (de haut en bas)
        for(y = 0; y < jeu->nbCaseY; y++) {
                casac = jeu->plateau[y][i]; // case actuellement étudiée
                // si la case appartient au moins en partie à l'IA
                if(IA_caseAppartientA(joueur, casac))
                    nb_piece_alignees++;
                // si elle est vide
                else if(IA_caseVide(casac))
                    nb_vide++;
                // sinon, c'est que la case est complètement bloquée par qqn d'autre
                else {
                    // on comptabilise le nombre de pièces si ya un espace vide
                    // et assez de place pour 4 pièces ou plus
                    // sinon c'est qu'on ne peut pas aligner plus de pièces
                    if(nb_vide > 0 && nb_vide+nb_piece_alignees >= 4) {
                        // si le nouvel alignement est plus grand, ou aussi grand
                        if(nb_piece_alignees >= alignMax) {
                            // alignMax au plus haut
                            alignMax = max(alignMax, nb_piece_alignees);
                            // et le joueur_max deviens le joueur actuel
                            joueur_max = joueur;
                        }
                    }
                    // compteurs réinitialisés
                    nb_vide = nb_piece_alignees = 0;
                }
        }
    }



printf("alignMax = %i\n", alignMax);
    if(joueur_max == idIA) {
        if(alignMax >= 3)
            return 90;
        else if(alignMax == 2)
            return 70;
        else if(alignMax == 1)
            return 60;
        else
            return 50;
    }
    // c'est un autre joueur qui aligne le plus de pièces
    else {
        if(alignMax >= 3)
            return 0;
        else if(alignMax == 2)
            return 20;
        else if(alignMax == 1)
            return 40;
        else
            return 50;
    }

    // END IA_h()
}





/*
 * IA: CASE APPARTIENT A
 */
// renvosi vrai si la case appartient, en partie au moins, au joueur envoyé
bool IA_caseAppartientA(int idJ, t_case casac) {
    return (casac.joueurPiecePleine == idJ || casac.joueurPieceCreuse == idJ);
}



/*
 * IA: CASE VIDE
 */
// renvois vrai si la case envoyée est vide
bool IA_caseVide(t_case casac) {
    return (casac.joueurPiecePleine == -1 && casac.joueurPieceCreuse == -1);
}



/*
 * IA: CASE JOUABLE
 */
// renvois vrai si la case envoyée est encore jouable (il y a au moins un empalcement libre
// NB: aucune vérification si une pièce peut y être déposée !
bool IA_caseJouable(t_case casac) {
    return (casac.joueurPiecePleine == -1 || casac.joueurPieceCreuse == -1);
}


