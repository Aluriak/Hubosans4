#PUISSANCE 4++



##Principes
Le principe est le même que celui du puissance 4, avec quelques améliorations :
* Gestion de 3 type de pieces
	* Pieces pleines
	* Pieces creuses
	* Pieces bloquantes
* Gestion du jeu à N joueurs (N > 1)
* Matrice de N\*M cases (gravite non optionnelle)


##Caractéristiques techniques
###Programmation
* Utilisation du compilateur gcc
	* Moteur de jeu
	* Sauvegarde de partie en cours
	* Sauvegarde de donnees joueurs
	* Scoring

* Utilisation de la SDL lib
	* Modules graphiques & sonores
	* Modules reseaux


###Support
* OS
	* Linux (prioritaire)
	* Windows (et encore)
	* Mac (faut pas chier non plus ;] )

* Stockage
	* Serveur git, github.com


## Etapes du développement
* Etape 1 : moteur du jeu + affichage terminal
    * utilisation des caractères , ·, O et X pour l'affichage des pièces (affichage en couleur grâce à la technologie printf)
* Etape 2 : gestion scoring et sauvegarde
* Etape 3 : IA
* Etape 4 : interface graphique et sonore avec la SDL
* Etape 5 : réseau
* Etape 6 : cross platform

Etape actuelle : 0.5


### Etape 1
L'étape 1 est la base du projet, puisque le moteur du jeu, définit à cette étape, restera inchangé pour le reste du projet.


