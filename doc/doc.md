# Documentation Technique : Projet B-YEP-400 Indie Studio

## Epitech

## Année 2021

> Membres : Corentin Petrau, Lyvia Mallereau, Raphael Risser, Alec Ferrari, Paul Narchal, Florian Chanson

## Sommaire

> I- Introduction
>
> II- Présentation du projet
>
> III- Organisation/Architecture du projet
>
> IV- Entity-Component-System
>
> V- Partie Raylib
>
> VI- Partie Jeu
>
> VII- Description technique du code
>
> VIII- Difficultés rencontrées
>
> IX- Conclusion
>
> X- Sources

## I- Introduction

Le présent document est une documentation technique du projet B-400-YEP Indie Studio destinée aux futurs utilisateurs et examinateurs dudit projet.

La documentation décompose le programme en différentes parties afin de mieux le décrire. Il n'est qu'une explication partielle du code du programme et ne sera pas une démonstration complète du projet. Le but est de discuter de l'implémentation du projet et de quoi celle-ci découle.

Les rédacteurs et programmeurs ne seront pas tenus responsables des différents bugs qui peuvent résulter de l'utilisation du programme. Les utilisateurs doivent le prendre dans son intégralité et l'adapter dans le cadre de leurs besoins, en tant que démonstration ou simplement pour jouer.

## II- Présentation du projet

Le projet B-400-YEP Indie Studio est un projet pour les étudiants de deuxième année (ici il s'agira de la promotion 2024) au sein de l'école Epitech.

Ce projet a pour but de recréer le jeu Bomberman (sorti en 1983 sur plusieurs machines, notamment la MSX et la ZX Spectrum). Le but du jeu est de déposer des bombes sur une grille afin de détruire ses adversaires. La réalisation du jeu en lui-même n'est pas très compliquée. Le gameplay est relativement simple, facile à implémenter. L'intérêt du projet vient dans la manière dont il sera implémenté. Cette implémentation peut compliquer le projet en le rendant par la même occasion plus intéressant.

D'un point de vue pédagogique, le projet s'effectue en groupe de 6 personnes. Chaque personne ayant sa propre façon de travailler, il faut trouver la bonne méthode de travail. Cette méthode devrait permettre aux membres du groupe de travailler sans craindre de mettre en péril le travail des autres. Dans cet esprit, la maîtrise d'un logiciel de gestion de version comme Github est primordiale.

De prime abord, recréer un Bomberman semble simple. Cependant, les conditions de réalisation complexifient la chose. En effet, la prise en compte du lancement sur différents systèmes d'exploitation (Linux-based/Windows) est la clé pour permettre la distribution du jeu. Par ailleurs, il faut réfléchir à une architecture extensible, optimisée et stable permettant un développement rapide. Bien entendu, recréer un jeu Bomberman ne veut pas dire reprendre le même design, il faut réfléchir à un thème et l'adapter au projet.

## III- Organisation/Architecture du projet

Dans un premier temps et comme dit précédemment, il a fallu discuter du thème choisi pour le jeu. Le gameplay à réaliser a guidé notre réflexion autour du thème : il nous fallait des explosions, des éléments destructibles et une opposition. Pour notre projet, nous avons le théme Godzilla vs King Kong, qui nous semblait assez amusant pour les joueurs, sans être ennuyant.

Lorsque le projet nous a été présenté, le responsable du projet a encouragé le développement d'une architecture complexe basée sur un design pattern moderne : l'Entity-Component-System. Réaliser un jeu en prenant avantage de ce design pattern peut s'avérer difficile et nécessite beaucoup de réflexion. Nous sommes le seul groupe ayant choisi cette difficulté supplémentaire. Il nous a semblé important de toujours travailler à se mettre à jour et s'améliorer.

Une fois que le thème a été choisi et que le design pattern a été décidé, le projet à été découpé en plusieurs parties distinctes : l'ECS (Entity-Component-System), l'engine basé sur la Raylib (librairie obligatoire) et le jeu en lui-même.

Cette division des tâches a permis de réaliser un projet moderne, proposant des solutions élégantes et facile à maintenir.

C'est en connaissant les forces et les faiblesses de chacun que le travail a pu se faire rapidement et efficacement. Chacun a travailler sur sa partie de manière optimale, sans s'interdire de collaborer avec ses coéquipiers sur les parties compliquées.

## IV- Entity-Component-System

Dans cette partie, nous décrirons le design pattern que nous avons suivi : l'Entity-Component-System. Il sera appelé ECS dorénavant.

Nous verrons dans un premier temps une explication de l'idée derrière le pattern, son fonctionnement en général, puis son implémentation dans notre cas.

## Sommaire Sous-Partie 1

> 1.Pourquoi un ECS ?
>
> 2.Fonctionnement général
>
> 3.Implémentation
>
> 4.Diagrammes

### 1.Pourquoi un ECS ?

Pour décrire un ECS, il s'agit d'un modèle architectural qui est principalement utilisé dans le développement de jeux-vidéos. En outre, il suit le principe de composition sur "l'héritage" qui permet une plus grande flexibilité dans la définition des entités où chaque objet dans la scéne d'un jeu est une entité (on peut prendre comme exemple des ennemis, des balles, des véhicules, etc).

Chaque entité se compose d'un ou de plusieurs composants qui contiennent des données ou d'un état. Par conséquent, le comportement d'une entité peut-être modifié lors de l'exécution par des systémes qui ajoutent, suppriment ou modifient des composants. Cela permet d'éliminer les problémes d'ambiguité des hiérarchies d'héritage profondes et larges qui sont difficiles à comprendre, maintenir et étendre. Les approches ECS communes sont hautement compatibles et souvent combinées avec des technique de conception orientées objet (une optimisation du programme motivée par une utilisation efficace du caahce CPU, principalemment utilisé dans le développement de jeux-vidéos).

Pour faire un bref rappel de l'histoire de l'ECS, c'est en 2007 qu'on en entend la première fois parler: une équipe travaillant sur un jeu nommé Operation Flashpoint : Dragon Rising expérimente des conceptions de l'ECS. C'est ensuite Adam Martin qui écrit un compte rendu détaillé de la conception ECS, comprenant des définitions de la terminologie et des concepts de base. Son travail à propulsé les idées de "systémes" (élément de première classe), "entité en tant qu'identifiant", "composants en tant que données brutes", "code stocké dans les systèmes, pas dans des composants ou des entités".

### 2.Fonctionnement général

Dans la terminologie de Martin, il y décrit son focntionnement de manière formelle:

- Entité: il s'agit d'un objet à usage général. Habituellement, il ne s'agit que d'un identifiant unique. Ils "marquent chaque objet de jeu grossier comme élément séparé". Les implémentations utilisent généralement un entier pour cela.
- Composant: les données brutes pour un aspect de l'objet, et comment il intergit avec le monde. "Etiquette l'entité comme possédant cet aspect particulier". Les implémentations utilisent généralement des structures, des classes ou des tableaux associatifs.
- Système: chaque système s'éxécute en continu (comme si chaque système avait son propre thread privé) et exécute des actions globales sur chaque entité qui possède un composant du même aspect que ce sytème.

Pour comprendre comment cela fonctionne on suppose, par exemple, qu'il existe une simple fonction de dessin : il s'agit la d'un "système" qui parcourt toutes les entités qui ont à la fois un composant physique et un composant visible, et les dessine. Ce composant visible peut généralement contenir des informations sur l'apparence d'une entité (par exemple: un humain, un monstre, des étincelles volantes, une flèche volante) et utiliser le composant physique pour savoir où le dessiner.

## V- Partie Raylib

Dans cette partie, nous allons décrire de manière simple la Raylib, la librairie graphique que nous avons utilisée ; ainsi que notre utilisation de celle-ci.

Pour ce faire, nous allons voir dans un premier temps une description de la Raylib elle-même et sa mise en place dans le programme.

## Sommaire Sous-Partie 2

> 1.Description de la Raylib
>
> 2.Mise en place de la Raylib

### 1.Description de la Raylib

La Raylib est une bibliothèque logicielle multiplateforme (Android, FreeBSD, HTML5, Linux, MacOS, Windows, ainsi que différents systèmes embarqués) sous licence zlib/libpng, publié par Ramon Santamaria depuis 2013, orientée vers le développement d'application interactives, telles que les jeux-vidéos.

Elle est developpé en langage C et son API qui se veut simple et légère comporte des bindings dans plus de 50 langages (C, Lua, C++, C#, PHP, Rust,Python, etc).

Cette librairie est incroyablement complète et dispose de beaucoup de fonctionnalités allant de modèles 3D, aux shaders en passant par de l'UI. Cette polyvalence est un réel atout et a rendu le développement relativement facile.

### 2.Mise en place de la Raylib

## VI- Partie Jeu

Nous décrirons ici toute la partie jeu ainsi que ses mécaniques. Comme dit précédement, nous avons choisi le théme Godzilla vs King Kong.

## VII- Description technique du code

## VIII- Difficultés rencontrées

Plusieurs difficultés ont été rencontrées dans la construction et la réalisation du projet.

Dans un premier temps ce fut la décision de l'architecture : ne pas choisir la facilité a mis le groupe dans une situation délicate. Le projet se réalisant en quatres semaines avec de nombreux membres et se révélant assez complexe, c'est avec les commentaires et les remarques des encadrants que le groupe a décidé de prendre des risques et de passer par l'ECS pour porter le projet.

Par la suite il a fallu appréhender la programmation orienté data en developpant directement via l'ECS. Comprendre le fonctionnement du design pattern fut aussi une difficulté supplémentaire. Il a fallu changer la manière dont nous réfléchissions jusque là. Ce changement a fait survenir de nombreux problèmes liés à nos habitudes de programmation mais sortir de celle-ci n'est que bénéfique pour le futur.

Par ailleurs, regrouper le travail de tout les membres fut relativement compliqué à mettre en place vu le nombre de fichiers et de la complexité du projet.

## IX- Conclusion

Nous tenons à préciser que la démonstration de ce projet n'a pas pour but de permettre la tricherie. Le projet peut cependant vous servir d'aide dans d'éventuelles réflexions concernant l'ECS ou la Raylib. En outre, nous nous dédouanons de toute responsabilité si vous tentez d'adapter votre code sur ce projet.

La dernière partie de ce document pourra vous servir puisqu'elle contient les références qui nous ont servies à comprendre le fonctionnement d'un ECS et de la Raylib.

Pour conclure, nous tenous à remercier nos encadrants pour leurs conseils sur l'ensemble du projet. Ce projet est l'un des plus importants de la fin de la deuxième année et nous avons pris beaucoups de plaisir à le réalisé.

## X- Sources

- Wikipédia ECS
- Wikipédia Conception Orienté Objet
- Wikipédia Raylib
- Documentation ECS
- Documentation Raylib
- Source interne Epitech
