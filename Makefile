# CONSTANTES #

CC=gcc
FLAGS=-Wall -Werror
FINALNAME=hubosans4





# FICHIERS OBJETS #

# le fichier objet main est créé
main.o: *.c
	$(CC) $(FLAGS) -c *.c

# pour chaque module, on créé un fichier .o dans le répertoire courant
mod_graphique.o: modules/graphique/*.c
	$(CC) $(FLAGS) -c modules/*.c
mod_IA.o: modules/IA/*.c
	$(CC) $(FLAGS) -c modules/*.c
mod_reseau.o: modules/reseau/*.c
	$(CC) $(FLAGS) -c modules/*.c
mod_sonore.o: modules/sonore/*.c
	$(CC) $(FLAGS) -c modules/*.c
mod_moteur.o: modules/moteur/*.c
	$(CC) $(FLAGS) -c modules/*.c





# EXECUTABLE #

# création de l'exécutable
$(FINALNAME) : *.o
	$(CC) -o $(FINALNAME) *.o





# COMMANDES

# suppression des fichiers objets
clean:
	rm *.o 
