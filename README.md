# Simulation d'Écosystème

## Description

Ce projet consiste à programmer une simulation simple d’écosystème en utilisant des **listes chaînées** et différentes structures de données.

L’objectif est de manipuler des structures dynamiques en C et d’implémenter une simulation contenant deux types d’entités :

- des **proies**
- des **prédateurs**

Les prédateurs peuvent manger les proies.

Ce modèle d’écosystème n’a pas vocation à être réaliste mais permet de se familiariser avec le concept d’**équilibre dans un écosystème**.

---

# Modèle de l’écosystème

L’écosystème simulé est un **monde discret représenté par un tore**, affiché sous forme de rectangle.

Le monde est composé d’un certain nombre de cases identifiées par leurs coordonnées :
(x, y)


Chaque case peut contenir :

- plusieurs **proies**
- plusieurs **prédateurs**
- de l’**herbe**, qui constitue la nourriture des proies

Les proies et les prédateurs peuvent se **déplacer dans le monde** au cours de la simulation.

---

# Structures de données

La simulation repose sur plusieurs structures de données principales :

- une **liste chaînée contenant les proies**
- une **liste chaînée contenant les prédateurs**
- un **tableau statique à deux dimensions représentant le monde**

Les proies et les prédateurs sont représentés par **une même structure de données**.

---

# Structure Animal

Les proies et les prédateurs sont représentés par une structure contenant :

- les coordonnées entières `x` et `y`
- une valeur réelle `energie`
- un tableau `dir` de deux entiers représentant la direction
- un pointeur `suivant` permettant de chaîner les éléments dans une liste

Cette structure est définie dans `ecosys.h` via un `typedef` nommé : Animal


---

# Organisation du programme

Le programme est organisé en quatre fichiers principaux :

main_tests.c
main_ecosys.c
ecosys.c
ecosys.h


### main_tests.c

Contient un **programme principal permettant de tester les fonctions** implémentées.

### main_ecosys.c

Contient un **programme principal permettant de simuler l’écosystème**.

### ecosys.c

Contient les **fonctions de manipulation des listes chaînées et des animaux**.

### ecosys.h

Contient :

- les **prototypes des fonctions**
- les **définitions des structures**

---

# Fonctions principales

Plusieurs fonctions sont implémentées pour manipuler les listes d’animaux.

### Création d’un animal

Prototype :

Animal *creer_animal(int x, int y, float energie);


Cette fonction :

- alloue dynamiquement un animal
- initialise les champs `x`, `y` et `energie`
- initialise aléatoirement la direction `dir`
- vérifie l’allocation mémoire avec `assert`

---

### Ajout dans une liste

Prototype :

Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal);


Cette fonction permet **d’ajouter un animal en tête d’une liste chaînée**.

---

### Comptage des animaux

Deux versions sont implémentées :

unsigned int compte_animal_rec(Animal *la);
unsigned int compte_animal_it(Animal *la);


- une version **récursive**
- une version **itérative**

Ces fonctions permettent de **compter le nombre d’éléments dans une liste chaînée**.

---

# Affichage de l'écosystème

L’écosystème est affiché sous forme de grille.

Chaque case est représentée par un caractère :

' ' case vide
'*' case contenant au moins une proie
'O' case contenant au moins un prédateur
'@' case contenant proies et prédateurs


Exemple d’affichage :

Nb proies (): 20

Nb predateurs (O): 20

+----------+
| * |

| O * **O|

| OO |

| O O |

| @ O O |

| ** *O |

| @ O @ |

| * O@ |

| O O |

| O O @ |

+----------+

L’herbe n’est pas affichée dans cette version.

---

# Tests

Un programme de test permet de :

- créer **20 proies et 20 prédateurs**
- les placer à des positions aléatoires
- vérifier leur nombre avec les fonctions de comptage
- afficher l’état de l’écosystème

---

# Gestion mémoire

Plusieurs fonctions permettent de gérer la mémoire :

### Libération de la liste

void liberer_liste_animaux(Animal *liste);


Cette fonction permet de **libérer toute la mémoire allouée pour une liste d’animaux**.

---

### Suppression d’un animal

void enlever_animal(Animal **liste, Animal *animal);


Cette fonction permet :

- de retirer un animal d’une liste chaînée
- de libérer la mémoire associée

---

# Vérification des fuites mémoire

Le programme est testé avec **Valgrind** pour vérifier l’absence de fuites mémoire :

valgrind ./tests_ecosys2

Objectif :

definitely lost: 0 bytes
indirectly lost: 0 bytes


---

# Compilation

La compilation est facilitée grâce à l’utilisation d’un **Makefile**.

Le Makefile permet de générer :

tests_ecosys
ecosys
tests_ecosys2


---

# Conclusion

Ce projet permet de manipuler plusieurs concepts importants en programmation C :

- listes chaînées
- gestion dynamique de la mémoire
- structures de données
- organisation modulaire d’un programme
- simulation simple d’un système dynamique
