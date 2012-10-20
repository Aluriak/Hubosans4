CC=gcc
FLAGS=-Wall -Werror
FINALNAME=hubosans4


$(FINALNAME) : main.c
	$(CC) $(FLAGS) -c main.c


mod_graphique.o: modules/graphique/graphique.c
	$(CC) $(FLAGS) -c modules/graphique.c
mod_IA.o: modules/IA/IA.c
	$(CC) $(FLAGS) -c modules/IA.c
mod_reseau.o: modules/reseau/reseau.c
	$(CC) $(FLAGS) -c modules/reseau.c
mod_sonore.o: modules/sonore/sonore.c
	$(CC) $(FLAGS) -c modules/sonore.c
mod_moteur.o: modules/moteur/moteur.c
	$(CC) $(FLAGS) -c modules/moteur.c
