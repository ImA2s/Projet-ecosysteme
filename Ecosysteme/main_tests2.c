#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>

#include "ecosys.h"


int main(void) {
    int i = 0;
    Animal *liste_proie = NULL;
    Animal *liste_predateur = NULL;

    srand(time(NULL));


    // Création de 20 proies à des positions aléatoires
    for (i = 0; i < 20; i++) {
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, 10, &liste_proie);
    }

    // Vérification du nombre de proies avec assert
    assert(compte_animal_rec(liste_proie) == 20);

    // Création de 20 prédateurs à des positions aléatoires
    for (i = 0; i < 20; i++) {
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, 10, &liste_predateur);
    }

    // Vérification du nombre de prédateurs avec assert
    assert(compte_animal_rec(liste_predateur) == 20);

    //Suppression de quelques proies et quelques prédateur de maniere a enlever le prochain
    enlever_animal(&liste_proie,liste_proie->suivant);
    enlever_animal(&liste_predateur,liste_predateur->suivant);
    
    // Affichage de l'écosystème
    afficher_ecosys(liste_proie, liste_predateur);
    
    Animal *liste_proie1=NULL;
    Animal *liste_predateur1=NULL;
    
    //Exercice 3
	ecrire_ecosys("fichier.txt",liste_predateur,liste_proie);
	lire_ecosys("fichier.txt",&liste_predateur1,&liste_proie1);

	// Affichage de l'écosystème à partir du fichier
	printf("Affichage à partir du fichier\n");
    afficher_ecosys(liste_proie1, liste_predateur1);
    //Donc on constate que c'est le meme que le premier affichage


    // Libération de la mémoire allouée
    liberer_liste_animaux(liste_proie);
    liberer_liste_animaux(liste_predateur);
    
    liberer_liste_animaux(liste_proie1);
    liberer_liste_animaux(liste_predateur1);
  
    

    return 0;
}

