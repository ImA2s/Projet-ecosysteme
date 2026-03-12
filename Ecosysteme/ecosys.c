#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "ecosys.h"

/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}

/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
   assert(x>=0 && x<SIZE_X && y>=0 && y<SIZE_Y);
   Animal * new = creer_animal(x,y,energie);
  *liste_animal = ajouter_en_tete_animal(*liste_animal,new);
}

/* A Faire. Part 1, exercice 6, question 4 */
Animal* liberer_liste_animaux(Animal *liste) {
    Animal *tpm;
   while(liste){
        tpm=liste->suivant;
        free(liste);
        liste=tpm;
    }
  return NULL;
}

/* A Faire. Part 1, exercice 6, question 7 */
void enlever_animal(Animal **liste, Animal *animal){
    Animal *tpm=*liste;
    Animal *prec=NULL;
     
    while(tpm && tpm!=animal){
        prec=tpm;
        tpm=tpm->suivant;
    }
    if(tpm){
        if(prec) prec->suivant=tpm->suivant;
        else *liste=tpm->suivant;
        free(tpm);
    }
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    cpt++;
    la=la->suivant;
  }
  return cpt;
}

/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; i++) {
    for (j = 0; j < SIZE_Y; j++) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
      ecosys[pa->x][pa->y] = '*';
      pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  
  while (pa) {
   assert(pa->x < SIZE_X && pa->y <SIZE_Y );
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; j++) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; i++) {
    printf("|");
    for (j = 0; j < SIZE_Y; j++) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; j++) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}
 
void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/


//Exercice 3 Lecture/eciture

void ecrire_ecosys(const char *nom_fichier, Animal *liste_predateur, Animal *liste_proie){
	FILE *f=fopen(nom_fichier,"w");
	if (f==NULL){
		fprintf(stderr,"Erreur de l'ouverture fichier %s\n",nom_fichier);
		return;
	}
	Animal *tpm=liste_proie ;//on garde la tete de la liste
	fprintf(f,"<proies>\n");
	while(tpm){
		fprintf(f,"x=%d y=%d dir=[%d %d] e=%f\n",tpm->x,tpm->y,tpm->dir[0],tpm->dir[1],tpm->energie);
		tpm=tpm->suivant;
	}
	fprintf(f,"</proies>\n");
	tpm=liste_predateur;
	fprintf(f,"<predateurs>\n");
	while(tpm){
		fprintf(f,"x=%d y=%d dir=[%d %d] e=%f\n",tpm->x,tpm->y,tpm->dir[0],tpm->dir[1],tpm->energie);
		tpm=tpm->suivant;
	}
	fprintf(f,"</predateurs>\n");
	fclose(f);
}

void lire_ecosys(const char *nom_fichier, Animal **liste_predateur, Animal **liste_proie){

    //on ouvre le fichier en mode lecture
    FILE *f = fopen(nom_fichier, "r");
    if (f==NULL) {
    fprintf(stderr,"Erreur de l'ouverture fichier %s\n",nom_fichier);
    return;
  }
    int x_lu,y_lu,dir_0_lu,dir_1_lu;
    float e_lu;
    char buffer[256]; 
  
    // Lecture du fichier ligne par ligne
    while (fgets(buffer, sizeof(buffer),f) != NULL) {
  
        // On fait la lecture pour les proies
        if (strcmp(buffer, "<proies>\n") == 0){
            while (fgets(buffer, sizeof(buffer), f) != NULL && strcmp(buffer, "</proies>\n") != 0){ 
                sscanf(buffer, "x=%d y=%d dir=[%d %d] e=%f\n", &x_lu, &y_lu, &dir_0_lu, &dir_1_lu, &e_lu);

                // Ajout d'une proie à la liste des proies
                ajouter_animal(x_lu,y_lu,e_lu,liste_proie);
                (*liste_proie)->dir[0]=dir_0_lu;
                (*liste_proie)->dir[1]=dir_1_lu;
            }
        }

        // On fait la lecture pour les prédateurs
        if (strcmp(buffer, "<predateurs>\n") == 0){
            while (fgets(buffer, sizeof(buffer), f) != NULL && strcmp(buffer, "</predateurs>\n") != 0){ 
                sscanf(buffer, "x=%d y=%d dir=[%d %d] e=%f\n", &x_lu, &y_lu, &dir_0_lu, &dir_1_lu, &e_lu);
        
                // Ajout d'une proie à la liste des prédateurs
                ajouter_animal(x_lu,y_lu,e_lu,liste_predateur);
                (*liste_predateur)->dir[0]=dir_0_lu;
                (*liste_predateur)->dir[1]=dir_1_lu;
            }
        }
    }
    fclose(f);
}

/* Parametres globaux de l’ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
    while (la) {
        // Changer de direction aléatoirement avec une probabilité p_ch_dir
        if ((float)rand() / RAND_MAX < p_ch_dir) { 
            la->dir[0]=rand()%3-1;  
            la->dir[1]=rand()%3-1; 
        }
        // Mise à jour des coordonnées en tenant compte du monde torique
        la->y =(SIZE_Y+la->y+la->dir[0])%SIZE_Y; 
        la->x =(SIZE_X+la->x+la->dir[1])%SIZE_X; 
        la=la->suivant;
    }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
    Animal *tmp=*liste_animal; //on garde la tete
    while(tmp){
        if ((float)rand() / RAND_MAX < p_reproduce){
            ajouter_animal(tmp->x,tmp->y,(tmp->energie)/2,liste_animal);
            tmp->energie=(tmp->energie)/2;
        }
        tmp=tmp->suivant;
    }
}

/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    bouger_animaux(*liste_proie);
     Animal *tmp=*liste_proie;
     while(tmp){
        tmp->energie -=1;
        if(tmp->energie<=0){
            Animal *animal_mort=tmp;
            tmp=tmp->suivant;
            enlever_animal(liste_proie,animal_mort);
            continue;
        }
        if (monde[tmp->x][tmp->y]>=0){
            tmp->energie=(tmp->energie)+monde[tmp->x][tmp->y];
            monde[tmp->x][tmp->y] = temps_repousse_herbe; 
        }
        tmp=tmp->suivant;
    }
    reproduce(liste_proie,p_reproduce_proie);
}

/* Part 2. Exercice 6, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    while(l){
        if(l->x==x && l->y==y) return l;
        l=l->suivant;
    }
  return NULL;
} 

/* Part 2. Exercice 6, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
     bouger_animaux(*liste_predateur);
     Animal *tmp=*liste_predateur;
     while(tmp){
        tmp->energie -=1;
        if(tmp->energie<=0){
            Animal *animal_mort=tmp;
            tmp=tmp->suivant;
            enlever_animal(liste_predateur,animal_mort);
            continue ;
        }
        Animal *proie=animal_en_XY(*liste_proie,tmp->x,tmp->y);
        if(proie){
            tmp->energie+=proie->energie;
            enlever_animal(liste_proie,proie);
        }
        tmp=tmp->suivant;
    }
    reproduce(liste_predateur,p_reproduce_predateur);
}

/* Part 2. Exercice 7, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]) {
    for (int i=0;i<SIZE_X;i++) {
        for (int j=0;j<SIZE_Y;j++) {
            monde[i][j]+=1;
        }
    }
}     



