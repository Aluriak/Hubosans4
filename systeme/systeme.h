#ifndef SYSTEME_H_INCLUDED
#define SYSTEME_H_INCLUDED

/*
 * BIBLIOTHEQUES
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <dirent.h>
#include <termios.h>
#include <unistd.h>

//#include <SDL/SDL.h>



/*
 * DEFINES
 */
#define FILE_ERR "erreur.txt"


/*
 * PREDECLARATIONS
 */
// énumération booléenne
typedef enum {false, true} bool;

// Autorise ou non d'annuler le dernier coup 
bool allow_last;

// Contient le nom de la sauvegarde à charger
//char save[20];


/*
 * PROTOTYPES
 */
    void FLUX_ERREUR(char* source, char* erreur); // affiche dans stderr l'erreur envoyée
    int randN(int N); // renvois un nombre aléatoire entre 0 et N-1 (N > 0)
    int max(int a, int b); // renvois a si a >= b, ou b
    int min(int a, int b); // renvois a si a <= b, ou b
    int tab_max(int* tab, int T); // renvois la valeur maximum contenue dans le tableau de taille T
    int tab_count(int* tab, int T, int A); // renvois le nombre de valeur A contenue dans le tableau T
    int apowb(int a, int b); // retourne a^b, si b >= 0
    int str2int(char * str, int nb_carac); // renvois un entier positif à partir d'une chaine de caractère ne contenant que des entiers positifs
    char getOneChar(); // retourne le char correspondant à la touche tapée par l'utilisateur



#endif
