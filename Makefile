CC=gcc
FLAGS=-Wall -Werror
FINALNAME=hubosans4


$(FINALNAME) :
	$(CC) $(FLAGS) -c main.c
	$(CC) -o $(FINALNAME) *.o




