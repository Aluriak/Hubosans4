#include "inSecure.h"




/*
 * INSECURE: INT
 */
// renvois un int envoyé par l'utilisateur
int inSecure_int() {
    char chaine[INSECURE_N_MAX] = inSecure_entree();
    return atoi(chaine);
}





/*
 * inSecure
 */
// attend une chaîne de 10 caractères dans l'entrée standard, et renvois le premier chiffre et le premier mot
void inSecure(int* nb, char* mot) {
    // INITIALISATIONS
    // on récupère l'entrée utilisateur
    char* chaine = inSecure_entree();
    char* stockNb = malloc(INSECURE_N_MAX*sizeof(char)); // stockage du nombre sous 
        // forme de string
    // traitement : on trouve le premier mot et le premier chiffre, qu'on place dans 
    //  les espaces mémoires pointés par nb et mot.
    bool f_nb = false; // nombre trouvé
    bool nb_lu = false; // nombre lu
    bool f_mot = false; // mot trouvé
    bool mot_lu = false; // mot lu
    int i = 0, itnb = 0, itmot = 0; // itérateurs de chaînes
    int t_chaine = strlen(chaine); // taille de la chaine
    char c; // lettre étudiée
    
    // TRAITEMENTS
    // lecture de la chaîne, tant que non lue entièrement ou tant que le nombre ou le mot
    //  n'a pas été trouvé
    for(i = 0; i < t_chaine && (!nb_lu || !mot_lu); i++) {
        c = chaine[i];
        // si c'est une lettre
        if(isalpha(c)) {
            // si on cherchait des chiffres
            if(f_nb) {
                nb_lu = true; // le nombre est lu
                f_nb = false; // et on ne cherche plus de chiffre
            }
            // si le mot n'est pas encore lu
            if(!mot_lu) {
                mot[itmot] = c; // on enregistre la lettre dans le mot
                itmot++; // et on incrémente l'itérateur
                f_mot = true; // on attend de nouvelles lettres
            }
        }
        // si c'est un chiffre
        else if(isdigit(c)) {
            // si on cherchait des lettres
            if(f_mot) {
                mot_lu = true; // le mot est lu
                f_mot = false; // et on ne cherche plus de lettres
            }
            // si le nombre n'est pas encore lu
            if(!nb_lu) {
                stockNb[itnb] = c; // on enregistre le chiffre dans la chaine stockNb
                itnb++; // et on incrémente l'itérateur
                f_nb = true; // on attend de nouveaux chiffres
            }
        }
    }
    // on possède maintenant le premier mot dans mot, et le chiffre en string dans stockNb
    if(itmot < t_chaine) // si besoin, on rajoute le caractère de fin de chaîne
        mot[itmot] = '\0';
    if(itnb < t_chaine) // de même pour stockNb
        stockNb[itnb] = '\0';
    // dernier traitement : *nb doit devenir égal à la valeur écrite ens tring dans stockNb
    *nb = atoi(stockNb);

    // POST-TRAITEMENT
    // libérations mémoires
    free(chaine);
    free(stockNb);
}



/*
 * INSECURE: ENTREE
 */
// capture une chaîne de taille INSECURE_N_MAX, et renvois son adresse
char* inSecure_entree() {
    char* chaine = malloc(INSECURE_N_MAX*sizeof(char));
    if(chaine == NULL) {
        FLUX_ERREUR("inSecure","allocation de chaîne d'entrée échouée.");
        exit(EXIT_FAILURE);
    }
    // lecture dans l'entrée standard avec fgets
    if(!fgets(chaine, INSECURE_N_MAX, stdin)) {
        // si échec de la lecture,
        // on renvois une chaîne vide
        chaine[0] = '\0';
    }
    // on remplace le \n par un \0, ou sinon on appelle le vidage de buffer clavier
    char* cible = strchr(chaine, '\n');
    // si la cible est trouvée
    if(cible != NULL)
        *cible = '\0'; // on remplace
    else
        inSecure_viderBufferClavier(); // on vide le buffer
    // retour de la chaîne
    return chaine;
}

/*
 * INSECURE: VIDER BUFFER CLAVIER
 */
// vide le buffer clavier
void inSecure_viderBufferClavier() {
    int c; // getchar renvois un int, pour gérer les cas d'erreur
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}


