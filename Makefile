CC=gcc
FLAGS=-Wall -Werror
FINALNAME=hubosans4


$(FINALNAME) : mod_graphiques.o
	$(CC) $(FLAGS) -c main.c


mod_graphiques.o:
	$(CC) $(FLAGS) -c modules/graphiques.c


mod_IA.o:
	$(CC) $(FLAGS) -c modules/IA.c
mod_reseau.o:
	$(CC) $(FLAGS) -c modules/reseau.c
mod_sonore.o:
	$(CC) $(FLAGS) -c modules/sonore.c
mod_moteur.o:
	$(CC) $(FLAGS) -c modules/moteur.c
