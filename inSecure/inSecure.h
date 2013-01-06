#ifndef INSECURE_H_INCLUDED
#define INSECURE_H_INCLUDED


/*
 * BIBLIOTHEQUES
 */
// modules
#include "../systeme/systeme.h"



/*
 * DEFINES
 */
# define INSECURE_N_MAX 10 // taille maxi de la chaîne capturée



/*
 * DECLARATIONS
 */





/*
 * PROTOTYPES
 */

    void inSecure(int*, char*); // attend une chaîne de INSECURE_N_MAX caractères dans l'entrée standard, et renvois le premier chiffre et le premier mot
    char* inSecure_entree(); // lit une chaîne de taille INSECURE_N_MAX et renvois l'adr

    void inSecure_viderBufferClavier(); // vide le buffer clavier






#endif
