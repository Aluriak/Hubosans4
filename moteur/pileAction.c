#include "moteur.h"




/*
 * T_PILE ACTION 
 */
// Initialise la pile aux bonnes valeurs de départ
void t_pileAction_init(t_pileAction* p) {
    p->nbElem = 0;
    p->sommet = NULL;
}


/*
 * T_PILE ACTION 
 */
// libère la pile
void t_pileAction_free(t_pileAction* p) {
    t_pileAction_vider(p);
}


/*
 * T_PILE ACTION 
 */
// empile l'action demandée
void t_pileAction_emp(t_pileAction *p, t_action action) {
    t_pile_elem* ajout = malloc(sizeof(t_pile_elem));
    ajout->action = action;
    ajout->nxt = p->sommet;
    p->sommet = ajout;
    p->nbElem++;
}




/*
 * T_PILE ACTION 
 */
// Retourne l'action du sommet de la pile, qui est dépilée. action nulle si 
// 	pile vide
t_action t_pileAction_dep(t_pileAction *p) {
    t_action action = {-1,-1}; // action à retourner
    t_pile_elem* cible = NULL; // élément à supprimer
    if(p->nbElem > 0) { // si il y a au moins un élément
	action = p->sommet->action; // on enregistre l'action
	cible = p->sommet; // la cible de dépilage est le sommet
	p->sommet = p->sommet->nxt; // le nouveau sommet est l'élément suivant
	free(cible); // on libère la cible de dépilage
	p->nbElem--; // un élément en moins dans la pile
    }
    return action;
}




/*
 * T_PILE ACTION 
 */
// retourne l'action du sommet de la pile, sans y toucher
t_action t_pileAction_val(t_pileAction *p) {
    t_action action = {-1,-1}; // action à retourner
    if(p->nbElem > 0)
	action = p->sommet->action;
    return action;
}



/*
 * T_PILE ACTION VIDER
 */
// Vide la pile
void t_pileAction_vider(t_pileAction* p) {
    while(p->nbElem > 0) {
	t_pileAction_dep(p);
    }
}




/*
 * T_PILE ACTION INVERSER
 */
// renvoit la pile inversée et libère la pile envoyée
t_pileAction* t_pileAction_inverser(t_pileAction* p) {
    // pile intermédiaire
    t_pileAction *inter = malloc(sizeof(t_pileAction));
    t_pileAction_init(inter);
    // traitement
    while(p->nbElem > 0)
	t_pileAction_emp(inter, t_pileAction_dep(p));
    // retour
    return inter;
}



/*
 * T_PILE ACTION COPIE
 */
// retourne une copie de la pile
t_pileAction* t_pileAction_copie(t_pileAction* p) {
    t_pileAction* copie = malloc(sizeof(t_pileAction));
    t_pileAction_init(copie);
    t_pile_elem * it = p->sommet; // itérateur de pile
    // on insère chaque élément de la pile rencontrée dans la copie
    while(it != NULL) {
        t_pileAction_emp( copie, it->action ); // empilage de l'action
        it = it->nxt; // passe au suivant
    }
    // maintenant, la copie étant inversée, on l'inverse pour qu'elle soit copie carbone
    copie = t_pileAction_inverser(copie);
    // copie carbone renvoyée
    return copie;
}





