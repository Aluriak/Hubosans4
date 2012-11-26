#include "systeme.h"




/*
 * FLUX ERREUR
 */
// affiche dans stderr l'erreur envoyée
void FLUX_ERREUR(char* source, char* erreur) {
    FILE* fileErr = fopen(FILE_ERR, "wa");
    assert(fileErr); // erreur ouverture fichier
    fprintf(fileErr, "%s: %s", source, erreur);
    fclose(fileErr);
}






/*
 * RAND N
 */
// renvois un nombre aléatoire entre 0 et N-1 (N > 0)
int randN(int N) {
    return (int) (rand() / (double)RAND_MAX * (N));
}





/*
 * MAX
 */
// renvois a si a >= b, ou b
int max(int a, int b) {
    if(a >= b)
	return a;
    else
	return b;
}




/*
 * TAB MAX
 */
// renvois la valeur maximum contenue dans le tableau de taille T
int tab_max(int* tab, int T) {
    if(T <= 0) return 0;
    int max = tab[0];
    int i = 1;
    for(; i < T; i++) {
	if(tab[i] > max)
	    max = tab[i];
    }
    return max;
}


/*
 * STR2INT
 */
//renvois un entier positif à partir d'une chaine de caractère ne contenant que des entiers positifs
//Valeurs ASCII :
//	dec chr   dec chr
//	----------------
//	48 : 0	| 53 : 5
//	49 : 1	| 54 : 6
//	50 : 2	| 55 : 7
//	51 : 3	| 56 : 8
//	52 : 4	| 57 : 9
//
int str2int(char * str, int nb_carac)
{
	int i = 0; // itérateur de boucle
	int resultat = 0; // Variable retournée contenant la valeur de str
	char tmp; // Variable tampon
	// Tant que tmp n'a pas lu tout les chiffres
	for(i=0;i<nb_carac;i++)
	{
		printf("tour %i: str[i] = %c\n", i, str[i]);
		tmp=str[i]; // On récupère la valeur de str[i] pour traitement
		tmp -= 48; // On retire 48 pour obtenir la valeur en int
		resultat += tmp*pow(10, nb_carac-1-i); 
	}
	return resultat;
}
