# TETRIS : THE GAME

## Introduction
Ce projet nous a amené à réaliser un remake du célèbre jeu Tétris, comportant des fonctionnalités supplémentaires à la version originale.

Ce jeu a été développé en C++, et l'affichage est géré par la librairie SDL2.

Le jeu est en anglais. Il aussi est possible de jouer avec la musique Tétris.

## Organisation du projet
Depuis la racine du projet, vous pouvez trouver:
- Le `Makefile` : permet de compiler le projet
- L'exécutable `tetris` (si le projet est compilé) : permet de jouer au jeu (fichiers binaires)
- The dossier `src` : ensemble des fichiers sources du projet (fichiers C++)
- Le dossier `obj` (si le projet est compilé) : ensemble des fichiers objets du projet (fichiers O)
- Le dossier `include` : ensemble des fichiers sources du projet (fichiers HPP)
- Le dossier `mp3` : ensemble des fichiers sons (fichiers MP3)
- Le dossier `font` : ensemble des fichiers de style de texte (fichiers TFF)
- Le fichier `README.md` : ce présent document, conenant des informations essentielles à la compréhension du projet

## Compilation et lancement du jeu
Afin de jouer à notre Tétris, vous devez réaliser les étapes suivantes :
- Compiler le projet en utilisant la commande `make` depuis la racine du projet
- Lancer le jeu en utilisant la commande `./tetris` depuis la racine du projet

Vous pouvez aussi effacer les fichiers objets, le dossier `obj` et l'exécutable `tetris` en utilisant la commande `make clean`.

Pour naviguer dans le menu, il suffit de tapper sur les touches qui vous intéresse. Les règles sont expliquées dans la partie `Display Help`.

Si vous souhaitez quitter le jeu, appuyez sur la touche `echap`.

## Différents modes de jeu
Dans ce jeu, il est possible de jouer à 3 modes.

### Mode Solo
Vous jouez seul, et votre objectif est de réaliser le maximum de point possible avant de perdre. La vitesse du jeu accélère progressivement.

### Mode Multijoueurs
Vous jouez contre notre IA. Il existe 4 niveaux : Facile, Moyen, Difficile et Impossible. Votre objectif est de battre l'IA, soit en atteignant le niveau maximum avant elle, soit si elle perd avant. Compléter plusieurs lignes d'un coup permet d'envoyer des lignes trouées à l'adversaire (2 lignes en envoient une, 3 lignes en envoient 2 et 4 lignes en envoient 4). La vitesse du jeu accélère progressivement.

### Mode Démo IA
Il s'agit d'une démonstration de notre IA au sommet de son art. 

## Contributeurs
Ce projet a été réalisé par :
- Hugo LAULLIER
- Antoine BALZANO
