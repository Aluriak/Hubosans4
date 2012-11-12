# CONSTANTES #

CC=gcc
FLAGS=-Wall -Werror
SDL=`sdl-config --cflags --libs`
FINALNAME=hubosans4




# EXECUTABLE #

# création de l'exécutable
$(FINALNAME) : main.o
	$(CC) -o $(FINALNAME) *.o



# FICHIERS OBJETS #

# le fichier objet main est créé
main.o: *.c graphique_TERM.o moteur.o systeme.o IA.o
	$(CC) $(FLAGS) -c *.c

# pour chaque module, on créé un fichier .o dans le répertoire courant
systeme.o: systeme/*.c
	$(CC) $(FLAGS) -c systeme/*.c
graphique_SDL.o: graphique/SDL/*.c systeme.o
	$(CC) $(FLAGS) -c graphique/SDL/*.c -o graphique_SDL.o
graphique_TERM.o: graphique/TERM/*.c systeme.o moteur.o
	$(CC) $(FLAGS) -c graphique/TERM/*.c -o graphique_TERM.o
IA.o: IA/*.c systeme.o moteur.o
	$(CC) $(FLAGS) -c IA/*.c
reseau.o: reseau/*.c systeme.o moteur.o
	$(CC) $(FLAGS) -c reseau/*.c
sonore.o: sonore/*.c systeme.o moteur.o
	$(CC) $(FLAGS) -c sonore/*.c
moteur.o: moteur/*.c  systeme.o 
	$(CC) $(FLAGS) -c moteur/*.c








# COMMANDES

# suppression des fichiers objets
clean:
	rm *.o 

# suppression de tous les fichiers produits
cleanALL:
	rm *.o
	rm $(FINALNAME)



