#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000


int main(void) {
    
  //Part 2:
    //exercice 4, questions 2 et 4
    
    //Test bouger_animaux
     Animal *a1 = creer_animal(0,0,10); //il est en haut tout a gauche
     a1->dir[0]=1;
     a1->dir[1]=-1;
     /* d'apres l'énoncé la prairie est en haut à gauche, une direction de (1,-1)
     correspond à un mouvement vers la case en haut (1) et à droite (-1) */
     printf("On se déplace de (1,-1)\n");
     bouger_animaux(a1);
     afficher_ecosys(a1,NULL);
     /* L'abscisse est de 0 à 19 et lorsque on augmente de 1 on voit bien que il réapparaît à gauche
     de meme avec les ordonnées. Donc le monde est bien torique !  */
    
    Animal *liste_proie = NULL;
    Animal *liste_predateur = NULL;
    Animal *a2 = creer_animal(15,35, 10);
  
    a1->suivant=a2;
    liste_proie=a1;

    Animal *a5 = creer_animal(2,5, 10);
    Animal *a6 = creer_animal(10,35, 10);
  
    a5->suivant=a6;
    liste_predateur=a5;
    // Afficher l'écosystème
     afficher_ecosys(liste_proie,liste_predateur);
     
     
         
    //Test reproduce
    printf("Reproduction des proies *2\n");
    reproduce(&liste_proie,1.0);
    afficher_ecosys(liste_proie,liste_predateur);
    printf("On voit bien que le nombre de proie a doublé\n");
   
   
   
   
   //Creation du monde
    Animal *liste_proie1 = NULL;
    Animal *liste_predateur1 = NULL; 
    
    int monde[SIZE_X][SIZE_Y];
        for(int i=0;i<SIZE_X;i++){
            for(int j=0;j<SIZE_Y;j++){
                monde[i][j]=0;
            }    
        }
    

    srand(time(NULL));
    // Créer 20 proies avec des positions et énergies aléatoires
    float energie_proie=10;
    float energie_predateur=165;
    //On peut faire varier ces deux parametres ainsi que les variables p_reproduce_proie, p_reproduce_predateur, temps_repousse_herbe
    
    for (int i=0; i<20; i++) {
        ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie_proie,&liste_proie1);
        ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie_predateur,&liste_predateur1);
        /*On peut augmenter l'energie des prédateurs pour avoir plus de chance que
        pendant qu'ils bougent ils trouvent au moins une proie pour qu'ils augmentent leur
        energies sinon il meurt trop rapidement */
    }
    
    // Ouvrir le fichier pour enregistrer les données
    FILE *f = fopen("Evol_Pop.txt", "w");
    if (f==NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier Evol_Pop.txt\n");
        return 1;
    }
    
    int iter = 0;
    while ((liste_proie1 || liste_predateur1) && iter<200) {
        // Effacement de l'écran
        clear_screen(); 
        // Écrire l'itération et les comptages dans le fichier
        fprintf(f, "%d %d %d\n",iter ,compte_animal_rec(liste_proie1),compte_animal_rec(liste_predateur1)); 
        // Afficher l'écosystème
        afficher_ecosys(liste_proie1, liste_predateur1);
        // Rafraîchir les proies : bouger, réduire l'énergie, et éliminer les proies mortes
        rafraichir_proies(&liste_proie1,monde); 
        // Rafraîchir les prédateurs : bouger, réduire l'énergie, et manger les proies
        rafraichir_predateurs(&liste_predateur1,&liste_proie1);
        // Rafraîchir le monde (herbe)
        rafraichir_monde(monde);
  
        // temps necessaire pour afficher avant la prochaine itération
        usleep(T_WAIT);
        iter++;
    }
    fclose(f);
    printf("Fin de la simulation après %d itérations.\n", iter);
    
    
    // Libérer la mémoire des animaux
    liberer_liste_animaux(liste_proie);
    liberer_liste_animaux(liste_predateur);
    liberer_liste_animaux(liste_proie1);
    liberer_liste_animaux(liste_predateur1);
       
  return 0;

}
