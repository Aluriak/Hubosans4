# CONSTANTES #

CC=gcc
FLAGS=-Wall -Werror
FINALNAME=hubosans4





# FICHIERS OBJETS #

# le fichier objet main est créé
main.o: *.c mod_systeme.o
	$(CC) $(FLAGS) -c *.c

# pour chaque module, on créé un fichier .o dans le répertoire courant
mod_systeme.o: modules/systeme/*.c
	$(CC) $(FLAGS) -c modules/systeme/*.c
mod_graphique.o: modules/graphique/*.c mod_systeme.o
	$(CC) $(FLAGS) -c modules/graphique/*.c
mod_IA.o: modules/IA/*.c mod_systeme.o
	$(CC) $(FLAGS) -c modules/IA/*.c
mod_reseau.o: modules/reseau/*.c mod_systeme.o
	$(CC) $(FLAGS) -c modules/reseau/*.c
mod_sonore.o: modules/sonore/*.c mod_systeme.o
	$(CC) $(FLAGS) -c modules/sonore/*.c
mod_moteur.o: modules/moteur/*.c mod_systeme.o
	$(CC) $(FLAGS) -c modules/moteur/*.c





# EXECUTABLE #

# création de l'exécutable
$(FINALNAME) : *.o
	$(CC) -o $(FINALNAME) *.o





# COMMANDES

# suppression des fichiers objets
clean:
	rm *.o 
