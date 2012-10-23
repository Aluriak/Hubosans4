# CONSTANTES #

CC=gcc
FLAGS=-Wall -Werror
FINALNAME=hubosans4




# EXECUTABLE #

# création de l'exécutable
$(FINALNAME) : main.o
	$(CC) -o $(FINALNAME) *.o



# FICHIERS OBJETS #

# le fichier objet main est créé
main.o: *.c graphique_TERM.o moteur.o systeme.o
	$(CC) $(FLAGS) -c *.c

# pour chaque module, on créé un fichier .o dans le répertoire courant
systeme.o: modules/systeme/*.c
	$(CC) $(FLAGS) -c modules/systeme/*.c
graphique_SDL.o: modules/graphique/SDL/*.c systeme.o
	$(CC) $(FLAGS) -c modules/graphique/SDL/*.c -o graphique_SDL.o
graphique_TERM.o: modules/graphique/TERM/*.c systeme.o moteur.o
	$(CC) $(FLAGS) -c modules/graphique/TERM/*.c -o graphique_TERM.o
IA.o: modules/IA/*.c systeme.o moteur.o
	$(CC) $(FLAGS) -c modules/IA/*.c
reseau.o: modules/reseau/*.c systeme.o moteur.o
	$(CC) $(FLAGS) -c modules/reseau/*.c
sonore.o: modules/sonore/*.c systeme.o moteur.o
	$(CC) $(FLAGS) -c modules/sonore/*.c
moteur.o: modules/moteur/*.c systeme.o 
	$(CC) $(FLAGS) -c modules/moteur/*.c








# COMMANDES

# suppression des fichiers objets
clean:
	rm *.o 




